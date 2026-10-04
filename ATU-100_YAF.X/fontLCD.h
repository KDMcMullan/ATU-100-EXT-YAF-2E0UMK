
/* 
 * File:   fontLCD.h
 * Author: Ken McMullan, 2E0UMK
 *
 * Created: 29 Sep 2026
 * 
 * 16 x 32 large seven-segment font.
 *
 * Each segment bitmap is presented in a "compressed" fashion.
 * The row number preserves the original 32-row vertical position. Only the
 * nonzero lines are included along with a line index, so this occupies 177
 * bytes instead of 512, at a small CPU overhead to build the character with
 * its empty lines.
 * 
 * Modified 04-Oct-2026 2E0UMK
 * Slightly larger digits and larger decimal point.
 * 
 */

#ifndef FONTLCD_H
#define FONTLCD_H

#include <stdint.h>

typedef struct
{
    uint8_t  row;
    uint16_t bits;
} LCDRow;

/* Segment masks used by LCDdigits[]. */

#define LCD_SEG_A   0x01
#define LCD_SEG_B   0x02
#define LCD_SEG_C   0x04
#define LCD_SEG_D   0x08
#define LCD_SEG_E   0x10
#define LCD_SEG_F   0x20
#define LCD_SEG_G   0x40
#define LCD_SEG_DP  0x80


/* Segment A */
static const LCDRow LCD_A[] = // 9 bytes instead of 64
{
  { 1, 0x1FF8 }, { 2, 0x0FF0 }, { 3, 0x07E0 }
};


/* Segment B */
static const LCDRow LCD_B[] = // 36 bytes instead of 64
{
  { 2, 0x0002 }, { 3, 0x0006 }, { 4, 0x000E }, { 5, 0x000E }, { 6, 0x000E }, { 7, 0x000E }, { 8, 0x000E }, { 9, 0x001E }, { 10, 0x001C }, { 11, 0x001C }, { 12, 0x001C }, { 13, 0x000C }, { 14, 0x0004 }
};


/* Segment C */
static const LCDRow LCD_C[] = // 36 bytes instead of 64
{
  { 17, 0x0004 }, { 18, 0x000C }, { 19, 0x001C }, { 20, 0x001C }, { 21, 0x001C }, { 22, 0x003C }, { 23, 0x0038 }, { 24, 0x0038 }, { 25, 0x0038 }, { 26, 0x0018 }, { 27, 0x0008 }
};


/* Segment D */
static const LCDRow LCD_D[] = // 9 bytes instead of 64
{
  { 27, 0x1FC0 }, { 28, 0x3FE0 }, { 29, 0x7FF0 }
};


/* Segment E */
static const LCDRow LCD_E[] = // 36 bytes instead of 64
{
  { 16, 0x4000 }, { 17, 0x6000 }, { 18, 0x7000 }, { 19, 0x7000 }, { 20, 0x7000 }, { 21, 0xF000 }, { 22, 0xE000 }, { 23, 0xE000 }, { 24, 0xE000 }, { 25, 0xE000 }, { 26, 0xC000 }, { 27, 0x8000 }
};


/* Segment F */
static const LCDRow LCD_F[] = // 36 bytes instead of 64
{
  { 3, 0x2000 }, { 4, 0x3000 }, { 5, 0x3800 }, { 6, 0x3800 }, { 7, 0x3800 }, { 8, 0x7800 }, { 9, 0x7000 }, { 10, 0x7000 }, { 11, 0x7000 }, { 12, 0x6000 }, { 13, 0x4000 }
};


/* Segment G */
static const LCDRow LCD_G[] = // 9 bytes instead of 64
{
  { 14, 0x1FE0 }, { 15, 0x1FF0 }, { 16, 0x0FF0 }
};


/* Decimal point */
static const LCDRow LCD_DP[] = // 6 bytes instead of 64
{
  { 28, 0x0007 }, { 29, 0x0007 }, { 30, 0x0007 }
};


/*
 * Segment mask for hexadecimal digits 0-F.
 *
 * Bit 0 = A
 * Bit 1 = B
 * Bit 2 = C
 * Bit 3 = D
 * Bit 4 = E
 * Bit 5 = F
 * Bit 6 = G
 *
 * Decimal point is separate: LCD_SEG_P.
 */

static const uint8_t LCDdigits[16] =
{
    0x3F,  /* 0 = A,B,C,D,E,F = bits 5,4,3,2,1,0 = 0x3F */
    0x06,  /* 1 */
    0x5B,  /* 2 */
    0x4F,  /* 3 */
    0x66,  /* 4 */
    0x6D,  /* 5 */
    0x7D,  /* 6 */
    0x07,  /* 7 */
    0x7F,  /* 8 */
    0x6F,  /* 9 */
    0x77,  /* A */
    0x7C,  /* B */
    0x39,  /* C */
    0x5E,  /* D */
    0x79,  /* E */
    0x71   /* F */
};

#endif /* FONTLCD_H */
