#include <gb/gb.h>
#include <gb/drawing.h>

// status flags
#define PRINTER_STATUS_CHECKSUM_INVALID 0x01
#define PRINTER_STATUS_PRINTING         0x02
#define PRINTER_STATUS_DATA_FULL        0x04
#define PRINTER_STATUS_READY_TO_PRINT   0x08
#define PRINTER_STATUS_PACKET_ERROR     0x10
#define PRINTER_STATUS_PAPER_JAM        0x20
#define PRINTER_STATUS_OTHER_ERROR      0x40
#define PRINTER_STATUS_LOW_BATTERY      0x80

#define COMPRESSION_NONE                0x00
#define COMPRESSION_RLE                 0x01

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
    0x01, 0x13, 0xE4, 0x40, // unknown, margins, palette, exposure
    0x3E, 0x01  // checksum
};

UINT16 rle_compress(const UINT8 *in_buf, UINT16 in_len, UINT8* out_buf) {
    UINT8 repeat = 0;
    UINT16 in_idx = 0, out_idx = 0, i;
    INT16 no_repeat_start = -1;

    if(in_len == 0)
        return 0;

    if(in_len == 1) {
        out_buf[0] = 0x00;
        out_buf[1] = in_buf[0];
        return 2;
    }

    for(in_idx = 1; in_idx < in_len; in_idx++) {
        if(in_buf[in_idx] == in_buf[in_idx - 1]) {
            repeat++;
            if(no_repeat_start != -1) {
                out_buf[out_idx++] = in_idx - no_repeat_start - 1;
                for(i = no_repeat_start; i < in_idx - 1; i++)
                    out_buf[out_idx++] = in_buf[i];
                no_repeat_start = -1;
            }
        } else if(in_buf[in_idx] != in_buf[in_idx - 1]) {
            if(repeat > 0) {
                out_buf[out_idx++] = 0x80 | (repeat - 1);
                out_buf[out_idx++] = in_buf[in_idx - 1];
                repeat = 0;
            } else {
                if(no_repeat_start == -1)
                    no_repeat_start = in_idx - 1;
            }
        }

        if(repeat == 128) {
            out_buf[out_idx++] = 0x80 | (repeat - 1);
            out_buf[out_idx++] = in_buf[in_idx - 1];
            repeat = 0;
        } else if(no_repeat_start != -1 && in_idx - no_repeat_start == 128) {
            out_buf[out_idx++] = 127;
            for(i = no_repeat_start; i < in_idx - 1; i++)
                out_buf[out_idx++] = in_buf[i];
            no_repeat_start = -1;
        }
    }

    if(repeat > 0) {
        out_buf[out_idx++] = 0x80 | (repeat - 1);
        out_buf[out_idx++] = in_buf[in_len - 1];
    } else if(no_repeat_start != -1) {
        out_buf[out_idx++] = in_len - no_repeat_start - 1;
        for(i = no_repeat_start; i < in_len; i++)
            out_buf[out_idx++] = in_buf[i];
    }

    return out_idx;
}

UINT8 serial_send_recv(UINT8 b) {
    SB_REG = b;
    SC_REG = 0x81;
    while(SC_REG & 0x80);
    return SB_REG;
}

UINT8 printer_cmd(UINT8* cmd) {
    UINT8 len = *cmd++;
    // received bytes should be 0x00, no point in checking them
    while(len--)
        serial_send_recv(*cmd++);

    // alive indicator, should return 0x80 or 0x81
    if((serial_send_recv(0) & 0xF0) != 0x80)
        return 0xFF;

    // status, should return 0x00
    return serial_send_recv(0);
}

UINT8 printer_data(UINT16 len, UINT8* data, UINT8 compression) {
    //UINT8 rle[1280]; // could be done in-place, separate buffer takes a lot RAM, but we don't care for test ROM
    UINT16 chksum = 0x04;

    // doesn't work with emulators, no real hw to test
    //if(compression == COMPRESSION_RLE) {
    //    len = rle_compress(data, len, rle);
    //    data = rle;
    //}

    serial_send_recv(0x88); // magic
    serial_send_recv(0x33);
    serial_send_recv(0x04); // command
    serial_send_recv(compression); // compression

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

    // keepalive, should return 0x80 or 0x81
    if((serial_send_recv(0) & 0xF0) != 0x80)
        return 0x40; // other error code, to indicate error

    // status, should return 0x00
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

INT8 get_lines_count(void) {
    UINT8 count = 0;
    INT8  line, col;
    for(line = 13; line >= 0; line--)
        for(col = 0; col < 20; col++)
            if(text[line][col] != ' ')
                return line;
    return 0;
}

INT8 print(void) {
    UINT8 line, col, lines, i, status;
    UINT8 pix[640], *tmp1;
    const UINT8* tmp2;

    // clean printer RAM
    if(printer_cmd(PRINTER_INIT) != 0x00)
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

        // only printing ready and low battery accepted
        if((status = (printer_data(640, pix, COMPRESSION_NONE) & 0b01110111)) != 0x00)
            return -2;
    }

    // ask status, expect ready to print
    if((printer_cmd(PRINTER_STATUS) & PRINTER_STATUS_READY_TO_PRINT) != PRINTER_STATUS_READY_TO_PRINT)
        return -3;

    // send "EOF", status should be still ready to print
    if((printer_data(0, (UINT8*) 0, COMPRESSION_NONE) & PRINTER_STATUS_READY_TO_PRINT) != PRINTER_STATUS_READY_TO_PRINT)
        return -4;

    // send start print command, status should be still ready to print
    if((printer_cmd(PRINTER_PRINT) & PRINTER_STATUS_READY_TO_PRINT) != PRINTER_STATUS_READY_TO_PRINT)
        return -5;

    // keep checking until printing in progress bit clear
    while((printer_cmd(PRINTER_STATUS) & PRINTER_STATUS_PRINTING) == PRINTER_STATUS_PRINTING);

    // final check for status
    if((printer_cmd(PRINTER_STATUS) & PRINTER_STATUS_DATA_FULL) != PRINTER_STATUS_DATA_FULL)
        return -6;

    return 0;
}

void main(void) {
    UINT8 keys;
    INT8 status;

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
            status = print();
            wait_vbl_done();
            if(status < 0) {
                set_bkg_tile_xy(0, 14, 'E');
                set_bkg_tile_xy(1, 14, '0'-status);
            } else {
                set_bkg_tiles(0, 14, 2, 1, "  ");
                clear();
            }
        }
        while(joypad() != 0); // don't use waitpadup(), it works weird
        __asm__("halt"); // power saving mode
    }
}

