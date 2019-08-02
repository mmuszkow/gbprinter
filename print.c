#include <gb/gb.h>
#include <gb/drawing.h>

static const UINT8 PRINTER_INIT[] = {
    8,          // length
    0x88, 0x33, // magic
    0x01,       // command
    0x00,       // compression
    0x00, 0x00, // data length
                // no data
    0x01, 0x00  // checksum
};

static const UINT8 PRINTER_STATUS[] = {
    8,          // length
    0x88, 0x33, // magic
    0x0F,       // command
    0x00,       // compression
    0x00, 0x00, // data length
                // no data
    0x0F, 0x00  // checksum
};

static const UINT8 PRINTER_PRINT[] = {
    12,         // length
    0x88, 0x33, // magic
    0x02,       // command
    0x00,       // compression
    0x04, 0x00, // data length
    0x01, 0x13, 0xE4, 0x40, // margins, palette, exposure
    0x3E, 0x01  // checksum
};

UINT8 serial_send_recv(UINT8 b) {
    SB_REG = b;
    SC_REG = 0x81;
    while(SC_REG & 0x80);
    return SB_REG;
}

// returns status code
UINT8 printer_cmd(UINT8* cmd) {
    UINT8 len = *cmd++;
    // received bytes should be 0x00, no point in checking them
    while(len--)
        serial_send_recv(*cmd++);

    // alive indicator
    if((serial_send_recv(0) & 0xF0) != 0x80)
        return 0xFF;

    // status
    return serial_send_recv(0);
}

UINT8 printer_data(UINT16 len, UINT8* data) {
    UINT16 chksum = 0x04;

    serial_send_recv(0x88); // magic
    serial_send_recv(0x33);
    serial_send_recv(0x04); // command
    serial_send_recv(0x00); // compression

    // data length
    serial_send_recv((UINT8) len);
    serial_send_recv((UINT8) (len >> 8));
    chksum += len & 0xFF;
    chksum += len >> 8;

    while(len--) {
        chksum += *data;
        serial_send_recv(*data++);
    }

    // checksum
    serial_send_recv((UINT8) chksum);
    serial_send_recv((UINT8) (chksum >> 8));

    // keepalive
    if((serial_send_recv(0) & 0xF0) != 0x80)
        return 0x60;

    // status
    return serial_send_recv(0);
}

// text currently on screen
static char text[14][20], c;
static UINT8 text_x = 0, text_y = 0;

#include "font.h"

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

INT8 get_lines_count() {
    UINT8 count = 0;
    INT8  line, col;
    for(line = 13; line >= 0; line--)
        for(col = 0; col < 20; col++)
            if(text[line][col] != ' ')
                return line;
    return 0;
}

INT8 print() {
    UINT8 line, col, lines, i;
    UINT8 status;
    UINT8 pix[640], *tmp1;
    const UINT8* tmp2;

    // clean printer RAM
    if(printer_cmd(PRINTER_INIT) != 0)
        return -1;

    // the number of lines must be even to get 640 bytes
    lines = ((get_lines_count() >> 1) + 1) << 1;

    for(line = 0; line < lines; line += 2) {
        tmp1 = pix;
        for(col=0; col<20; col++) {
            tmp2 = &FONT[text[line][col]<<4]; // times 16 as each char is 16 bytes
            for(i = 0; i < 16; i++)
                *tmp1++ = *tmp2++;
        }
        for(col=0; col<20; col++) {
            tmp2 = &FONT[text[line+1][col]<<4]; // times 16 as each char is 16 bytes
            for(i = 0; i < 16; i++)
                *tmp1++ = *tmp2++;
        }

        if(printer_data(640, pix) != 0x08) // TODO: this should (could?) return 0?
            return -2;
    }

    // ask status, expect 0x08 status (ready to print)
    if(printer_cmd(PRINTER_STATUS) != 0x08)
        return -3;

    // send "EOF", status should be still 0x08
    if(printer_data(0, (UINT8*) 0) != 0x08)
        return -4;

    // send start print command, status should be still 0x08
    if(printer_cmd(PRINTER_PRINT) != 0x08)
        return -5;

    // keep checking until status changes from 0x06 (printing)
    while(printer_cmd(PRINTER_STATUS) == 0x06);

    // check if status is 0x04 (printing done)
    if(printer_cmd(PRINTER_STATUS) != 0x00) // TODO: this should (could?) return 0x04?
        return -6;

    return 0;
}

void main(void) {
    UINT8 keys;

    disable_interrupts();

    DISPLAY_OFF;
    set_bkg_data(0x00, 0x80, FONT);
    set_bkg_tiles(4, 14, 12, 4, (char*) KEYB_UPPER);

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
            disable_interrupts();
            if(print() != 0) {
                wait_vbl_done();
                set_bkg_tiles(0, 14, 3, 1, "ERR");
            } else {
                wait_vbl_done();
                set_bkg_tiles(0, 14, 3, 1, "   ");
                clear();
            }
            enable_interrupts();
        }
        waitpadup();
        __asm__("halt"); // power saving mode
    }
}

