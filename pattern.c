#include <gb/gb.h>

static UINT8* pattern_strip(UINT8* data) {
    UINT8 i;
    for(i = 0; i < 32; i++)
        *data++ = 0xFF;
    for(i = 0; i < 16; i++) {
        *data++ = 0x00;
        *data++ = 0xFF;
    }
    for(i = 0; i < 16; i++) {
        *data++ = 0xFF;
        *data++ = 0x00;
    }
    for(i = 0; i < 32; i++)
        *data++ = 0x00;
    return data;
}

static UINT8* pattern_cross(UINT8* data, UINT8 color0, UINT8 color1, UINT8 color2, UINT8 color3, UINT8 is_reversed) {
    UINT8 i, j;
    for(i = 0; i < 4; i++) {
        if(!is_reversed) {
            for(j = 0; j < 16; j++)
                *data++ = 0x00;
        }

        for(j = 0; j < 4; j++) {
            *data++ = color0;
            *data++ = color1;
            *data++ = color2;
            *data++ = color3;
        }

        if(is_reversed) {
            for(j = 0; j < 16; j++)
                *data++ = 0x00;
        }
    }
    return data;
}

static UINT8* pattern_border_horizontal(UINT8* data) {
    UINT16 i;
    for(i = 0; i < 320; i++)
        *data++ = 0xFF;
    return data;
}

static UINT8* pattern_border_vertical(UINT8* data) {
    UINT8 i;
    for(i = 0; i < 32; i++)
        *data++ = 0xFF;
    return data;
}

void generate_pattern(UINT8* data, UINT8 line) {
    switch(line) {
        case 0:
            data = pattern_border_horizontal(data);
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x55, 0x00, 0xAA, 0x00, 0);
            data = pattern_strip(data);
            data = pattern_border_vertical(data);
           break;
        case 2:
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x55, 0x00, 0xAA, 0x00, 1);
            data = pattern_strip(data);
            data = pattern_border_vertical(data);
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x00, 0x55, 0x00, 0xAA, 0);
            data = pattern_border_vertical(data);
            break;
        case 4:
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x00, 0x55, 0x00, 0xAA, 1);
            data = pattern_strip(data);
            data = pattern_border_vertical(data);
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x55, 0x55, 0xAA, 0xAA, 0);
            data = pattern_border_vertical(data);
            break;
        case 6:
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x55, 0x55, 0xAA, 0xAA, 1);
            data = pattern_strip(data);
            data = pattern_border_vertical(data);
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0xFF, 0x00, 0xFF, 0x00, 0);
            data = pattern_border_vertical(data);
            break;
        case 8:
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0xFF, 0x00, 0xFF, 0x00, 1);
            data = pattern_strip(data);
            data = pattern_border_vertical(data);
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x00, 0xFF, 0x00, 0xFF, 0);
            data = pattern_border_vertical(data);
            break;
        case 10:
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0x00, 0xFF, 0x00, 0xFF, 1);
            data = pattern_strip(data);
            data = pattern_border_vertical(data);
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0xFF, 0xFF, 0xFF, 0xFF, 0);
            data = pattern_border_vertical(data);
            break;
        case 12:
            data = pattern_border_vertical(data);
            data = pattern_cross(data, 0xFF, 0xFF, 0xFF, 0xFF, 1);
            data = pattern_strip(data);
            data = pattern_border_vertical(data);
            data = pattern_border_horizontal(data);
            break;
    }
}

