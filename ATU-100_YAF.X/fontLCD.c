/* 
 * File:   fontLCD.h
 * Author: Ken McMullan, 2E0UMK
 *
 * Created: 08-Nov-2026
 * 
 * 24 x 32 large seven-segment font.
 *
 */

#include <stdint.h>
#include "fontLCD.h"
#include "disp.h" // for the I2C functions

// Include the project header which declares the I2C functions
// and DISP_DataAddress().

#define LCD_WRITE_BITMAP       0
#define LCD_CLEAR_SEGMENTS     1

static LCDBitmap bitmap;
static LCDBitmap bitmap_mask;

void DISP_LCD(uint8_t x,      // x-coordinate of units digit, in pixels
              uint8_t page,   // y in pages, range 0..7, usually 0 or 4
              int16_t n,      // input value
              uint8_t scale,  // decimal scaling: 0 = /1, 1 = /10, 2 = /100
              uint8_t d,      // number of decimal places to display
              uint8_t maxint) // maximum digits left of decimal point
{
    uint32_t magnitude;
    uint32_t divisor;
    uint32_t integer_part;
    uint32_t fraction_part;
    uint32_t scale_factor;
    uint8_t digits;
    uint8_t i;
    uint8_t digit;
    uint8_t negative;
    int32_t signed_value;
    int32_t char_x;

    if (page > 4 || scale > 9)
    {
        return;
    }

    /*
     * Convert to magnitude safely, including n == -32768.
     */
    signed_value = n;
    negative = (signed_value < 0);

    if (negative)
    {
        signed_value = -signed_value;
    }

    magnitude = (uint32_t)signed_value;

    /*
     * Calculate 10^scale.
     */
    scale_factor = 1;

    for (i = 0; i < scale; i++)
    {
        scale_factor *= 10UL;
    }

    /*
     * Split the input into integer and fractional portions.
     */
    integer_part = magnitude / scale_factor;
    fraction_part = magnitude % scale_factor;

    /*
     * Count the integer digits. Zero must occupy one digit.
     */
    digits = 1;
    divisor = 1;

    while (integer_part >= 10UL)
    {
        integer_part /= 10UL;
        digits++;
        divisor *= 10UL;
    }

    /*
     * Clear unused integer positions, including the sign position.
     * Do not erase digits which are about to be drawn.
     */
    for (i = digits; i <= maxint; i++)
    {
        char_x = (int32_t)x - ((int32_t)i * LCD_WIDTH);

        if (char_x >= 0 &&
            char_x <= (int32_t)(RES_X - LCD_WIDTH))
        {
            LCD_EraseDigit((uint8_t)char_x, page);
        }
    }

    /*
     * Restore the integer portion for digit extraction.
     */
    integer_part = magnitude / scale_factor;

    /*
     * Start with the most significant integer digit.
     */
    char_x = (int32_t)x - ((int32_t)(digits - 1) * LCD_WIDTH);

    for (i = 0; i < digits; i++)
    {
        digit = (uint8_t)(integer_part / divisor);
        integer_part %= divisor;

        if (char_x >= 0 &&
            char_x <= (int32_t)(RES_X - LCD_WIDTH))
        {
            if (i == (digits - 1))
            {
                LCD_WriteDigitDP((uint8_t)char_x,
                                 page,
                                 (char)('0' + digit));
            }
            else
            {
                LCD_WriteDigit((uint8_t)char_x,
                               page,
                               (char)('0' + digit));
            }
        }

        char_x += LCD_WIDTH;

        if (divisor > 1UL)
        {
            divisor /= 10UL;
        }
    }

    /*
     * Display fractional digits to the right of the units digit.
     * Missing decimal places are zero-padded.
     */
    for (i = 0; i < d; i++)
    {
        char_x = (int32_t)x + ((int32_t)(i + 1) * LCD_WIDTH);

        if (char_x >= 0 &&
            char_x <= (int32_t)(RES_X - LCD_WIDTH))
        {
            uint32_t fraction_divisor = 1UL;
            uint8_t j;

            if (i < scale)
            {
                for (j = 0; j < (uint8_t)(scale - i - 1); j++)
                {
                    fraction_divisor *= 10UL;
                }

                digit = (uint8_t)(fraction_part / fraction_divisor);
                fraction_part %= fraction_divisor;
            }
            else
            {
                digit = 0;
            }

            LCD_WriteDigit((uint8_t)char_x,
                           page,
                           (char)('0' + digit));
        }
    }

    /*
     * Display a minus sign immediately to the left of the number.
     * The sign uses segment G.
     */
    if (negative)
    {
        char_x = (int32_t)x - ((int32_t)digits * LCD_WIDTH);

        if (char_x >= 0 &&
            char_x <= (int32_t)(RES_X - LCD_WIDTH))
        {
            LCD_WriteDigit((uint8_t)char_x, page, '-');
        }
    }
} // DISP_LCD


static uint8_t LCD_GetMask(char c)
{
    switch (c)
    {
        case '0': return LCD_SEG_A | LCD_SEG_B | LCD_SEG_C |
                         LCD_SEG_D | LCD_SEG_E | LCD_SEG_F;

        case '1': return LCD_SEG_B | LCD_SEG_C;

        case '2': return LCD_SEG_A | LCD_SEG_B | LCD_SEG_G |
                         LCD_SEG_E | LCD_SEG_D;

        case '3': return LCD_SEG_A | LCD_SEG_B | LCD_SEG_C |
                         LCD_SEG_D | LCD_SEG_G;

        case '4': return LCD_SEG_F | LCD_SEG_G |
                         LCD_SEG_B | LCD_SEG_C;

        case '5': return LCD_SEG_A | LCD_SEG_F | LCD_SEG_G |
                         LCD_SEG_C | LCD_SEG_D;

        case '6': return LCD_SEG_A | LCD_SEG_F | LCD_SEG_G |
                         LCD_SEG_C | LCD_SEG_D | LCD_SEG_E;

        case '7': return LCD_SEG_A | LCD_SEG_B | LCD_SEG_C;

        case '8': return LCD_SEG_A | LCD_SEG_B | LCD_SEG_C |
                         LCD_SEG_D | LCD_SEG_E | LCD_SEG_F | LCD_SEG_G;

        case '9': return LCD_SEG_A | LCD_SEG_B | LCD_SEG_C |
                         LCD_SEG_D | LCD_SEG_F | LCD_SEG_G;

        case 'A': return LCD_SEG_A | LCD_SEG_B | LCD_SEG_C |
                         LCD_SEG_E | LCD_SEG_F | LCD_SEG_G;

        case 'B': return LCD_SEG_C | LCD_SEG_D | LCD_SEG_E |
                         LCD_SEG_F | LCD_SEG_G;

        case 'C': return LCD_SEG_A | LCD_SEG_D |
                         LCD_SEG_E | LCD_SEG_F;

        case 'D': return LCD_SEG_B | LCD_SEG_C | LCD_SEG_D |
                         LCD_SEG_E | LCD_SEG_G;

        case 'E': return LCD_SEG_A | LCD_SEG_D |
                         LCD_SEG_E | LCD_SEG_F | LCD_SEG_G;

        case 'F': return LCD_SEG_A | LCD_SEG_E |
                         LCD_SEG_F | LCD_SEG_G;

        case '-': return LCD_SEG_G;

        case '.': return LCD_SEG_DP;

        default:  return 0;
    }
}


static void LCD_AddSegment(LCDBitmap bitmap,
                           const LCDSegmentData *segment)
{
    uint8_t i;

    for (i = 0; i < segment->count; i++)
    {
        bitmap[segment->byte_index][segment->data[i].column]
                |= segment->data[i].bits;
    }
}


static uint8_t LCD_GetSegmentMask(char segment)
{
    switch (segment)
    {
        case 'a': return LCD_SEG_A;
        case 'b': return LCD_SEG_B;
        case 'c': return LCD_SEG_C;
        case 'd': return LCD_SEG_D;
        case 'e': return LCD_SEG_E;
        case 'f': return LCD_SEG_F;
        case 'g': return LCD_SEG_G;
        case 'p': return LCD_SEG_DP;

        default: return 0;
    }
}


void LCD_BuildDigit(char c, LCDBitmap bitmap)
{
    uint8_t mask;
    uint8_t segment_mask;
    uint8_t i;
    uint8_t row;
    uint8_t column;

    mask = LCD_GetMask(c);

    // Clear the bitmap.

    for (row = 0; row < LCD_PAGES; row++)
    {
        for (column = 0; column < LCD_WIDTH; column++)
        {
            bitmap[row][column] = 0;
        }
    }

    // Add the required segments.

    for (i = 0; i < ARRAY_COUNT(LCD_Segments); i++)
    {
        segment_mask = LCD_GetSegmentMask(LCD_Segments[i].segment);

        if (mask & segment_mask)
        {
            LCD_AddSegment(bitmap, &LCD_Segments[i]);
        }
    }
}

static void LCD_WriteBitmap(uint8_t x,
                            uint8_t page,
                            const LCDBitmap bitmap,
                            uint8_t mode)
{
    uint8_t lcd_page;
    uint8_t column;
    uint8_t value;

    static LCDBitmap mask;

    if (x > (RES_X - LCD_WIDTH))
    {
        return;
    }

    if (page > 4)
    {
        return;
    }

    // Build the mask: all digit segments plus decimal point.
    LCD_BuildDigit('8', mask);
    LCD_AddSegment(mask, &LCD_Segments[ARRAY_COUNT(LCD_Segments) - 1]);

    for (lcd_page = 0; lcd_page < LCD_PAGES; lcd_page++)
    {
        column = 0;

        while (column < LCD_WIDTH)
        {
            // Skip columns outside the font's occupied area.
            if (mask[lcd_page][column] == 0)
            {
                column++;
                continue;
            }

            DISP_DataAddress(page + lcd_page, x + column);

            // Write the complete column, including zero bytes.
            value = bitmap[lcd_page][column];
            I2C_Write(value);

            column++;

            while (column < LCD_WIDTH &&
                   mask[lcd_page][column] != 0)
            {
                value = bitmap[lcd_page][column];
                I2C_Write(value);
                column++;
            }

            I2C_Stop();
        }
    }
} // LCD_WriteBitmap


void LCD_WriteDigit(uint8_t x, uint8_t page, char c)
{
    LCD_BuildDigit(c, bitmap);
    LCD_WriteBitmap(x, page, bitmap, LCD_WRITE_BITMAP);
}


void LCD_WriteDigitDP(uint8_t x, uint8_t page, char c)
{
    uint8_t i;

    LCD_BuildDigit(c, bitmap);

    for (i = 0; i < ARRAY_COUNT(LCD_Segments); i++)
    {
        if (LCD_Segments[i].segment == 'p')
        {
            LCD_AddSegment(bitmap, &LCD_Segments[i]);
        }
    }

    LCD_WriteBitmap(x, page, bitmap, LCD_WRITE_BITMAP);
}


void LCD_EraseDigit(uint8_t x, uint8_t page)
{
    // very similar to the second part of LCD_WriteDigit, but creates an "8"
    // and, for I2C write efficiency, only erases the columns which would be
    // occupied by the segments of te "8".

    uint8_t lcd_page;
    uint8_t column;

    LCD_BuildDigit('8', bitmap);

    for (lcd_page = 0; lcd_page < LCD_PAGES; lcd_page++)
    {
        column = 0;

        while (column < LCD_WIDTH)
        {
            if (bitmap[lcd_page][column] == 0)
            {
                column++;
                continue;
            }

            DISP_DataAddress(page + lcd_page, x + column);

            while (column < LCD_WIDTH &&
                   bitmap[lcd_page][column] != 0)
            {
                I2C_Write(0);
                column++;
            }

            I2C_Stop();
        }
    }
}
