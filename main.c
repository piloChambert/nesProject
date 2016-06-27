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
#define PPUCTRL_SSIZE_16x16 0x20 // 16x16 sprite size
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
uint8_t inputPort1Old = 0;
#pragma zpsym("InputPort1");

extern uint8_t InputPort1Prev;
#pragma zpsym("InputPort1Prev");

extern uint8_t InputPort2;
#pragma zpsym("InputPort2");

extern uint8_t InputPort2Prev;
#pragma zpsym("InputPort2Prev");

void WaitFrame(void);

#pragma bss-name(push, "ZEROPAGE")
size_t i, x, y;
#pragma bss-name(pop)

#pragma bss-name(push, "OAM")
sprite_t player;
#pragma bss-name(pop)


const char TEXT[] = "Hello, World!";

const uint8_t PALETTE[] = { 0x0F, 0x00, 0x10, 0x20,
                            0x0F, 0x11, 0x21, 0x31,
                            0x0F, 0x15, 0x25, 0x35,
                            0x0F, 0x19, 0x29, 0x39,
                            0x0F, 0x06, 0x15, 0x36,
                            0x0F, 0x11, 0x21, 0x31,
                            0x0F, 0x15, 0x25, 0x35,
                            0x0F, 0x19, 0x29, 0x39 };

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

    // load the text sprites into the background (nametable 0)
    // nametable 0 is VRAM $2000-$23ff, so we'll choose an address in the
    // middle of the screen. The screen can hold a 32x30 grid of 8x8 sprites,
    // so an offset of 0x1ca (X: 10, Y:14) puts us around the middle vertically
    // and roughly centers our text horizontally.
    PPU.vram.address = 0x20;
    PPU.vram.address = 0x20;
    for ( i = 0; i < 1024; ++i ) {
        x = i & 0X0F;
        y = (i >> 5) & 0x0F;
        PPU.vram.data = (uint8_t)(x + (y << 4));
    }

    // set color
    PPU.vram.address = 0x23;
    PPU.vram.address = 0xC0;
    for(i = 0; i < 64; i++) {
        PPU.vram.data = i & 0x0F;
    }

    player.x = 20;
    player.y = 20;
    player.tile_index = 0x0;


    // reset scroll location to top-left of screen
    PPU.scroll = 0x00;
    PPU.scroll = 0x00;

    // enable NMI and rendering
    PPU.control = PPUCTRL_NAMETABLE_0 | PPUCTRL_INC_1_HORIZ | PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_1 | PPUCTRL_NMI_ON;
    PPU.mask = PPUMASK_COLOR | PPUMASK_L8_BSHOW | PPUMASK_L8_SSHOW | PPUMASK_SSHOW | PPUMASK_BSHOW;

    APU.status = 0x0F;

    // infinite loop
    while (1) {
        WaitFrame();

        // reset scroll
        PPU.scroll = 0x00;
        PPU.scroll = 0x00;

        if (InputPort1 & BUTTON_UP) {
            if (player.y > 0) {
                --player.y;

                if(!(inputPort1Old & BUTTON_UP)) {
                    APU.pulse[0].control = 0x0F;
                    APU.pulse[0].ramp = 0x01;
                    APU.pulse[0].period_low = 0x05;
                    APU.pulse[0].len_period_high = (0x0F << 5) + 0x01;
                }
            }
        }

        if (InputPort1 & BUTTON_DOWN) {
            if (player.y < 255) {
                ++player.y;
            }
        }

        if (InputPort1 & BUTTON_LEFT) {
            if (player.x > 0) {
                --player.x;
            }
        }

        if (InputPort1 & BUTTON_RIGHT) {
            if (player.x < 255) {
                ++player.x;
            }
        }

        inputPort1Old = InputPort1;
    }   
};
