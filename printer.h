#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <gb/gb.h>

// status flags
#define PRINTER_STATUS_CHECKSUM_INVALID 0x01
#define PRINTER_STATUS_PRINTING         0x02
#define PRINTER_STATUS_DATA_FULL        0x04
#define PRINTER_STATUS_UNPROCESSED_DATA 0x08
#define PRINTER_STATUS_PACKET_ERROR     0x10
#define PRINTER_STATUS_PAPER_JAM        0x20
#define PRINTER_STATUS_OTHER_ERROR      0x40
#define PRINTER_STATUS_LOW_BATTERY      0x80

// statuses considered an error
#define PRINTER_STATUS_ERROR            0b01110101

#define COMPRESSION_NONE                0x00
#define COMPRESSION_RLE                 0x01

INT8 print(char text[14][20]);
void generate_pattern(UINT8* data, UINT8 line);

#endif

