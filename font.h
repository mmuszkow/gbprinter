#ifndef __FONT_H__
#define __FONT_H__

static const UINT8 FONT[0x80*16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00 */
    0x7E, 0x7E, 0x81, 0x81, 0xA5, 0xA5, 0x81, 0x81, 0xBD, 0xBD, 0x99, 0x99, 0x81, 0x81, 0x7E, 0x7E, /* 0x01 */
    0x7E, 0x7E, 0xFF, 0xFF, 0xDB, 0xDB, 0xFF, 0xFF, 0xC3, 0xC3, 0xE7, 0xE7, 0xFF, 0xFF, 0x7E, 0x7E, /* 0x02 */
    0x6C, 0x6C, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x7C, 0x7C, 0x38, 0x38, 0x10, 0x10, 0x00, 0x00, /* 0x03 */
    0x10, 0x10, 0x38, 0x38, 0x7C, 0x7C, 0xFE, 0xFE, 0x7C, 0x7C, 0x38, 0x38, 0x10, 0x10, 0x00, 0x00, /* 0x04 */
    0x38, 0x38, 0x7C, 0x7C, 0x38, 0x38, 0xFE, 0xFE, 0xFE, 0xFE, 0x54, 0x54, 0x38, 0x38, 0x7C, 0x7C, /* 0x05 */
    0x10, 0x10, 0x10, 0x10, 0x38, 0x38, 0x7C, 0x7C, 0xFE, 0xFE, 0x7C, 0x7C, 0x38, 0x38, 0x7C, 0x7C, /* 0x06 */
    0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x3C, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, /* 0x07 */
    0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xE7, 0xC3, 0xC3, 0xC3, 0xC3, 0xE7, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, /* 0x08 */
    0x00, 0x00, 0x3C, 0x3C, 0x66, 0x66, 0x42, 0x42, 0x42, 0x42, 0x66, 0x66, 0x3C, 0x3C, 0x00, 0x00, /* 0x09 */
    0xFF, 0xFF, 0xC3, 0xC3, 0x99, 0x99, 0xBD, 0xBD, 0xBD, 0xBD, 0x99, 0x99, 0xC3, 0xC3, 0xFF, 0xFF, /* 0x0A */
    0x0F, 0x0F, 0x07, 0x07, 0x0F, 0x0F, 0x7D, 0x7D, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, /* 0x0B */
    0x3C, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x3C, 0x18, 0x18, 0x7E, 0x7E, 0x18, 0x18, /* 0x0C */
    0x3F, 0x3F, 0x33, 0x33, 0x3F, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x70, 0x70, 0xF0, 0xF0, 0xE0, 0xE0, /* 0x0D */
    0x7F, 0x7F, 0x63, 0x63, 0x7F, 0x7F, 0x63, 0x63, 0x63, 0x63, 0x67, 0x67, 0xE6, 0xE6, 0xC0, 0xC0, /* 0x0E */
    0x99, 0x99, 0x5A, 0x5A, 0x3C, 0x3C, 0xE7, 0xE7, 0xE7, 0xE7, 0x3C, 0x3C, 0x5A, 0x5A, 0x99, 0x99, /* 0x0F */
    0x80, 0x80, 0xE0, 0xE0, 0xF8, 0xF8, 0xFE, 0xFE, 0xF8, 0xF8, 0xE0, 0xE0, 0x80, 0x80, 0x00, 0x00, /* 0x10 */
    0x02, 0x02, 0x0E, 0x0E, 0x3E, 0x3E, 0xFE, 0xFE, 0x3E, 0x3E, 0x0E, 0x0E, 0x02, 0x02, 0x00, 0x00, /* 0x11 */
    0x18, 0x18, 0x3C, 0x3C, 0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x7E, 0x3C, 0x3C, 0x18, 0x18, /* 0x12 */
    0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, /* 0x13 */
    0x7F, 0x7F, 0xDB, 0xDB, 0xDB, 0xDB, 0x7B, 0x7B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, /* 0x14 */
    0x3E, 0x3E, 0x63, 0x63, 0x38, 0x38, 0x6C, 0x6C, 0x6C, 0x6C, 0x38, 0x38, 0xCC, 0xCC, 0x78, 0x78, /* 0x15 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00, 0x00, /* 0x16 */
    0x18, 0x18, 0x3C, 0x3C, 0x7E, 0x7E, 0x18, 0x18, 0x7E, 0x7E, 0x3C, 0x3C, 0x18, 0x18, 0xFF, 0xFF, /* 0x17 */
    0x18, 0x18, 0x3C, 0x3C, 0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, /* 0x18 */
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x7E, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x00, /* 0x19 */
    0x00, 0x00, 0x18, 0x18, 0x0C, 0x0C, 0xFE, 0xFE, 0x0C, 0x0C, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, /* 0x1A */
    0x00, 0x00, 0x30, 0x30, 0x60, 0x60, 0xFE, 0xFE, 0x60, 0x60, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, /* 0x1B */
    0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, /* 0x1C */
    0x00, 0x00, 0x24, 0x24, 0x66, 0x66, 0xFF, 0xFF, 0x66, 0x66, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, /* 0x1D */
    0x00, 0x00, 0x18, 0x18, 0x3C, 0x3C, 0x7E, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, /* 0x1E */
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, /* 0x1F */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20 ( ) */
    0x30, 0x30, 0x78, 0x78, 0x78, 0x78, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, /* 0x21 (!) */
    0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x22 (") */
    0x6C, 0x6C, 0x6C, 0x6C, 0xFE, 0xFE, 0x6C, 0x6C, 0xFE, 0xFE, 0x6C, 0x6C, 0x6C, 0x6C, 0x00, 0x00, /* 0x23 (#) */
    0x30, 0x30, 0x7C, 0x7C, 0xC0, 0xC0, 0x78, 0x78, 0x0C, 0x0C, 0xF8, 0xF8, 0x30, 0x30, 0x00, 0x00, /* 0x24 ($) */
    0x00, 0x00, 0xC6, 0xC6, 0xCC, 0xCC, 0x18, 0x18, 0x30, 0x30, 0x66, 0x66, 0xC6, 0xC6, 0x00, 0x00, /* 0x25 (%) */
    0x38, 0x38, 0x6C, 0x6C, 0x38, 0x38, 0x76, 0x76, 0xDC, 0xDC, 0xCC, 0xCC, 0x76, 0x76, 0x00, 0x00, /* 0x26 (&) */
    0x60, 0x60, 0x60, 0x60, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x27 (') */
    0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x00, 0x00, /* 0x28 (() */
    0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x00, 0x00, /* 0x29 ()) */
    0x00, 0x00, 0x66, 0x66, 0x3C, 0x3C, 0xFF, 0xFF, 0x3C, 0x3C, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, /* 0x2A (*) */
    0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0xFC, 0xFC, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, /* 0x2B (+) */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x60, 0x60, /* 0x2C (,) */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x2D (-) */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, /* 0x2E (.) */
    0x06, 0x06, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, /* 0x2F (/) */
    0x38, 0x38, 0x6C, 0x6C, 0xC6, 0xC6, 0xD6, 0xD6, 0xC6, 0xC6, 0x6C, 0x6C, 0x38, 0x38, 0x00, 0x00, /* 0x30 (0) */
    0x30, 0x30, 0x70, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xFC, 0xFC, 0x00, 0x00, /* 0x31 (1) */
    0x78, 0x78, 0xCC, 0xCC, 0x0C, 0x0C, 0x38, 0x38, 0x60, 0x60, 0xCC, 0xCC, 0xFC, 0xFC, 0x00, 0x00, /* 0x32 (2) */
    0x78, 0x78, 0xCC, 0xCC, 0x0C, 0x0C, 0x38, 0x38, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x33 (3) */
    0x1C, 0x1C, 0x3C, 0x3C, 0x6C, 0x6C, 0xCC, 0xCC, 0xFE, 0xFE, 0x0C, 0x0C, 0x1E, 0x1E, 0x00, 0x00, /* 0x34 (4) */
    0xFC, 0xFC, 0xC0, 0xC0, 0xF8, 0xF8, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x35 (5) */
    0x38, 0x38, 0x60, 0x60, 0xC0, 0xC0, 0xF8, 0xF8, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x36 (6) */
    0xFC, 0xFC, 0xCC, 0xCC, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, /* 0x37 (7) */
    0x78, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x38 (8) */
    0x78, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x7C, 0x0C, 0x0C, 0x18, 0x18, 0x70, 0x70, 0x00, 0x00, /* 0x39 (9) */
    0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, /* 0x3A (:) */
    0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x60, 0x60, /* 0x3B (;) */
    0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0xC0, 0xC0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x00, 0x00, /* 0x3C (<) */
    0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, /* 0x3D (=) */
    0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x00, 0x00, /* 0x3E (>) */
    0x78, 0x78, 0xCC, 0xCC, 0x0C, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, /* 0x3F (?) */
    0x7C, 0x7C, 0xC6, 0xC6, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xDE, 0xC0, 0xC0, 0x78, 0x78, 0x00, 0x00, /* 0x40 (@) */
    0x30, 0x30, 0x78, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0xFC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, /* 0x41 (A) */
    0xFC, 0xFC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x7C, 0x66, 0x66, 0x66, 0x66, 0xFC, 0xFC, 0x00, 0x00, /* 0x42 (B) */
    0x3C, 0x3C, 0x66, 0x66, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x66, 0x66, 0x3C, 0x3C, 0x00, 0x00, /* 0x43 (C) */
    0xF8, 0xF8, 0x6C, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6C, 0x6C, 0xF8, 0xF8, 0x00, 0x00, /* 0x44 (D) */
    0xFE, 0xFE, 0x62, 0x62, 0x68, 0x68, 0x78, 0x78, 0x68, 0x68, 0x62, 0x62, 0xFE, 0xFE, 0x00, 0x00, /* 0x45 (E) */
    0xFE, 0xFE, 0x62, 0x62, 0x68, 0x68, 0x78, 0x78, 0x68, 0x68, 0x60, 0x60, 0xF0, 0xF0, 0x00, 0x00, /* 0x46 (F) */
    0x3C, 0x3C, 0x66, 0x66, 0xC0, 0xC0, 0xC0, 0xC0, 0xCE, 0xCE, 0x66, 0x66, 0x3A, 0x3A, 0x00, 0x00, /* 0x47 (G) */
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0xFC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, /* 0x48 (H) */
    0x78, 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x78, 0x00, 0x00, /* 0x49 (I) */
    0x1E, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x4A (J) */
    0xE6, 0xE6, 0x66, 0x66, 0x6C, 0x6C, 0x78, 0x78, 0x6C, 0x6C, 0x66, 0x66, 0xE6, 0xE6, 0x00, 0x00, /* 0x4B (K) */
    0xF0, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x62, 0x66, 0x66, 0xFE, 0xFE, 0x00, 0x00, /* 0x4C (L) */
    0xC6, 0xC6, 0xEE, 0xEE, 0xFE, 0xFE, 0xFE, 0xFE, 0xD6, 0xD6, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, /* 0x4D (M) */
    0xC6, 0xC6, 0xE6, 0xE6, 0xF6, 0xF6, 0xDE, 0xDE, 0xCE, 0xCE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, /* 0x4E (N) */
    0x7C, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x7C, 0x00, 0x00, /* 0x4F (O) */
    0xFC, 0xFC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x7C, 0x60, 0x60, 0x60, 0x60, 0xF0, 0xF0, 0x00, 0x00, /* 0x50 (P) */
    0x7C, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6, 0xDE, 0xDE, 0x7C, 0x7C, 0x0E, 0x0E, /* 0x51 (Q) */
    0xFC, 0xFC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x7C, 0x6C, 0x6C, 0x66, 0x66, 0xE6, 0xE6, 0x00, 0x00, /* 0x52 (R) */
    0x7C, 0x7C, 0xC6, 0xC6, 0xE0, 0xE0, 0x7C, 0x7C, 0x0E, 0x0E, 0xC6, 0xC6, 0x7C, 0x7C, 0x00, 0x00, /* 0x53 (S) */
    0xFC, 0xFC, 0xFC, 0xFC, 0xB4, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x78, 0x00, 0x00, /* 0x54 (T) */
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x55 (U) */
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x30, 0x30, 0x00, 0x00, /* 0x56 (V) */
    0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6, 0xD6, 0xD6, 0xFE, 0xFE, 0x6C, 0x6C, 0x00, 0x00, /* 0x57 (W) */
    0xC6, 0xC6, 0xC6, 0xC6, 0x6C, 0x6C, 0x38, 0x38, 0x6C, 0x6C, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, /* 0x58 (X) */
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x30, 0x30, 0x30, 0x30, 0x78, 0x78, 0x00, 0x00, /* 0x59 (Y) */
    0xFE, 0xFE, 0xC6, 0xC6, 0x8C, 0x8C, 0x18, 0x18, 0x32, 0x32, 0x66, 0x66, 0xFE, 0xFE, 0x00, 0x00, /* 0x5A (Z) */
    0x78, 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x78, 0x00, 0x00, /* 0x5B ([) */
    0xC0, 0xC0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0C, 0x0C, 0x06, 0x06, 0x02, 0x02, 0x00, 0x00, /* 0x5C (\) */
    0x78, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x78, 0x00, 0x00, /* 0x5D (]) */
    0x10, 0x10, 0x38, 0x38, 0x6C, 0x6C, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x5E (^) */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, /* 0x5F (_) */
    0x30, 0x30, 0x30, 0x30, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 (`) */
    0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x0C, 0x0C, 0x7C, 0x7C, 0xCC, 0xCC, 0x76, 0x76, 0x00, 0x00, /* 0x61 (a) */
    0xE0, 0xE0, 0x60, 0x60, 0x78, 0x78, 0x6C, 0x6C, 0x66, 0x66, 0x66, 0x66, 0xDC, 0xDC, 0x00, 0x00, /* 0x62 (b) */
    0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0xCC, 0xCC, 0xC0, 0xC0, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x63 (c) */
    0x1C, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x7C, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x76, 0x00, 0x00, /* 0x64 (d) */
    0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0xCC, 0xCC, 0xFC, 0xFC, 0xC0, 0xC0, 0x78, 0x78, 0x00, 0x00, /* 0x65 (e) */
    0x38, 0x38, 0x6C, 0x6C, 0x60, 0x60, 0xF0, 0xF0, 0x60, 0x60, 0x60, 0x60, 0xF0, 0xF0, 0x00, 0x00, /* 0x66 (f) */
    0x00, 0x00, 0x00, 0x00, 0x76, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x7C, 0x0C, 0x0C, 0xF8, 0xF8, /* 0x67 (g) */
    0xE0, 0xE0, 0x60, 0x60, 0x6C, 0x6C, 0x76, 0x76, 0x66, 0x66, 0x66, 0x66, 0xE6, 0xE6, 0x00, 0x00, /* 0x68 (h) */
    0x30, 0x30, 0x00, 0x00, 0x70, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x78, 0x00, 0x00, /* 0x69 (i) */
    0x0C, 0x0C, 0x00, 0x00, 0x1C, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, /* 0x6A (j) */
    0xE0, 0xE0, 0x60, 0x60, 0x66, 0x66, 0x6C, 0x6C, 0x78, 0x78, 0x6C, 0x6C, 0xE6, 0xE6, 0x00, 0x00, /* 0x6B (k) */
    0x70, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x78, 0x00, 0x00, /* 0x6C (l) */
    0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xFE, 0xFE, 0xFE, 0xFE, 0xD6, 0xD6, 0xC6, 0xC6, 0x00, 0x00, /* 0x6D (m) */
    0x00, 0x00, 0x00, 0x00, 0xDC, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, /* 0x6E (n) */
    0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x00, 0x00, /* 0x6F (o) */
    0x00, 0x00, 0x00, 0x00, 0xDC, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x7C, 0x60, 0x60, 0xF0, 0xF0, /* 0x70 (p) */
    0x00, 0x00, 0x00, 0x00, 0x76, 0x76, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x7C, 0x0C, 0x0C, 0x1E, 0x1E, /* 0x71 (q) */
    0x00, 0x00, 0x00, 0x00, 0xDC, 0xDC, 0x76, 0x76, 0x66, 0x66, 0x60, 0x60, 0xF0, 0xF0, 0x00, 0x00, /* 0x72 (r) */
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x7C, 0xC0, 0xC0, 0x78, 0x78, 0x1C, 0x1C, 0xF8, 0xF8, 0x00, 0x00, /* 0x73 (s) */
    0x10, 0x10, 0x30, 0x30, 0xFC, 0xFC, 0x30, 0x30, 0x30, 0x30, 0x36, 0x36, 0x1C, 0x1C, 0x00, 0x00, /* 0x74 (t) */
    0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x76, 0x00, 0x00, /* 0x75 (u) */
    0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x78, 0x30, 0x30, 0x00, 0x00, /* 0x76 (v) */
    0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xD6, 0xFE, 0xFE, 0xFE, 0xFE, 0x6C, 0x6C, 0x00, 0x00, /* 0x77 (w) */
    0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0x6C, 0x6C, 0x38, 0x38, 0x6C, 0x6C, 0xC6, 0xC6, 0x00, 0x00, /* 0x78 (x) */
    0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x7C, 0x7C, 0x0C, 0x0C, 0xF8, 0xF8, /* 0x79 (y) */
    0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x98, 0x98, 0x30, 0x30, 0x64, 0x64, 0xFC, 0xFC, 0x00, 0x00, /* 0x7A (z) */
    0x1C, 0x1C, 0x30, 0x30, 0x30, 0x30, 0xE0, 0xE0, 0x30, 0x30, 0x30, 0x30, 0x1C, 0x1C, 0x00, 0x00, /* 0x7B ({) */
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, /* 0x7C (|) */
    0xE0, 0xE0, 0x30, 0x30, 0x30, 0x30, 0x1C, 0x1C, 0x30, 0x30, 0x30, 0x30, 0xE0, 0xE0, 0x00, 0x00, /* 0x7D (}) */
    0x76, 0x76, 0xDC, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x7E (~) */
    0x00, 0x00, 0x10, 0x10, 0x38, 0x38, 0x6C, 0x6C, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xFE, 0x00, 0x00, /* 0x7F () */
};
#endif


