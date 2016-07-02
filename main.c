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
    // position 
    uint8_t x;
    uint8_t y;

    // speed?
    int8_t vx;
    int8_t vy;

    // health
    uint8_t health;

    // list management
    uint8_t prev;  
    uint8_t next;

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

void UpdateInput();
void WaitFrame(void);
void __fastcall__ bankswitch(unsigned char bank);

#pragma bss-name(push, "ZEROPAGE")
size_t i, x, y, mapX, mapY, tileIndex;
uint8_t tile, tileIdx;
uint8_t currentEntityId; // parameter for update func ptr
uint8_t currentMetaSpriteId; // reset it to 0 at each frame!
#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
Sprite sprites[64];
#pragma bss-name(pop)

const uint8_t PALETTE[] = { 0x22, 0x00, 0x10, 0x20,
                            0x22, 0x11, 0x21, 0x31,
                            0x22, 0x15, 0x25, 0x35,
                            0x22, 0x19, 0x29, 0x39,
                            0x22, 0x16, 0x05, 0x27,
                            0x22, 0x11, 0x21, 0x31,
                            0x22, 0x15, 0x25, 0x35,
                            0x22, 0x19, 0x29, 0x39 };

const uint8_t mapWidth = 32; // tiles count

// map meta tile
const uint8_t map[] = { 0x01, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05,
                        0x01, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x01, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x01, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x03, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
                        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05};

void __fastcall__ copyBgLine(uint8_t line) {
    for(tile = 0; tile < 64; tile++) {
        tileIdx = map[line * 16 + ((tile & 0x1F) >> 1)] << 1;

        if(tile & 0x1) {
            ++tileIdx;
        }

        if(tile >= 32) {
            tileIdx += 0x10;
        }
        PPU.vram.data = tileIdx;
    }
}

void fillBackground() {
    PPU.vram.address = 0x20;
    PPU.vram.address = 0x00;

    // for each line of nametable 0
    for(i = 0; i < 15; i++) {
        // copy tile idx to bufer
        copyBgLine(i);
    }

    // color
    PPU.vram.address = 0x23;
    PPU.vram.address = 0xC0;
    for(i = 0; i < 64; i++) {
        PPU.vram.data = 0x55;
    }

    PPU.vram.address = 0x28;
    PPU.vram.address = 0x00;
    // for each line of nametable 0
    for(i = 0; i < 15; i++) {
        // copy tile idx to bufer
        copyBgLine(15 + i);
    }

}

const uint8_t playerSpriteFrames[2][17] = {
    { // x, y, tile, attr
        0, 0, 0x00, 0x00,
        8, 0, 0x01, 0x00,
        0, 8, 0x10, 0x00,
        8, 8, 0x11, 0x00,
        127
    },
    { // x, y, tile, attr
        0, 0, 0x02, 0x00,
        8, 0, 0x03, 0x00,
        0, 8, 0x12, 0x00,
        8, 8, 0x13, 0x00,
        127
    },

};

// return next id
void __fastcall__ drawMetaSprite(uint8_t x, uint8_t y, const uint8_t *data) {
    // copy data at pos
    const uint8_t *ptr = data;
    while(*ptr != 127) {
        sprites[currentMetaSpriteId].x = x + *(ptr++);
        sprites[currentMetaSpriteId].y = y + *(ptr++);
        sprites[currentMetaSpriteId].tile_index = *(ptr++);
        sprites[currentMetaSpriteId].attributes = *(ptr++);

        currentMetaSpriteId++;
    }
}

// 16?
#define ENTITY_COUNT 16
Entity entities[ENTITY_COUNT]; 
uint8_t freeEntityList = 0xFF;
uint8_t entityList = 0xFF;

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
        entities[i].next = i == ENTITY_COUNT - 1 ? 0x0FF : i + 1;
    }

    freeEntityList = 0;
    entityList = 0xFF;
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
    }

    entities[id].next = 0xFF;
    entities[id].prev = 0xFF;
}

// pop the first entity of the list
uint8_t popEntity(uint8_t *list) {
    uint8_t newId = *list;

    removeEntity(newId, list);

    return newId;
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

    entities[currentEntityId].x += entities[currentEntityId].vx;
    entities[currentEntityId].y += entities[currentEntityId].vy;

    // update player sprites
    drawMetaSprite(entities[currentEntityId].x, entities[currentEntityId].y, playerSpriteFrames[(FrameCount >> 2) & 0x01]);

    if(entities[currentEntityId].y > 240) {
        removeEntity(currentEntityId, &entityList);
        pushEntity(currentEntityId, &freeEntityList);
    }
}

/**
 * main() will be called at the end of the initialization code in reset.s.
 * Unlike C programs on a computer, it takes no arguments and returns no value.
 */
void main(void) {
    uint8_t playerId;

    // load the palette data into PPU memory $3f00-$3f1f
    PPU.vram.address = 0x3f;
    PPU.vram.address = 0x00;
    for ( i = 0; i < sizeof(PALETTE); ++i ) {
        PPU.vram.data = PALETTE[i];
    }

    initEntityList();

    bankswitch(0);

    fillBackground();
    Scroll = 0;

    playerId = popEntity(&freeEntityList);
    pushEntity(playerId, &entityList);
    entities[playerId].x = 64;
    entities[playerId].y = 128;
    entities[playerId].vx = 0;
    entities[playerId].vy = 0;
    entities[playerId].health = 255;
    entities[playerId].update = playerUpdate;

    playerId = popEntity(&freeEntityList);
    pushEntity(playerId, &entityList);
    entities[playerId].x = playerId;
    entities[playerId].y = 64;
    entities[playerId].vx = 0;
    entities[playerId].vy = 0;
    entities[playerId].health = 255;
    entities[playerId].update = playerUpdate;

    // tells the NMI to update
    // THIS ONE IS VERY IMPORTANT as without sprite 0 is not displayed and the NMI will be stuck!
    VRAMUpdateReady = 1;

    // enable NMI and rendering
    PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_ON;
    PPU.mask = PPUMASK_L8_BSHOW | PPUMASK_L8_SSHOW | PPUMASK_SSHOW | PPUMASK_BSHOW;

    APU.status = 0x0F;

    Scroll = 0;

    // infinite loop
    while (1) {
        WaitFrame();

        currentMetaSpriteId = 0; // might be done in nmi?

        // Auto scroll
        if(FrameCount > 0x30) {
            if(Scroll > 0) {
                --Scroll;

                if(Scroll == 255) {
                    Scroll = 239;
                }
            } else {
                Scroll = 256 + 239;
            }

            FrameCount = 0;
        }

        // update game entity
        currentEntityId = entityList;
        while(currentEntityId != 0xFF) {
            uint8_t next = entities[currentEntityId].next;
            entities[currentEntityId].update();
            currentEntityId = next;
        }

        // tells the NMI to update
        VRAMUpdateReady = 1;
    }   
};
