/**
 * ATU-100_EXT_YAF 
 * Yet Another Firmware
 * by DG4SN
 *
 * EEPROM function
 *
 * Modified 09-Sep-2026 2E0UMK
 * Added flag to store display rotation (among other things).
 *
 */

#include "defines.h"


void EEPROM_Init(void)
{ 
  EEPROM_Read((uint8_t)&ee_tune_stop_swr, &global.tune_stop_swr, sizeof(global.tune_stop_swr));
  EEPROM_Read((uint8_t)&ee_tune_auto_swr, &global.tune_auto_swr, sizeof(global.tune_auto_swr));
  EEPROM_Read((uint8_t)&ee_tune_auto_enable, &global.tune_auto_enable, sizeof(global.tune_auto_enable));
  EEPROM_Read((uint8_t)&ee_sleep_delay_sec, &global.sleep_delay_sec, sizeof(global.sleep_delay_sec));
  EEPROM_Read((uint8_t)&ee_sleep_enable, &global.sleep_enable, sizeof(global.sleep_enable));  
  EEPROM_Read((uint8_t)&ee_cal_point_0, &global.cal_point[0], sizeof(global.cal_point[0]));
  EEPROM_Read((uint8_t)&ee_cal_point_1, &global.cal_point[1], sizeof(global.cal_point[1]));
  EEPROM_Read((uint8_t)&ee_cal_offset, &global.cal_offset, sizeof(global.cal_offset));
  EEPROM_Read((uint8_t)&ee_cal_gain, &global.cal_gain, sizeof(global.cal_gain));

  EEPROM_Read((uint8_t)&ee_flags, &global.flags, sizeof(global.flags));

// Stopgap so that an EEPROM which hasn't previously contained our flags byte
// is interpreted properly rather than treating the erased EEPROM value 0xFF
// as "all options enabled".

  if (global.flags == 0xFF)
  {
    global.flags = 0x00;
  }
  
}


void EEPROM_Write(uint8_t addr, void *ptrValue, uint8_t size)
{
  uint8_t *ptr = ptrValue;
    while(size >0)
    {
        eeprom_write(addr, *ptr);
        size--;
        addr++;
        ptr++;
    }
}


void EEPROM_Read(uint8_t addr, void *ptrValue, uint8_t size)
{
  uint8_t *ptr = ptrValue;
    while(size >0)
    {
        *ptr = eeprom_read(addr);
        size--;
        addr++;
        ptr++;
    }
}
