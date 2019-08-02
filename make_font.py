#!/usr/bin/env python3

from PIL import Image

if __name__ == '__main__':
    s = '#ifndef __FONT_H__\n#define __FONT_H__\n\nstatic const UINT8 FONT[0x80*16] = {\n'
    png = Image.open('ibmpc8x8.png')
    for c in range(0x80):
        s += '    '
        x0 = (c % 16) * 8 
        y0 = (c // 16) * 8
        for y in range(y0, y0 + 8):
            val = 0
            for x in range(x0, x0 + 8):
                val <<= 1
                if png.getpixel((x, y)) == 9:
                    val |= 1
            s += '0x{:02X}, 0x{:02X}, '.format(val, val)
        if c >= 0x20:
            s += '/* 0x{:02X} ({:1c}) */\n'.format(c,c)
        else:
            s += '/* 0x{:02X} */\n'.format(c)
    s += '};\n#endif\n\n'
    print(s)        

