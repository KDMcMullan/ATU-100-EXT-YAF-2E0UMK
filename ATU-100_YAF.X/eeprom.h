/* 
 * File:   eeprom.h
 * Author: DG4SN
 *
 * Created 22 March 2022
 * 
 * Modified 09-Sep-2026 2E0UMK
 * Added boolean flags for EEPROM storage of settings such as screen rotation.
 * 
 * Modified 10-Sep-2026 2E0UMK
 * On reflection (!) rotate by default.
 * 
 * Modified 11-Sep-2026 2E0UMK
 * Changed default calibration gain / offset to suit my observations.
 * Modified EEPROM_Write prototype to remove warnings.
 * 
 * Modified 09-Oct-2026 2E0UMK
 * Default to large LCD font.
 * 
 * Modified 01-Nov-2026 2E0UMK
 * Calibration P0, P1, offset and gain can now by reset using the menu, so
 * their constant values are stored in defines.h.
 * 
 * Modified 05-Nov-2026 2E0UMK
 * Reverted back to 8 bit address in EEPROM write.
 * Added intermediate in order to remove warnings without suppressing them.
 * 
 * Modified 06-Nov-2026 2E0UMK
 * Added default strings for the tune save slots. Selfishly in order of my
 * favourite bands and available antennas!
 * 
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C"
{
#endif

// intermediate of the correct address type, in order to remove warnings
// without blindly suppressing them
#define EEPROM_ADDR(p) ((uint8_t)(uintptr_t)(p))
    
__eeprom  int16_t ee_tune_stop_swr  = 120;
__eeprom  int16_t ee_tune_auto_swr  = 140;
__eeprom  uint8_t ee_tune_auto_enable = 0;
__eeprom  uint8_t ee_sleep_enable    =  0;
__eeprom  int16_t ee_sleep_delay_sec = 10; // need to address this: the value 10 is in the menu, but screensaver is disabled by default.

__eeprom int16_t ee_cal_point_0 = DEF_CAL_P0_STD;
__eeprom int16_t ee_cal_point_1 = DEF_CAL_P1_STD;
__eeprom  int16_t ee_cal_offset = DEF_CAL_OFFSET_STD; // originally 150, which was likely unit specific
__eeprom  int16_t ee_cal_gain = DEF_CAL_GAIN_STD; // originally 12000, which was likely unit specific


__eeprom  tunemem_t ee_tunemem[TUNEMEM_ITEMS] ={
  {0,"40m Loop"}, //0
  {0,"20m Loop"}, //1
  {0,"15m Loop"}, //2
  {0,"10m LoLp"}, //3
  {0,"17m Dipl"}, //4
  {0,"15m Dipl"}, //5
  {0,"30m Dipl"}, //6
  {0,"10m HiLp"}, //7
  {0,"80m Dipl"}, //8
  {0,"60m Loop"}  //9
  
};
          
// bit0 = screen rotation
// bit1 = debug mode
// bit2 = wake on RF
// bit3 = relay save
// bit4 = large display
// bits 7-5 reserved

__eeprom uint8_t ee_flags = 0b00010001; // rotate / large display by default

void EEPROM_Init(void);    
void EEPROM_Write(uint8_t addr, void *ptrValue, uint8_t size);
void EEPROM_Read(uint8_t addr, void *ptrValue, uint8_t size);    
  

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */
