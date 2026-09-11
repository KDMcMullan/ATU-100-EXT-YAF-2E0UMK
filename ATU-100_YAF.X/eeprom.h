/* 
 * File:   eeprom.h
 * Author: DG4SN
 *
 * Created on 22. März 2022, 16:09
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
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C"
{
#endif

  
__eeprom  int16_t ee_tune_stop_swr = 120;
__eeprom  int16_t ee_tune_auto_swr = 140;
__eeprom  uint8_t ee_tune_auto_enable = 0;
__eeprom  uint8_t ee_sleep_enable =0;
__eeprom  int16_t ee_sleep_delay_sec = 30;
__eeprom  int16_t ee_cal_point_0 = 10; // 1W
__eeprom  int16_t ee_cal_point_1 = 30; // 3W
__eeprom  int16_t ee_cal_offset = 0; // originally 150, which was likely unit specific
__eeprom  int16_t ee_cal_gain = 10000; // originally 12000, which was likely unit specific

__eeprom  tunemem_t ee_tunemem[TUNEMEM_ITEMS] ={
  {0,"Startup "}, //0
  {0,"        "}, //1
  {0,"        "}, //2
  {0,"        "}, //3
  {0,"        "}, //4
  {0,"        "}, //5
  {0,"        "}, //6
  {0,"        "}, //7
  {0,"        "}, //8
  {0,"        "} //9
  
};
          
// bit0 = screen rotation
// bit1 = debug mode
// bits 7-2 = reserved
__eeprom uint8_t ee_flags = 0b00000001; // rotate by default

void EEPROM_Init(void);    
// void EEPROM_Write(uint8_t addr, void *ptrValue, uint8_t size);
void EEPROM_Write(uint16_t addr, void *ptrValue, uint8_t size);
void EEPROM_Read(uint8_t addr, void *ptrValue, uint8_t size);    
  

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

