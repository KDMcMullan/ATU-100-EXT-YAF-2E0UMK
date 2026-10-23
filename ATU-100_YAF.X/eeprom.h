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
__eeprom  uint8_t ee_sleep_enable = 0;
__eeprom  int16_t ee_sleep_delay_sec = 10; // most folk might actually want 0 for no screensaver
__eeprom  int16_t ee_cal_point_0 = 10; // 1W
__eeprom  int16_t ee_cal_point_1 = 30; // 3W
__eeprom  int16_t ee_cal_offset = 100; // originally 150, which was likely unit specific
__eeprom  int16_t ee_cal_gain = 9400; // originally 12000, which was likely unit specific

// NB: call_gain 9600 compensates for real-world diode forward-voltage knee variations at typical HF frequencies.
// NB: call_gain 9120 is the exact math scalar when compensating for a 5:1 vs 10:1 coupler conversion or low-power QRP detector scaling.
// So, 9120-9600 is a fair guess (but may be specific to my hardware).

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
// bit2 = wake on RF
// bit3 = relay save
// bit4 = large display
// bits 7-5 reserved

__eeprom uint8_t ee_flags = 0b00010001; // rotate / large display by default

void EEPROM_Init(void);    
// void EEPROM_Write(uint8_t addr, void *ptrValue, uint8_t size);
void EEPROM_Write(uint16_t addr, void *ptrValue, uint8_t size);
void EEPROM_Read(uint8_t addr, void *ptrValue, uint8_t size);    
  

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */
