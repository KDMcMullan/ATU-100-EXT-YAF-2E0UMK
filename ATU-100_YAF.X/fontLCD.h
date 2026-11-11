/* 
 * File:   fontLCD.h
 * Author: Ken McMullan, 2E0UMK
 *
 * Created: 29 Sep 2026
 * 
 * 24 x 32 large seven-segment font.
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
 * Modified 31-Oct-2026 2E0UMK
 * Made the digit slightly narrower and shorter so as to make the decimal
 * point more evident.
 * 
 * Modified 05-Nov-2026 2E0UMK
 * Shift the digits one pixel right, hoping not to interfere with other text
 * labels.
 * 
 * Modified 11-Nov-2026 2E0UMK
 * Recalled that the purpose of the exercise was to make the font bigger.
 * Realised that it was still only 14 pixels wide (albeit on a 16 bit wide
 * grid) and that this isn't really very much wider than the 10 pixels of the
 * original font. Font is now 24 bits wide.
 * Font uses a completely different storage format, more compatible with the 
 * OLED display (which stores the pixels as columns of 8, where you might
 * expect it to be rows.
 */

#ifndef FONTLCD_H
#define FONTLCD_H

#include <stdint.h>

#define LCD_WIDTH       24
#define LCD_HEIGHT      32
#define LCD_PAGES       4
#define LCD_MAX_CHARS   5

#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))

typedef uint8_t LCDBitmap[LCD_PAGES][LCD_WIDTH];

typedef struct
{
    uint8_t column;
    uint8_t bits;
} LCDColumnByte;

typedef struct
{
    char segment;
    uint8_t byte_index;
    uint8_t count;
    const LCDColumnByte *data;
} LCDSegmentData;

#define LCD_SEG_A   0x01
#define LCD_SEG_B   0x02
#define LCD_SEG_C   0x04
#define LCD_SEG_D   0x08
#define LCD_SEG_E   0x10
#define LCD_SEG_F   0x20
#define LCD_SEG_G   0x40
#define LCD_SEG_DP  0x80


/* Segment A */
static const LCDColumnByte LCD_a_0[] = { { 6, 0x02 }, { 7, 0x06 }, { 8, 0x0E }, { 9, 0x1E }, { 10, 0x1E }, { 11, 0x1E }, { 12, 0x1E }, { 13, 0x1E }, { 14, 0x1E }, { 15, 0x1E }, { 16, 0x0E }, { 17, 0x06 }, { 18, 0x02 } };


/* Segment B */
static const LCDColumnByte LCD_b_0[] = { { 17, 0xC0 }, { 18, 0xE0 }, { 19, 0xF0 }, { 20, 0xF8 } };
static const LCDColumnByte LCD_b_1[] = { { 16, 0x0E }, { 17, 0x1F }, { 18, 0x3F }, { 19, 0x7F }, { 20, 0x01 } };


/* Segment C */
static const LCDColumnByte LCD_c_2[] = { { 14, 0x80 }, { 15, 0xF0 }, { 16, 0xF8 }, { 17, 0xFC }, { 18, 0x7E } };
static const LCDColumnByte LCD_c_3[] = { { 14, 0x03 }, { 15, 0x07 }, { 16, 0x0F }, { 17, 0x1F } };


/* Segment D */
static const LCDColumnByte LCD_d_3[] = { { 3, 0x40 }, { 4, 0x60 }, { 5, 0x70 }, { 6, 0x78 }, { 7, 0x78 }, { 8, 0x78 }, { 9, 0x78 }, { 10, 0x78 }, { 11, 0x78 }, { 12, 0x78 }, { 13, 0x70 }, { 14, 0x60 }, { 15, 0x40 } };


/* Segment E */
static const LCDColumnByte LCD_e_2[] = { { 1, 0x80 }, { 2, 0xFE }, { 3, 0xFC }, { 4, 0xF8 }, { 5, 0x70 } };
static const LCDColumnByte LCD_e_3[] = { { 1, 0x1F }, { 2, 0x0F }, { 3, 0x07 }, { 4, 0x03 } };


/* Segment F */
static const LCDColumnByte LCD_f_0[] = { { 4, 0xF8 }, { 5, 0xF0 }, { 6, 0xE0 }, { 7, 0xC0 } };
static const LCDColumnByte LCD_f_1[] = { { 3, 0x7E }, { 4, 0x3F }, { 5, 0x1F }, { 6, 0x0F }, { 7, 0x01 } };


/* Segment G */
static const LCDColumnByte LCD_g_1[] = { { 5, 0x80 }, { 6, 0xC0 }, { 7, 0xC0 }, { 8, 0xC0 }, { 9, 0xC0 }, { 10, 0xC0 }, { 11, 0xC0 }, { 12, 0xC0 }, { 13, 0xC0 }, { 14, 0xC0 }, { 15, 0xC0 }, { 16, 0xC0 }, { 17, 0x80 } };
static const LCDColumnByte LCD_g_2[] = { { 4, 0x01 }, { 5, 0x03 }, { 6, 0x03 }, { 7, 0x03 }, { 8, 0x03 }, { 9, 0x03 }, { 10, 0x03 }, { 11, 0x03 }, { 12, 0x03 }, { 13, 0x03 }, { 14, 0x03 }, { 15, 0x03 }, { 16, 0x01 } };


/* Decimal point */
static const LCDColumnByte LCD_p_3[] = { { 20, 0x38 }, { 21, 0x38 }, { 22, 0x38 } };


static const LCDSegmentData LCD_Segments[] =
{
    { 'a', 0, ARRAY_COUNT(LCD_a_0), LCD_a_0 },

    { 'b', 0, ARRAY_COUNT(LCD_b_0), LCD_b_0 },
    { 'b', 1, ARRAY_COUNT(LCD_b_1), LCD_b_1 },

    { 'c', 2, ARRAY_COUNT(LCD_c_2), LCD_c_2 },
    { 'c', 3, ARRAY_COUNT(LCD_c_3), LCD_c_3 },

    { 'd', 3, ARRAY_COUNT(LCD_d_3), LCD_d_3 },

    { 'e', 2, ARRAY_COUNT(LCD_e_2), LCD_e_2 },
    { 'e', 3, ARRAY_COUNT(LCD_e_3), LCD_e_3 },

    { 'f', 0, ARRAY_COUNT(LCD_f_0), LCD_f_0 },
    { 'f', 1, ARRAY_COUNT(LCD_f_1), LCD_f_1 },

    { 'g', 1, ARRAY_COUNT(LCD_g_1), LCD_g_1 },
    { 'g', 2, ARRAY_COUNT(LCD_g_2), LCD_g_2 },

    { 'p', 3, ARRAY_COUNT(LCD_p_3), LCD_p_3 }

};


void LCD_BuildDigit(char c, LCDBitmap bitmap);
void LCD_WriteDigit(uint8_t x, uint8_t page, char c);
void LCD_WriteDigitDP(uint8_t x, uint8_t page, char c);
void LCD_EraseDigit(uint8_t x, uint8_t page);
void LCD_EraseDigitLeft(uint8_t units_x, uint8_t page);

#endif /* FONTLCD_H */
