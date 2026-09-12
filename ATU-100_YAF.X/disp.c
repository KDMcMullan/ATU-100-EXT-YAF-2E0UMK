/*
 * ATU-100_EXT_YAF 
 * Yet Another Firmware
 * Author (presumably): DG4SN
 *
 * Display functions
 * (Presumably) created around March 2022
 *
 * Modified 10-Sep-2026 2E0UMK
 * Changed to Int Osc and disabled redundant clock settings.
 * 
 * Modified 12-Sep-2026 2E0UMK
 * Added a function to draw a vertical line and a wrapper to scroll it
 * back-and-forth like Larson Lights (for an OLED screen saver).
 * 
 */

#include "defines.h"
#include "font5x8.h"


#define FONT_WIDTH    5       //5pixel (muliply by 2)
#define FONT_SPACING (5+1)  //5pixel font + 1 pixel space  (muliply by 2)
#define RES_X         128  //Display resolution
#define RES_Y         64


uint8_t DISP_i2_addr;
uint8_t DISP_rotate;

void I2C_Start(void)
{
  I2C_SCL_DIR = 1; //SCL=1
  DELAY_2_us();
  I2C_SDA_DIR = 1; //SDA=1
  DELAY_2_us();
  I2C_SDA_DIR = 0; //SDA=0
  DELAY_2_us();
  I2C_SCL_DIR = 0; //SCL=0
  DELAY_2_us();
}

void I2C_Stop(void)
{
  I2C_SDA_DIR = 0; //SDA=0
  DELAY_2_us();
  I2C_SCL_DIR = 1; //SCL=1
  DELAY_2_us();
  I2C_SDA_DIR = 1; //SDA=1
  DELAY_2_us();

}

void I2C_Write(uint8_t value)
{
  for (uint8_t i = 0; i <= 7; i++)
  {
    if ((value & 0x80) == 0)
    {
      I2C_SDA_DIR = 0;
    }
    else
    {
      I2C_SDA_DIR = 1;
    }

    DELAY_2_us();

    I2C_SCL_DIR = 1;
    DELAY_2_us();
    I2C_SCL_DIR = 0;
    DELAY_2_us();
    value = (uint8_t) (value << 1);
  }

  I2C_SDA_DIR = 1; //ACK
  DELAY_2_us();
  I2C_SCL_DIR = 1;
  DELAY_2_us();
  I2C_SCL_DIR = 0;
  DELAY_2_us();
}

void DISP_Command(uint8_t command)
{
  I2C_Start();
  I2C_Write(DISP_i2_addr);
  I2C_Write(128); // 128 - command, 192 - data
  I2C_Write(command);
  I2C_Stop();
}

void DISP_DataAddress(uint8_t page, uint8_t start)
{
  I2C_Start();
  I2C_Write(DISP_i2_addr);
  I2C_Write(0); // 0 - continious mode, command; 64 - Co, data
  I2C_Write(0xB0 + page);
  I2C_Write(start & 0x0f); //low nibble of start
  I2C_Write(0x10 + (start >> 4)); //high nibbe of start

  I2C_Start(); //send start again
  I2C_Write(DISP_i2_addr);
  I2C_Write(64); // 0 - continious mode, command; 64 - Co, data

}

void DISP_Clr(void)
{
  DISP_Off();

  for (uint8_t page = 0; page <= 7; page++)
  {

    DISP_DataAddress(page, 0);
    for (uint8_t i = 0; i < RES_X; i++) //clear pixels
    {
      I2C_Write(0x00);
    }
  }
  I2C_Stop();

  DISP_On();
}

void DISP_On(void)
{
  DISP_Command(0xAF);
}

void DISP_Off(void)
{
  DISP_Command(0xAE);
}

void DISP_Init(uint8_t i2_addr, uint8_t rotate)
{
  DISP_i2_addr = i2_addr;
  DISP_rotate = rotate;

  I2C_SCL_DIR = DIR_INPUT; //1 = input / 0 = output
  I2C_SDA_DIR = DIR_INPUT; //note: external pull up resistors
  I2C_SCL_W = 0; //If output then 0
  I2C_SDA_W = 0;

  //DELAY_ms(1);

  //I2C_Stop();

  DELAY_5_us();

  I2C_Start();
  I2C_Write(DISP_i2_addr);
  I2C_Write(0); // 0 - continious mode, command; 64 - Co, data
  I2C_Write(0xAE); // display OFF

  // 128*64 OLED
  I2C_Write(0xD5); // clock division
  I2C_Write(0x80); // ratio
  //
  I2C_Write(0xA8); //  multiplexer
  I2C_Write(63); //
  //
  I2C_Write(0xD3); //  offset
  I2C_Write(0); // no offset for x64 !
  //
  I2C_Write(0x40); // set line, line = 0
  //
  I2C_Write(0x8D); //  charge pump
  I2C_Write(0x14); //  0x10 - external, 0x14 - internal
  //
  I2C_Write(0x81); //  contrast
  I2C_Write(255); //   0-255
  //
  I2C_Write(0xD9); //  pre-charge
  I2C_Write(0xf1); //  0x22 - external, 0xF1 - internal
  //
  I2C_Write(0x20); //  memory addressing mode
  I2C_Write(0x02); //  page addressing mode   02
  //
  I2C_Write(0x21); // set column range
  I2C_Write(0); // column start
  I2C_Write(127); // column stop
  //
  I2C_Write(0x2E); //  stop scrolling
  //
  
  
 
  if (DISP_rotate == TRUE)
  {
    I2C_Write(0xA0); //  segment re-map, A0 - normal, A1 - remapped
    //
    I2C_Write(0xC0); // scan direction, C0 - normal, C8 - remapped
  }
  else 
  {
    I2C_Write(0xA1); //  segment re-map, A0 - normal, A1 - remapped
    //
    I2C_Write(0xC8); // scan direction, C0 - normal, C8 - remapped
  }
  //
  I2C_Write(0xDA); //  COM pins configure
  I2C_Write(0x12); // 12 for x64
  //
  I2C_Write(0xDB); //  V-COM detect
  I2C_Write(0x40); //

  I2C_Write(0xA4); //  display entire ON
  //
  I2C_Write(0xA6); // 0xA6 - normal, 0xA7 - inverse
  //
  I2C_Stop();

  DISP_Clr();

}

void DISP_Char(uint8_t col, uint8_t row, char c, uint8_t invert)
{
  char str[2];
  str[0] = c;
  str[1] =0;
  DISP_Str(col, row, str, invert);
}


void DISP_Str(uint8_t col, uint8_t row, const char *str, uint8_t invert)
{
  const char *p;
  bitfield_t x, y;
  uint8_t page;
  uint8_t start;
  uint8_t empty;
  uint16_t fpos;

  if (invert) empty = 0xff;
  else empty = 0;


  page = row * 2;

  if (col == DISP_COL_CENTER)
  {
    uint8_t len = 0;
    //string length
    p = str;
    while (*p != 0)
    {
      len++;
      p++;
    }

    //pixel length
    len = len * (2 * FONT_SPACING);
    start = (RES_X - len) / 2;

  }
  else //Left aligned
  {
    start = col * (2 * FONT_SPACING);
  }

  //upper part of the string
  DISP_DataAddress(page, start);

  p = str;
  while (*p != 0)
  {
    fpos = (*p - 32) * FONT_WIDTH;
    for (uint8_t h = 0; h < FONT_WIDTH; h++)
    {
      x.byte = font5x8[fpos + h]; //get byte from font

      y.bits.B7 = x.bits.B3;
      y.bits.B6 = x.bits.B2;
      y.bits.B5 = x.bits.B2;
      y.bits.B4 = x.bits.B1;
      y.bits.B3 = x.bits.B1;
      y.bits.B2 = x.bits.B0;
      y.bits.B1 = x.bits.B0;
      y.bits.B0 = 0; //space line

      y.byte = y.byte ^ empty; //maybe invert    
      I2C_Write(y.byte);
      I2C_Write(y.byte); //128x64  the same byte twice
    }
    I2C_Write(empty); //Space between two char
    I2C_Write(empty);
    p++;
  }


  //lower part of the string
  DISP_DataAddress(page + 1, start);
  p = str;
  while (*p != 0)
  {
    fpos = (*p - 32) * FONT_WIDTH;
    for (uint8_t h = 0; h < FONT_WIDTH; h++)
    {
      x.byte = font5x8[fpos + h]; //get byte from font
      y.bits.B7 = 0; //space line
      y.bits.B6 = x.bits.B6;
      y.bits.B5 = x.bits.B6;
      y.bits.B4 = x.bits.B5;
      y.bits.B3 = x.bits.B5;
      y.bits.B2 = x.bits.B4;
      y.bits.B1 = x.bits.B4;
      y.bits.B0 = x.bits.B3;

      y.byte = y.byte ^ empty; //maybe invert    
      I2C_Write(y.byte);
      I2C_Write(y.byte); //128x64  the same byte twice

    }
    I2C_Write(empty); //Space between two char
    I2C_Write(empty);
    p++;
  }

  I2C_Stop();

}

/**
 * Show power as x.xW when < 10W and xxW or xxxW if higher
 */
void DISP_PWR(uint8_t col, uint8_t row, int16_t deciWatt, uint8_t invert)
{
  char str[5];
  uint8_t low_value =1;
 
  if(deciWatt >= 100)
  {
    deciWatt = deciWatt / 10;
    low_value=0;
  }
  UTILI_Int2Str(deciWatt, str, (sizeof(str)-1));
  
  
  if(low_value)
  {
    //Example: " 99" -> "9.9"
    str[0] = str[1];
    if(str[0] == ' ')  str[0] = '0'; //leading zero
    str[1] = '.';
  }
  
  str[3] = 'W';
  str[4] = 0; //terminate string
  
 
  DISP_Str(col, row, str, invert);

}


void DISP_SWR(uint8_t col, uint8_t row, int16_t centiSWR, uint8_t invert)
{
  char str[5] = "0.00";
  if(centiSWR >= 100)
  {
    UTILI_Int2Str(centiSWR , &str[1], (sizeof(str)-1));
    str[0] = str[1]; //first number 
    str[1] = '.';
  }
  DISP_Str(col, row, str, invert);
}
/*
void DISP_DrawVLine(uint8_t x, uint8_t state)
{
    if (x >= RES_X) return; // Out of bounds safety check

    uint8_t fill_byte = state ? 0xFF : 0x00;

    // SSD1306 page addressing: 8 pages (0..7), each 8 pixels tall.
    // Stream fill_byte to column 'x' across all 8 pages for a 64-pixel vertical bar.
    for (uint8_t page = 0; page <= 7; page++)
    {
        DISP_DataAddress(page, x);
        I2C_Write(fill_byte);
        I2C_Stop();
    }
}
*/

/**
 * @brief True streamed VLine drawing with zero repeated Start sequences.
 */
void DISP_DrawVLineFast(uint8_t x, uint8_t state)
{
    if (x >= RES_X) return;
    uint8_t fill_byte = state ? 0xFF : 0x00;

    for (uint8_t page = 0; page <= 7; page++)
    {
        // 1. Send page setup command sequence
        I2C_Start();
        I2C_Write(DISP_i2_addr);
        I2C_Write(0x00);                // Command stream mode
        I2C_Write(0xB0 + page);         // Page number
        I2C_Write(x & 0x0F);            // Low nibble col
        I2C_Write(0x10 + (x >> 4));     // High nibble col

        // 2. Write pixel byte immediately without extra Start frame
        I2C_Start();                    // Restart for Data
        I2C_Write(DISP_i2_addr);
        I2C_Write(0x40);                // Data mode (Co=0, D/C#=1)
        I2C_Write(fill_byte);
        I2C_Stop();                     // Close page write
    }
}

/**
 * @brief Renders a single step of the Larson scanner screensaver.
 * @note 8-pixel wide bar moving at 4 pixels per step with zero-edge-hiccup.
 */
void DISP_RenderScreenSaver(void)
{
    static int16_t x_pos = 0;
    static int8_t  dir = 4; // 4 pixels per tick step
    
    int16_t old_pos = x_pos;

    if (dir > 0)
    {
        // MOVING RIGHT: Erase trailing (left), draw leading (right)
        for (uint8_t i = 0; i < 4; i++)
        {
            DISP_DrawVLineFast((uint8_t)(old_pos + i), 0);
            DISP_DrawVLineFast((uint8_t)(old_pos + 8 + i), 1);
        }
        
        x_pos += 4;
        if (x_pos >= 120)
        {
            x_pos = 120;
            dir = -4; // Reverse direction for NEXT frame
        }
    }
    else
    {
        // MOVING LEFT: Erase trailing (right), draw leading (left)
        for (uint8_t i = 0; i < 4; i++)
        {
            DISP_DrawVLineFast((uint8_t)(old_pos + 7 - i), 0);
            DISP_DrawVLineFast((uint8_t)(old_pos - 1 - i), 1);
        }
        
        x_pos -= 4;
        if (x_pos <= 0)
        {
            x_pos = 0;
            dir = 4; // Reverse direction for NEXT frame
        }
    }
}


/*

void DISP_MoveVLine(uint8_t old_col, uint8_t new_col)
{
    // Clear only the previous column instead of full screen clear to eliminate flicker
    if (old_col < RES_X)
    {
        DISP_DrawVLine(old_col, 0);
    }

    if (new_col < RES_X)
    {
        DISP_DrawVLine(new_col, 1);
    }
}


void DISP_RenderScreenSaver(void)
{
    static int8_t col = 0;
    static int8_t dir = 1;
    int8_t old_col = col;

    // Advance column position
    col += dir;
    if (col >= (RES_X - 1))
    {
        col = RES_X - 1;
        dir = -1;
    }
    else if (col <= 0)
    {
        col = 0;
        dir = 1;
    }

    // Move line directly on hardware
    DISP_MoveVLine((uint8_t)old_col, (uint8_t)col);
}
*/
