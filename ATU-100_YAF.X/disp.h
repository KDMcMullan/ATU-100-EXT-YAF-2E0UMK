/*
 * ATU-100_EXT_YAF 
 * Yet Another Firmware
 * Author (presumably): Sven, DG4SN
 *
 * Display prototypes
 * (Presumably) created around March 2022
 *
 * Modified 12-Sep-2026 2E0UMK
 * Added functions for OLED screensaver.
 * 
 */

/* 
 * File:   disp.h
 * Author: sven
 *
 * Created on 23. März 2022, 15:38
 */

#ifndef DISP_H
#define	DISP_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define DISP_COL_CENTER   0x80
  

void DISP_Init(uint8_t i2_addr, uint8_t rotate);
void DISP_Str(uint8_t col, uint8_t row, const char *str, uint8_t invert);
void DISP_Char(uint8_t col, uint8_t row, char c, uint8_t invert);
void DISP_PWR(uint8_t col, uint8_t row, int16_t deciWatt, uint8_t invert);
void DISP_SWR(uint8_t col, uint8_t row, int16_t centiSWR, uint8_t invert);
void DISP_On(void);
void DISP_Off(void);
void DISP_Clr(void);
void DISP_DrawVLine(uint8_t x, uint8_t state);
void DISP_MoveVLine(uint8_t old_col, uint8_t new_col);
void DISP_RenderScreenSaver(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DISP_H */

