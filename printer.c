#include <gb/gb.h>
#include <gb/drawing.h>
#include "printer.h"
#include "font.h"

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

static UINT16 rle_compress(const UINT8 *in_buf, UINT16 in_len, UINT8* out_buf) {
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

static UINT8 serial_send_recv(UINT8 b) {
    UINT16 timeout = 65000; // ~100ms
    SB_REG = b;
    SC_REG = 0x81;
    while(--timeout && (SC_REG & 0x80));
    return timeout ? SB_REG : 0xFF;
}

static UINT8 printer_cmd(UINT8* cmd) {
    UINT8 len = *cmd++;
    // received bytes should be 0x00, no point in checking them
    while(len--)
        serial_send_recv(*cmd++);

    // alive indicator, should return 0x80 or 0x81
    if((serial_send_recv(0) & 0xF0) != 0x80)
        return 0xFF;

    // status
    return serial_send_recv(0);
}

static UINT8 printer_data(UINT16 len, UINT8* data, UINT8 compression) {
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
        return 0xFF;

    // status, should return 0x00
    return serial_send_recv(0);
}

static UINT8 get_lines_count(char text[14][20]) {
    UINT8 count = 0;
    INT8 line, col;
    for(line = 13; line >= 0; line--)
        for(col = 0; col < 20; col++)
            if(text[line][col] != ' ')
                return line;
    return 0;
}

static void show_hex(UINT8 val) {
    UINT8 hi = val >> 4;
    UINT8 lo = val & 0xF;
    wait_vbl_done();
    if(hi < 10)
        set_bkg_tile_xy(0, 15, '0'+hi);
    else
        set_bkg_tile_xy(0, 15, 'A'+hi-10);
    if(lo < 10)
        set_bkg_tile_xy(1, 15, '0'+lo);
    else
        set_bkg_tile_xy(1, 15, 'A'+lo-10);
}

INT8 print(char text[14][20]) {
    UINT8 line, col, lines, i, pix[640], *tmp1, status, is_pattern;
    UINT16 timeout, delay;
    const UINT8* tmp2;

    wait_vbl_done();
    set_bkg_tiles(0, 14, 2, 1, "  ");
    set_bkg_tiles(0, 15, 2, 1, "  ");
    set_bkg_tile_xy(0, 14, 'P');

    // the number of lines must be even to get 640 bytes
    lines = ((get_lines_count(text) >> 1) + 1) << 1;

    // clean printer RAM
    status = printer_cmd(PRINTER_INIT);
    if(status != 0x00) {
        show_hex(status);
        return -1;
    }

    // check whether to print pattern or on-screen text
    is_pattern = text[0][0] == 'P' && text[0][1] == 'A' && text[0][2] == 'T';
    if(is_pattern)
        lines = 14;

    // send data to the printer in 640 bytes buffers
    for(line = 0; line < lines; line += 2) {
        if(is_pattern) {
            generate_pattern(pix, line);
        } else {
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
        }

        // send data
        status = printer_data(640, pix, COMPRESSION_NONE);
        if(status & PRINTER_STATUS_ERROR) {
            show_hex(status);
            return -2;
        }

        // check for errors, Pokemon Yellow does that
        status = printer_cmd(PRINTER_STATUS);
        if(status & PRINTER_STATUS_ERROR) {
            show_hex(status);
            return -3;
        }
    }

    // send "EOF"
    status = printer_data(0, (UINT8*) 0, COMPRESSION_NONE);
    if(status & PRINTER_STATUS_ERROR) {
        show_hex(status);
        return -4;
    }

    // perform final check for errors
    status = printer_cmd(PRINTER_STATUS);
    if(status & PRINTER_STATUS_ERROR) {
        show_hex(status);
        return -5;
    }

    // send start print command & keep checking until printing in progress bit clear
    printer_cmd(PRINTER_PRINT);
    timeout = 20000; // ~30secs
    while(--timeout) {
        status = printer_cmd(PRINTER_STATUS);
        if(!(status & PRINTER_STATUS_PRINTING))
            break;

        // ~1.5ms delay
        delay = 1000;
        while(--delay);
    }
    if(timeout == 0) {
        show_hex(status);
        return -6;
    }

    return 0;
}

