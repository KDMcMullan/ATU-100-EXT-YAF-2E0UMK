/**
 * ATU-100_EXT_YAF 
 * Yet Another Firmware
 * (presumably) by DG4SN, Sven
 *
 * Created on 30 Jun 2022
 * File:   tune.h
 * 
 * Modified 12-Sep-2026 2E0UMK
 * Explicitly typed tunestate_t as U8 to save variable space
 * 
 */
/* 
 * Author: sven
 *
 */

#ifndef TUNE_H
#define	TUNE_H

#include "defines.h"


#ifdef	__cplusplus
extern "C"
{
#endif


#define TUNE_MIN_PWR   10   //10 = 1W  

  
 
typedef uint8_t tunestate_t; // force U8 (default is likely U16)

enum
{
  TUNE_IDLE=1,
  TUNE_RUN=2,
  TUNE_BREAK=3,
  TUNE_PWRLOW=4,        
  TUNE_READY=5           
};  
  




extern tunestate_t TUNE_state;

void TUNE_Init(void);
void TUNE_Run(void);




#ifdef	__cplusplus
}
#endif

#endif	/* TUNE_H */

