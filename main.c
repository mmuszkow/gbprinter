#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/drawing.h>
#include "printer.h"
#include "font.h"

// text currently on screen
static char text[14][20], c;
static UINT8 text_x = 0, text_y = 0;

static const char KEYB_UPPER[4][12] = {
    { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=' },
    { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']' },
    { 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '\\' },
    { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', ' ', '\n' }
};
static const char KEYB_LOWER[4][12] = {
    { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+' },
    { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}' },
    { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ':', '"', '|' },
    { 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<', '>', '?', ' ', '\n' }
};
static UINT8 keyb_is_upper = 1;

// position of selection cursor on screen in pixels
// visible screen starts at (40, 128) 
static UINT8 cursor_x = 40, cursor_y = 128;

static const UINT8 CURSORS[32] = {
    // selection cursor
    0xC3, 0xC3, 0x81, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0xC3, 0xC3,
    // current position cursor
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF
};

void clear(void) {
    for(text_y = 0; text_y < 14; text_y++)
        for(text_x = 0; text_x < 20; text_x++)
            text[text_y][text_x] = ' ';
    text_x = 0;
    text_y = 0;

    wait_vbl_done(); 
    set_bkg_tiles(0, 0, 20, 14, (char*) text);
    move_sprite(1, 8, 16);
}

void main(void) {
    UINT8 keys;
    INT8 status;

    disable_interrupts();

    DISPLAY_OFF;
    set_bkg_data(0x00, 0x80, FONT);
    set_bkg_tiles(4, 14, 12, 4, (char*) KEYB_UPPER);
    if(_cpu == CGB_TYPE) {
        set_bkg_palette(0, 1, CGB_TILE_PALETTE);
        set_sprite_palette(0, 1, CGB_SPRITE_PALETTE);
    }

    SPRITES_8x8;
    set_sprite_data(0, 2, CURSORS);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    move_sprite(0, cursor_x, cursor_y);
    move_sprite(1, 8, 16);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    enable_interrupts();

    clear(); 
    while(1) {
        keys = joypad();
        if((keys & J_UP) && cursor_y > 128) {
            cursor_y -= 8;
            move_sprite(0, cursor_x, cursor_y);
        } else if((keys & J_DOWN) && cursor_y < 152) {
            cursor_y += 8;
            move_sprite(0, cursor_x, cursor_y);
        } else if((keys & J_LEFT) && cursor_x > 40) {
            cursor_x -= 8;
            move_sprite(0, cursor_x, cursor_y);
        } else if((keys & J_RIGHT) && cursor_x < 128) {
            cursor_x += 8;
            move_sprite(0, cursor_x, cursor_y);
        } else if(keys & J_A) {
            // A = put letter
            if(text_x < 20 && text_y < 14) {
                // get key under cursor
                if(keyb_is_upper)
                    c = KEYB_UPPER[(cursor_y - 128) >> 3][(cursor_x - 40) >> 3];
                else
                    c = KEYB_LOWER[(cursor_y - 128) >> 3][(cursor_x - 40) >> 3];
                
                if(c != '\n') {
                    text[text_y][text_x] = c;
                    wait_vbl_done();
                    set_bkg_tiles(text_x, text_y, 1, 1, &c);
                
                    if(text_x == 19) {
                        text_x = 0;
                        text_y++;;
                    } else
                        text_x++;
                } else if(text_y < 13) {
                    text_x = 0;
                    text_y++;
                }
                move_sprite(1, (text_x << 3) + 8, (text_y << 3) + 16);
            }
        } else if(keys & J_B) {
            // B = backspace
            if(text_x > 0)
                text_x--;
            else if(text_x == 0 && text_y > 0) {
                text_x = 19;
                text_y--;
            }
            c = ' ';
            text[text_y][text_x] = c;
            wait_vbl_done();
            set_bkg_tiles(text_x, text_y, 1, 1, &c);
            move_sprite(1, (text_x << 3) + 8, (text_y << 3) + 16);
        } else if(keys & J_SELECT) {
            // SELECT = Shift/Caps Lock key
            keyb_is_upper = !keyb_is_upper;
            wait_vbl_done();
            if(keyb_is_upper)
                set_bkg_tiles(4, 14, 12, 4, (char*) KEYB_UPPER);
            else
                set_bkg_tiles(4, 14, 12, 4, (char*) KEYB_LOWER);
        } else if(keys & J_START) {
            // START = print
            status = print(text);
            wait_vbl_done();
            if(status < 0) {
                set_bkg_tile_xy(0, 14, 'E');
                set_bkg_tile_xy(1, 14, '0'-status);
            } else {
                set_bkg_tiles(0, 14, 2, 1, "  ");
                set_bkg_tiles(0, 15, 2, 1, "  ");
                clear();
            }
        }
        while(joypad() != 0); // don't use waitpadup(), it works weird
        __asm__("halt"); // power saving mode
    }
}

