#include <stddef.h>
#include <stdint.h>
#include <nes.h>

// PPU_CTRL flags
// see http://wiki.nesdev.com/w/index.php/PPU_registers#Controller_.28.242000.29_.3E_write
#define PPUCTRL_NAMETABLE_0 0x00 // use nametable 0
#define PPUCTRL_NAMETABLE_1 0x01 // use nametable 1
#define PPUCTRL_NAMETABLE_2 0x02 // use nametable 2
#define PPUCTRL_NAMETABLE_3 0x03 // use nametable 3
#define PPUCTRL_INC_1_HORIZ 0x00 // PPU_DATA increments 1 horizontally
#define PPUCTRL_INC_32_VERT 0x04 // PPU_DATA increments 32 vertically
#define PPUCTRL_SPATTERN_0  0x00 // sprite pattern table 0
#define PPUCTRL_SPATTERN_1  0x08 // sprite pattern table 1
#define PPUCTRL_BPATTERN_0  0x00 // background pattern table 0
#define PPUCTRL_BPATTERN_1  0x10 // background pattern table 1
#define PPUCTRL_SSIZE_8x8   0x00 // 8x8 sprite size
#define PPUCTRL_SSIZE_8x16  0x20 // 8x16 sprite size
#define PPUCTRL_NMI_OFF     0x00 // disable NMIs
#define PPUCTRL_NMI_ON      0x80 // enable NMIs

// PPU_MASK flags
// see http://wiki.nesdev.com/w/index.php/PPU_registers#Mask_.28.242001.29_.3E_write
#define PPUMASK_COLOR    0x00
#define PPUMASK_GRAY     0x01
#define PPUMASK_L8_BHIDE 0x00
#define PPUMASK_L8_BSHOW 0x02
#define PPUMASK_L8_SHIDE 0x00
#define PPUMASK_L8_SSHOW 0x04
#define PPUMASK_BHIDE    0x00
#define PPUMASK_BSHOW    0x08
#define PPUMASK_SHIDE    0x00
#define PPUMASK_SSHOW    0x10
#ifdef TV_NTSC
    #define PPUMASK_EM_RED   0x20
    #define PPUMASK_EM_GREEN 0x40
#else // TV_PAL
    #define PPUMASK_EM_RED   0x40
    #define PPUMASK_EM_GREEN 0x20
#endif
#define PPUMASK_EM_BLUE 0x80

#define BUTTON_RIGHT  0x01
#define BUTTON_LEFT   0x02
#define BUTTON_DOWN   0x04
#define BUTTON_UP     0x08
#define BUTTON_START  0x10
#define BUTTON_SELECT 0x20
#define BUTTON_B      0x40
#define BUTTON_A      0x80

typedef struct _Sprite {
    uint8_t y;          // y pixel coordinate
    uint8_t tile_index; // index into pattern table
    uint8_t attributes; // attribute flags
    uint8_t x;          // x pixel coordinate
} Sprite;

typedef struct _Entity {
    // list management
    uint8_t prev;  
    uint8_t next;

    // position 
    uint8_t x;
    uint8_t y;

    // speed?
    int8_t vx;
    int8_t vy;

    // health
    uint8_t health;

    // update function
    void (*update)(void); 
} Entity;

extern uint8_t FrameCount;
#pragma zpsym("FrameCount");

extern uint8_t InputPort1;
#pragma zpsym("InputPort1");

extern uint8_t InputPort1Prev;
#pragma zpsym("InputPort1Prev");

extern uint8_t InputPort2;
#pragma zpsym("InputPort2");

extern uint8_t InputPort2Prev;
#pragma zpsym("InputPort2Prev");

extern uint8_t VRAMUpdateReady;
#pragma zpsym("VRAMUpdateReady");

extern uint16_t Scroll;
#pragma zpsym("Scroll");

extern uint16_t BGDestAddr;
#pragma zpsym("BGDestAddr");

extern uint8_t BGBuffer;
#pragma zpsym("BGBuffer");

void UpdateInput();
void WaitFrame(void);
void __fastcall__ bankswitch(unsigned char bank);
void flushBGBuffer();

#pragma bss-name(push, "ZEROPAGE")
uint8_t endLoop;
size_t i, x, y, mapX, mapY, tileIndex;
uint8_t tile, tileIdx;
uint8_t currentEntityId; // parameter for update func ptr
uint8_t currentMetaSpriteId; // reset it to 0 at each frame!
uint16_t mapCurrentLine;
uint16_t timer;
#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
Sprite sprites[64];
#pragma bss-name(pop)

#include "title.c"
#include "level.c"

void __fastcall__ copyBgLine(const uint8_t *buffer, uint16_t line) {
    static uint8_t *ptr;
    ptr = &BGBuffer;

    for(tile = 0; tile < 64; tile++) {
        tileIdx = buffer[line * 16 + ((tile & 0x1F) >> 1)] << 1;

        if(tile & 0x1) {
            ++tileIdx;
        }

        if(tile >= 32) {
            tileIdx += 0x10;
        }

        (*ptr++) = tileIdx;
    }
}

void fillBackground() {
    mapCurrentLine = mapLineCount - 30;

    PPU.vram.address = 0x20;
    PPU.vram.address = 0x00;

    // for each line of nametable 0
    for(i = 0; i < 15; i++) {
        // copy tile idx to bufer
        copyBgLine(map, mapCurrentLine + i);
        flushBGBuffer();
    }

    PPU.vram.address = 0x28;
    PPU.vram.address = 0x00;
    // for each line of nametable 0
    for(i = 0; i < 15; i++) {
        // copy tile idx to bufer
        copyBgLine(map, mapCurrentLine + 15 + i);
        flushBGBuffer();
    }

    // color
    PPU.vram.address = 0x23;
    PPU.vram.address = 0xC0;
    for(i = 0; i < 64; i++) {
        PPU.vram.data = 0x00;
    }

    // color
    PPU.vram.address = 0x2B;
    PPU.vram.address = 0xC0;
    for(i = 0; i < 64; i++) {
        PPU.vram.data = 0xFF;
    }

}

const uint8_t playerSpriteFrames[][17] = {
    { // x, y, tile, attr
        0, 0, 0x24, 0x00,
        8, 0, 0x25, 0x00,
        0, 8, 0x34, 0x00,
        8, 8, 0x35, 0x00,
        127
    },
    { // x, y, tile, attr
        0, 0, 0x22, 0x00,
        8, 0, 0x23, 0x00,
        0, 8, 0x32, 0x00,
        8, 8, 0x33, 0x00,
        127
    },

    { // x, y, tile, attr
        0, 0, 0x26, 0x00,
        8, 0, 0x27, 0x00,
        0, 8, 0x36, 0x00,
        8, 8, 0x37, 0x00,
        127
    },
    { // x, y, tile, attr
        0, 0, 0x28, 0x00,
        8, 0, 0x29, 0x00,
        0, 8, 0x38, 0x00,
        8, 8, 0x39, 0x00,
        127
    },

    { // x, y, tile, attr
        0, 0, 0x2A, 0x00,
        8, 0, 0x2B, 0x00,
        0, 8, 0x3A, 0x00,
        8, 8, 0x3B, 0x00,
        127
    },
    { // x, y, tile, attr
        0, 0, 0x2C, 0x00,
        8, 0, 0x2D, 0x00,
        0, 8, 0x3C, 0x00,
        8, 8, 0x3D, 0x00,
        127
    },
};

// return next id
void __fastcall__ drawMetaSprite(uint8_t x, uint8_t y, const uint8_t *data) {
    // copy data at pos
    const uint8_t *ptr = data;
    while(*ptr != 127) {
        if(x + *ptr < 255) {
            sprites[currentMetaSpriteId].x = x + *(ptr++);
            sprites[currentMetaSpriteId].y = y + *(ptr++);
            sprites[currentMetaSpriteId].tile_index = *(ptr++);
            sprites[currentMetaSpriteId].attributes = *(ptr++);

            currentMetaSpriteId++;
        } else {
            ptr += 4; 
        }
    }
}

void __fastcall__ drawSprite(uint8_t x, uint8_t y, uint8_t tile, uint8_t attr) {
    // copy data at pos
    sprites[currentMetaSpriteId].x = x;
    sprites[currentMetaSpriteId].y = y;
    sprites[currentMetaSpriteId].tile_index = tile;
    sprites[currentMetaSpriteId].attributes = attr;

    currentMetaSpriteId++;
}


// 16?
#define ENTITY_COUNT 16
Entity entities[ENTITY_COUNT]; 
uint8_t freeEntityList = 0xFF;
uint8_t entityList = 0xFF;
uint8_t missileList = 0xFF;

// reset entity
void initEntityList() {
    for(i = 0; i < ENTITY_COUNT; i++) {
        entities[i].x = 0;
        entities[i].y = 0;
        entities[i].vx = 0;
        entities[i].vy = 0;
        entities[i].update = NULL;
        entities[i].health = 0;
        entities[i].prev = i == 0? 0xFF : i - 1;
        entities[i].next = i == ENTITY_COUNT - 1 ? 0xFF : i + 1;
    }

    freeEntityList = 0;
    entityList = 0xFF;
    missileList = 0xFF;
}

// push an entity to the list
void pushEntity(uint8_t id, uint8_t *list) {
    if(*list != 0xFF) {
        entities[id].next = *list;
        entities[*list].prev = id;
        *list = id;
    } else {
        *list = id;
    }
}

// remove an entity from the list
void removeEntity(uint8_t id, uint8_t *list) {
    // if it's the first element
    if(*list == id) {
        if(entities[id].next == 0xFF) {
            *list = 0xFF; // empty list
        } else {
            *list = entities[id].next;
            entities[*list].prev = 0xFF;
        }
    } else {
        entities[entities[id].prev].next = entities[id].next;
        entities[entities[id].next].prev = entities[id].prev;
    }

    entities[id].next = 0xFF;
    entities[id].prev = 0xFF;
}

// pop the first entity of the list
uint8_t popEntity(uint8_t *list) {
    uint8_t newId = *list;

    if(newId != 0xFF)
        removeEntity(newId, list);

    return newId;
}

void bulletUpdate() {
    entities[currentEntityId].x += entities[currentEntityId].vx;
    entities[currentEntityId].y += entities[currentEntityId].vy;

    if(entities[currentEntityId].y + entities[currentEntityId].vy > entities[currentEntityId].y) {
        removeEntity(currentEntityId, &entityList);
        pushEntity(currentEntityId, &freeEntityList);
    }

    // update player sprites
    drawSprite(entities[currentEntityId].x, entities[currentEntityId].y, 0x60, 0x00);
}

void __fastcall__ spawnBullet(uint8_t x, uint8_t y) {
    static uint8_t id;
    id = popEntity(&freeEntityList);

    // if there's a free entity
    if(id != 0xFF) {
        pushEntity(id, &entityList);
        entities[id].x = x;
        entities[id].y = y;
        entities[id].vx = 0;
        entities[id].vy = -4;
        entities[id].health = 255;
        entities[id].update = bulletUpdate;
    }
}

void playerUpdate() {
    if(InputPort1 & BUTTON_UP) {
        if (entities[currentEntityId].vy > -6) {
            entities[currentEntityId].vy -= 1;
        }
    }
    else if(InputPort1 & BUTTON_DOWN) {
        if (entities[currentEntityId].vy < 6) {
            entities[currentEntityId].vy += 1;
        }
    } else if(entities[currentEntityId].vy > 2) {
        entities[currentEntityId].vy -= 2;
    } else if(entities[currentEntityId].vy < -2) {
        entities[currentEntityId].vy += 2;
    } else {
        entities[currentEntityId].vy = 0;
    }

    if(InputPort1 & BUTTON_LEFT) {
        if (entities[currentEntityId].vx > -6) {
            --entities[currentEntityId].vx;
        }
    } else if(InputPort1 & BUTTON_RIGHT) {
        if (entities[currentEntityId].vx < 6) {
            ++entities[currentEntityId].vx;
        }
    } else if(entities[currentEntityId].vx > 2) {
        entities[currentEntityId].vx -= 2;
    } else if(entities[currentEntityId].vx < -2) {
        entities[currentEntityId].vx += 2;
    } else {
        entities[currentEntityId].vx = 0;
    }

    if(entities[currentEntityId].vy < 0 && entities[currentEntityId].y + entities[currentEntityId].vy - 16 > entities[currentEntityId].y) {
        entities[currentEntityId].y = 16;
        entities[currentEntityId].vy = 0;
    }

    if(entities[currentEntityId].y + entities[currentEntityId].vy > 218) {
        entities[currentEntityId].y = 218;
        entities[currentEntityId].vy = 0;
    }

    if(entities[currentEntityId].vx < 0 && entities[currentEntityId].x + entities[currentEntityId].vx > entities[currentEntityId].x) {
        entities[currentEntityId].x = 0;
        entities[currentEntityId].vx = 0;
    }

    if(entities[currentEntityId].x + entities[currentEntityId].vx > 240) {
        entities[currentEntityId].x = 240;
        entities[currentEntityId].vx = 0;
    }


    entities[currentEntityId].x += entities[currentEntityId].vx;
    entities[currentEntityId].y += entities[currentEntityId].vy;

    if((InputPort1 & BUTTON_B) && !(InputPort1Prev & BUTTON_B)) {
        spawnBullet(entities[currentEntityId].x, entities[currentEntityId].y - 8);
        spawnBullet(entities[currentEntityId].x + 4, entities[currentEntityId].y - 8);
        spawnBullet(entities[currentEntityId].x + 8, entities[currentEntityId].y - 8);
    }

    // update player sprites
    if(entities[currentEntityId].vx > 2) {
        drawMetaSprite(entities[currentEntityId].x, entities[currentEntityId].y, playerSpriteFrames[((FrameCount >> 3) & 0x01) + 4]);
    } else if(entities[currentEntityId].vx < -2) {
        drawMetaSprite(entities[currentEntityId].x, entities[currentEntityId].y, playerSpriteFrames[((FrameCount >> 3) & 0x01) + 2]);
    } else {
        drawMetaSprite(entities[currentEntityId].x, entities[currentEntityId].y, playerSpriteFrames[((FrameCount >> 3) & 0x01)]);
    }
}

// load the palette data into PPU memory $3f00-$3f1f
void loadPalette(const uint8_t *pal) {
    PPU.vram.address = 0x3f;
    PPU.vram.address = 0x00;
    for ( i = 0; i < 32; ++i ) {
        PPU.vram.data = pal[i];
    }
}

/**
 * main() will be called at the end of the initialization code in reset.s.
 * Unlike C programs on a computer, it takes no arguments and returns no value.
 */
void main(void) {
    uint8_t playerId;


    // reset APU
    APU.status = 0x0F;

titleScreen:
    bankswitch(1);
    loadPalette(titlePalette);

    copyTitleScreen();
    Scroll = 239;
    timer = 0;
    VRAMUpdateReady = 1;

    // enable NMI and rendering
    PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_ON;

    while (!endLoop) {
        WaitFrame();

        if(timer > 32) {
            // blink text
            Scroll = 0;

            PPU.vram.address = 0x3f;
            PPU.vram.address = 0x0B;
            PPU.vram.data = (((FrameCount >> 2) & 0x03) << 4) + 0x06;
            PPU.vram.address = 0x00;
            PPU.vram.address = 0x00;

            if((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                endLoop = 1;
            }

        } else {
            ++timer;
            if(Scroll > 0) 
                Scroll -= 16;

            if(Scroll > 0x100)
                Scroll = 0;

        }

        // tells the NMI to update
        //VRAMUpdateReady = 1;
    }

    // wait an extra frame and disable rendering
    WaitFrame();
    PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_OFF;
    PPU.mask = 0;

gameState:
    bankswitch(0);

    loadPalette(mapPalette);

    initEntityList();
    fillBackground();

    playerId = popEntity(&freeEntityList);
    pushEntity(playerId, &entityList);
    entities[playerId].x = 64;
    entities[playerId].y = 128;
    entities[playerId].vx = 0;
    entities[playerId].vy = 0;
    entities[playerId].health = 255;
    entities[playerId].update = playerUpdate;

    // tells the NMI to update
    VRAMUpdateReady = 1;

    // enable NMI and rendering
    PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_ON;

    Scroll = 0x108;

    // "infinite" loop
    endLoop = 0;
    while (!endLoop) {
        WaitFrame();

        currentMetaSpriteId = 0; // might be done in nmi?

        // Auto scroll
        if(!(FrameCount & 0x00) && mapCurrentLine != 0xFFFF) { // stop when mapCurrentLine == -1
            if(Scroll > 0) {
                --Scroll;

                if(Scroll == 255) {
                    Scroll = 239;
                }
            } else {
                Scroll = 256 + 239;
            }

            if((Scroll & 0x0F) == 0x0F && mapCurrentLine != 0xFFFF) {
                --mapCurrentLine;
                copyBgLine(map, mapCurrentLine);
                BGDestAddr = (Scroll > 240 ? 0x2800 : 0x2000) + (((Scroll & 0xFF) >> 4) << 6);
            }
        }

        // update game entity
        currentEntityId = entityList;
        while(currentEntityId != 0xFF) {
            uint8_t next = entities[currentEntityId].next;
            entities[currentEntityId].update();
            currentEntityId = next;
        }

        // clean up unused sprites
        for(i = currentMetaSpriteId; i < 64; i++) {
            sprites[i].y = 240;
        }

        // tells the NMI to update
        VRAMUpdateReady = 1;
    }   
};
