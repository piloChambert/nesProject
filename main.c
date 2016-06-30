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

typedef struct sprite {
    uint8_t y;          // y pixel coordinate
    uint8_t tile_index; // index into pattern table
    uint8_t attributes; // attribute flags
    uint8_t x;          // x pixel coordinate
} sprite_t;

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

extern uint8_t SplitEnable;
#pragma zpsym("SplitEnable");

extern uint16_t Scroll;
#pragma zpsym("Scroll");

void UpdateInput();
void WaitFrame(void);
void __fastcall__ bankswitch(unsigned char bank);

#pragma bss-name(push, "ZEROPAGE")
size_t i, x, y, mapX, mapY, tileIndex;
uint16_t playerX = 0, playerY = 0;
int8_t playerSpeedX = 0;
int8_t playerYOffset = 0;
uint16_t relativePlayerX; // use to store screen space player X
uint16_t score = 5421;

#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
sprite_t spriteZero;
sprite_t playerSprites[4];
#pragma bss-name(pop)


const char ScoreText[] = "Score.";

const uint8_t PALETTE[] = { 0x22, 0x00, 0x10, 0x20,
                            0x22, 0x11, 0x21, 0x31,
                            0x22, 0x15, 0x25, 0x35,
                            0x22, 0x19, 0x29, 0x39,
                            0x22, 0x16, 0x05, 0x27,
                            0x22, 0x11, 0x21, 0x31,
                            0x22, 0x15, 0x25, 0x35,
                            0x22, 0x19, 0x29, 0x39 };

const uint8_t mapWidth = 32; // tiles count
const uint8_t map[] = { 0x04, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x01, 0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x01, 0x01, 0x04, 0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x04, 0x04, 0x04, 0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04};

void drawStatus() {
    PPU.vram.address = 0x20;
    PPU.vram.address = 0x40 + 0x04;    

    for(i = 0; i < sizeof(ScoreText); i++) {
        PPU.vram.data = ScoreText[i];
    }
}

void drawBackground() {
    PPU.vram.address = 0x20;
    PPU.vram.address = 0xA0;

    for(i = 0; i < 32 * 26; i++) {
        mapX = (i & 0x1F) >> 1;
        mapY = (i >> 6);

        tileIndex = map[mapX + (mapY << 5)] << 1;

        // second row
        if((i >> 5) & 0x1) {
            tileIndex += 16;
        }

        // second column
        if(i & 0x1) {
            ++tileIndex;
        }

        PPU.vram.data = (uint8_t)tileIndex;
    }

    // color
    PPU.vram.address = 0x23;
    PPU.vram.address = 0xC0;
    for(i = 0; i < 64; i++) {
        PPU.vram.data = 0x00;
    }
}

/**
 * main() will be called at the end of the initialization code in reset.s.
 * Unlike C programs on a computer, it takes no arguments and returns no value.
 */
void main(void) {
    // load the palette data into PPU memory $3f00-$3f1f
    PPU.vram.address = 0x3f;
    PPU.vram.address = 0x00;
    for ( i = 0; i < sizeof(PALETTE); ++i ) {
        PPU.vram.data = PALETTE[i];
    }

    bankswitch(1);

    drawStatus();
    drawBackground();
    Scroll = 0;

    // init sprite zero
    spriteZero.x = 72;
    spriteZero.y = 16;
    spriteZero.tile_index = 0xFF;

    // init player sprite
    playerSprites[0].x = 0;
    playerSprites[0].y = 0;
    playerSprites[0].tile_index = 0x00;

    playerSprites[1].x = 0;
    playerSprites[1].y = 0;
    playerSprites[1].tile_index = 0x01;

    playerSprites[2].x = 0;
    playerSprites[2].y = 0;
    playerSprites[2].tile_index = 0x10;

    playerSprites[3].x = 0;
    playerSprites[3].y = 0;
    playerSprites[3].tile_index = 0x11;

    playerX = 32;


    // tells the NMI to update
    // THIS ONE IS VERY IMPORTANT as without sprite 0 is not displayed and the NMI will be stuck!
    VRAMUpdateReady = 1;


    // enable NMI and rendering
    PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_ON;
    PPU.mask = PPUMASK_L8_BSHOW | PPUMASK_L8_SSHOW | PPUMASK_SSHOW | PPUMASK_BSHOW;

    APU.status = 0x0F;

    Scroll = 0;
    SplitEnable = 1;

    // infinite loop
    while (1) {
        WaitFrame();

        if(InputPort1 & BUTTON_UP) {
            if (playerY > 0) {
                --playerY;
            }
        }

        if(InputPort1 & BUTTON_DOWN) {
            if (playerY < 240) {
                ++playerY;
            }
        }

        if(InputPort1 & BUTTON_LEFT) {
            if (playerSpeedX > -8) {
                --playerSpeedX;
            }
        } else if(InputPort1 & BUTTON_RIGHT) {
            if (playerSpeedX < 8) {
                ++playerSpeedX;
            }
        } else if(playerSpeedX > 0) {
            --playerSpeedX;
        } else if(playerSpeedX < 0) {
            ++playerSpeedX;
        }

        if(playerX < Scroll + 32 && Scroll > 0) {
            Scroll -= 2;
        }


        if(playerX > Scroll + 256 - 32 && Scroll < 256) {
            Scroll += 2;
        }

        playerX += playerSpeedX;

        // update player sprites
        relativePlayerX = playerX - Scroll;
        playerYOffset = (FrameCount & 0x07);
        playerSprites[0].x = relativePlayerX; playerSprites[0].y = playerY + playerYOffset; playerSprites[0].tile_index = ((FrameCount >> 3) & 0x01) ? 0x00 : 0x02;
        playerSprites[1].x = relativePlayerX + 8; playerSprites[1].y = playerY + playerYOffset; playerSprites[1].tile_index = playerSprites[0].tile_index + 0x01;
        playerSprites[2].x = relativePlayerX; playerSprites[2].y = playerY + 8 + playerYOffset; playerSprites[2].tile_index = playerSprites[0].tile_index + 0x10;
        playerSprites[3].x = relativePlayerX + 8; playerSprites[3].y = playerY + 8 + playerYOffset; playerSprites[3].tile_index = playerSprites[0].tile_index + 0x11;

        // tells the NMI to update
        VRAMUpdateReady = 1;
    }   
};
