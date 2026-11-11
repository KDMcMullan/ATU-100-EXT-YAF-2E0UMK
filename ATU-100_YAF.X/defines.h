/*
 * ATU-100_EXT_YAF 
 * Yet Another Firmware
 * Author: DG4SN
 *
 * File:   defines.h
 * Created on 22 March 2022
 * 
 * Modified 23-June-2025 2E0UMK
 * Rotated the display. 
 * 
 * Modified 10-Aug-2025 2E0UMK
 * Added a little bit of credit to the About screen.
 * 
 * Modified 09-Sep-2026 2E0UMK
 * Added boolean flags for EEPROM storage of settings such as screen rotation.
 * 
 * Modified 10-Sep-2026 2E0UMK
 * Added debug flag and specified size of crystal freq.
 * 
 * Modified 11-Sep-2026 2E0UMK
 * Added comments describing the reverse-engineered cal variables.
 * 
 * Modified 12-Sep-2026 2E0UMK
 * Added extra bits (and removed bits) for the new sleep delay routines.
 * Added comments describing the reverse-engineered cal variables.
 * Added a 2us delay macro to speed up display refresh.
 * 
 * Modified 29-Sep-2026 2E0UMK
 * Added a new bit to indicate that the large font is to be employed.
 * 
 * Modified 01-Nov-2026 2E0UMK
 * Added defines for P0 and P1 and cal gain and offset for "Default"
 * hardware and QRP variant.
 * 
 * Modified 05-Nov-2026 2E0UMK
 * Added constants for DISP_LCD_WriteBitmap() ("sparse" write / erase.)
 * 
 * Modified 06-Nov-2026 2E0UMK
 * Added a switch and some parameters to facilitate a simulated RF input at
 * the ADC.
 * 
 */

#ifndef DEFINES_H
#define	DEFINES_H

#ifdef	__cplusplus
extern "C"
{
#endif

 
  
#include <xc.h>

//----------------------------------------------------------------------    
  
//  the internal oscillator is 16 Mhz
//  the xc8 compiler needs the crystal freq defined here

// Include debug with software uart  
// #define DEBUG_UART 

#define TRUE          1
#define FALSE         0  
  
#define DISPLAY_I2C_ADDR    0x78  
#define DISPLAY_INIT_DELAY  500  //ms

#define _XTAL_FREQ 16000000UL

//  the CPU clock is 4 Mhz, so to convert to microseconds, there are
//  4 clocks per usec

#define DELAY_5_US_CLOCKS 20
#define DELAY_5_us() _delay((unsigned long)(DELAY_5_US_CLOCKS))

#define DELAY_2_US_CLOCKS  8
#define DELAY_2_us() _delay((unsigned long)(DELAY_2_US_CLOCKS))

//#define DELAY_100_US_CLOCKS 400
//#define DELAY_100_us() _delay((unsigned long)(DELAY_100_US_CLOCKS))  

#define DELAY_1_MS_CLOCKS 4000  
#define DELAY_ms(x) UTILI_Delay_ms(x)

#define MAX_SWR                 999  //9.99 
#define SWR_FORWORD_THRESHOLD   100 //mV  

#define CAL_GAIN_MULTIPLIER      4096  
#define DIR_OUTPUT 0
#define DIR_INPUT 1  
  
#define UART_PIN_W LATAbits.LATA6
#define UART_PIN_DIR TRISAbits.TRISA6
  
#define BUTTON_TUNE_R       PORTBbits.RB0   
#define BUTTON_TUNE_DIR     TRISBbits.TRISB0 
#define BUTTON_TUNE_PULLUP  WPUBbits.WPUB0   

#define BUTTON_AUTO_R       PORTBbits.RB1   
#define BUTTON_AUTO_DIR     TRISBbits.TRISB1 
#define BUTTON_AUTO_PULLUP  WPUBbits.WPUB1  

#define BUTTON_BYPASS_R       PORTBbits.RB2   
#define BUTTON_BYPASS_DIR     TRISBbits.TRISB2 
#define BUTTON_BYPASS_PULLUP  WPUBbits.WPUB2    

#define n_Tx LATBbits.LATB2
#define p_Tx LATBbits.LATB0
    
#define LED_GREEN LATBbits.LATB2
#define LED_RED   LATBbits.LATB0
#define LED_GREEN_DIR TRISAbits.LATB2
#define LED_RED_DIR   TRISAbits.LATB0   

#define I2C_SCL_W LATBbits.LATB6
#define I2C_SDA_W LATBbits.LATB7 
#define I2C_SCL_DIR TRISBbits.TRISB6
#define I2C_SDA_DIR TRISBbits.TRISB7  
    
#define ADC_REVERSE_DIR TRISAbits.TRISA0  
#define ADC_REVERSE_SEL ANSELAbits.ANSA0    
#define ADC_REVERSE_CH  0
  
#define ADC_FORWARD_DIR TRISAbits.TRISA1  
#define ADC_FORWARD_SEL ANSELAbits.ANSA1   
#define ADC_FORWARD_CH  1  

#define REL_CAP_1           LATCbits.LATC7
#define REL_CAP_1_DIR       TRISCbits.TRISC7   
  
#define REL_CAP_2           LATCbits.LATC3
#define REL_CAP_2_DIR       TRISCbits.TRISC3
   
#define REL_CAP_3           LATCbits.LATC6
#define REL_CAP_3_DIR       TRISCbits.TRISC6  
  
#define REL_CAP_4           LATCbits.LATC2
#define REL_CAP_4_DIR       TRISCbits.TRISC2  
  
#define REL_CAP_5           LATCbits.LATC5
#define REL_CAP_5_DIR       TRISCbits.TRISC5  
  
#define REL_CAP_6           LATCbits.LATC1
#define REL_CAP_6_DIR       TRISCbits.TRISC1  
  
#define REL_CAP_7           LATCbits.LATC4
#define REL_CAP_7_DIR       TRISCbits.TRISC4  
  
#define REL_CAP_SW          LATCbits.LATC0
#define REL_CAP_SW_DIR      TRISCbits.TRISC0

#define REL_IND_1           LATBbits.LATB3
#define REL_IND_1_DIR       TRISBbits.TRISB3  
  
#define REL_IND_2           LATAbits.LATA2
#define REL_IND_2_DIR       TRISAbits.TRISA2    
  
#define REL_IND_3           LATBbits.LATB4
#define REL_IND_3_DIR       TRISBbits.TRISB4  

#define REL_IND_4           LATAbits.LATA3
#define REL_IND_4_DIR       TRISAbits.TRISA3  
  
#define REL_IND_5           LATBbits.LATB5
#define REL_IND_5_DIR       TRISBbits.TRISB5  
  
#define REL_IND_6           LATAbits.LATA5
#define REL_IND_6_DIR       TRISAbits.TRISA5    
  
#define REL_IND_7           LATAbits.LATA4 
#define REL_IND_7_DIR       TRISAbits.TRISA4      
 
//---- Boolean Flags and Macros -----------------------------------------------    

// these are bit positions (not masks)
#define FLAG_DISPLAY_ROTATE    0 // rotate display
#define FLAG_DEBUG             1 // show debug info
#define FLAG_WAKE_ON_RF        2 // 1 = Wake on RF, 0 = Button only (DigiMode)
#define FLAG_RELAY_SAVE        3 // 1 = Drop relays on sleep (QRP only), 0 = Keep match
#define FLAG_DISPLAY_LARGE     4 // large PWR/SWR display
#define FLAG_SIM_ADC           5 // use simulated ADC input    
//#define FLAG_6                 6
//#define FLAG_7                 7
#define FLAG_DISPLAY_ROTATE_MASK  (1 << FLAG_DISPLAY_ROTATE)
#define FLAG_DEBUG_MASK           (1 << FLAG_DEBUG)
#define FLAG_WAKE_ON_RF_MASK      (1 << FLAG_WAKE_ON_RF)
#define FLAG_RELAY_SAVE_MASK      (1 << FLAG_RELAY_SAVE)
#define FLAG_DISPLAY_LARGE_MASK   (1 << FLAG_DISPLAY_LARGE)
#define FLAG_SIM_ADC_MASK         (1 << FLAG_SIM_ADC)

//---- Default calibration gains and offsets for various hardware mods --------    
    
// NB: cal_gain 9600 compensates for real-world diode forward-voltage knee
// variations at typical HF frequencies.
// (No 1:5 tandem match (current) transformer (transcoupler) modification.)

#define DEF_CAL_OFFSET_STD     175
#define DEF_CAL_GAIN_STD     10100
#define DEF_CAL_P0_STD          50
#define DEF_CAL_P1_STD         250

#define DEF_CAL_OFFSET_QRP       0 // actually try -90.
#define DEF_CAL_GAIN_QRP      6580
#define DEF_CAL_P0_QRP          10
#define DEF_CAL_P1_QRP          30

//---- Write / clear flags for drawing teh LCD characters ---------------------    

#define LCD_WRITE_BITMAP       0 // constants for DISP_LCD_WriteBitmap()
#define LCD_CLEAR_SEGMENTS     1

//---- Parameters to create sawtooth mock ADC input for debugging -------------    
    
#define RAMP_MIN          0    // bottom of sawtooth
#define RAMP_MAX       1023    // 1023 would be 10-bit ADC full scale
#define RAMP_INC          7    // increment per ramp update
#define RAMP_PERIOD      20    // milliseconds between updates

//----------------------------------------------------------------------    

#define TUNEMEM_ITEMS      10
#define TUNEMEM_STRLEN      8  
  
#define SLEEP_WAKEUP_PWR    5 // = 0.5W
  
typedef struct
{
  uint16_t relays;
  char str_name[TUNEMEM_STRLEN];
}tunemem_t;  
  
//----------------------------------------------------------------------  
  
  typedef union
  {
      uint8_t byte;
      struct
      {
          unsigned B0 : 1;
          unsigned B1 : 1;
          unsigned B2 : 1;
          unsigned B3 : 1;
          unsigned B4 : 1;
          unsigned B5 : 1;
          unsigned B6 : 1;
          unsigned B7 : 1;
      } bits;
  } bitfield_t;  
  
  

const    int16_t CAP_VALUES[7] = {10, 22, 47, 100, 220, 470, 1000}; //Cap in pF
const    int16_t IND_VALUES[7] = {50, 100, 220, 450, 1000, 2200, 4400}; //Ind in nH
  
  
//Note: EEPROM values in global due to EEPROM address flexibility

typedef struct
  {
    int16_t PWR; // deciWatt -> 10 = 1W
    int16_t SWR; // 100 = 1.00

    int16_t tune_stop_swr;
    int16_t tune_auto_swr;
    uint8_t tune_auto_enable;
    
    uint8_t sleep_enable;
    int16_t sleep_delay_sec;

    uint8_t bypass_enable;
    uint16_t bypass_save_relays;
    
    int16_t cal_point[2]; // Holds the raw ADC samples corresponding to two known forward power references.
    int16_t cal_offset; // Sets the baseline noise floor in ADC counts or millivolts.
    int16_t cal_gain; // Global linear scaling factor to compensate for coupler transformer winding ratios (e.g., 1:10 turns) and diode attenuators.
    int16_t adc_r_mV;
    int16_t adc_f_mV;
    uint8_t cap_sw;
    uint8_t cap_relays;
    uint8_t ind_relays;

    uint8_t flags; // various Booleans
       
  } global_t;
  
 
//variables
  
  
global_t extern global;  

#include "uart.h"
#include "eeprom.h"
#include "utili.h"
#include "disp.h"
#include "button.h"
#include "menu.h"
#include "adc.h"  
#include "tune.h"  
  

const char str_ATU100EXT[] = "ATU-100";
const char str_YAF[]       = "EXT-YAF";
const char str_Version[]   =  "V0.69.6"; // 2E0UMK - LCD complete
const char str_YetAnother[] = "YetAnother";
const char str_Firmware[] = "Firmware";
const char str_Hardware[] = "Hardware";

const char str_designed[] = "designed";
const char str_by[] = "by";
const char str_N7DCC[] = "N7DDC";
const char str_DG4SN[] = "DG4SN";

const char str_Tweaks_by[] ="Tweaks by";
const char str_2E0UMK[] ="2E0UMK";

const char str_SWR[]   =  "SWR";
const char str_PWR[]   =  "PWR";

const char str_Large[] = "Large";

const char str_L_[]   =  "L=";
const char str_C_[]   =  "C=";

const char str_C_L[] = ">C-L";
const char str_L_C[] = ">L-C";

const char str__Tune_[] = " Tune ";

const char str_Esc[] = "Esc";

const char str_Off[] = "Off";
const char str_On[] = " On";
const char str_OK[] = "OK";

const char str_Power[] = "Power";
const char str_Point[] = "Point";

const char str_Delay[]  = "Delay";
const char str_Sleep[]  = "Sleep";     // Sleep delay time
const char str_RFwake[]  = "RFwake";   // Wake on RF
const char str_RlySave[] = "RlySave";  // Relay save toggle

const char str_MENU_Display[] = "Display   ";
const char str_Normal[] = "Normal";
const char str_Rotate[] = "Rotate";

const char str_Auto[]     = "Auto";
const char str_Start[]    = "Start";
const char str_Stop[]     = "Stop";
const char str_Save[]     = "Save";
const char str_Standard[] = "Standard";

const char str_MENU_Debug[]         =  "Debug     ";
const char str_MENU_Reset[]         =  "Reset     ";
const char str_MENU_Bypass[]        =  "Bypass    ";
const char str_MENU_Save[]          =  "Save Tune ";
const char str_MENU_Load[]          =  "Load Tune ";
const char str_MENU_TunePar[]       =  "Tuning    ";
const char str_MENU_Sleep[]         =  "Sleep     ";
const char str_MENU_RelTest[]       =  "Test      ";
const char str_MENU_Cal[]           =  "Calibrate ";
const char str_MENU_Setup[]         =  "Setup     ";
const char str_MENU_About[]         =  "About     ";
const char str_MENU_Hardware[]      =  "Hardware  "; // spaces so they work as a menu item

const char str_SpaceLine[] = "          "; // FUTURE: shorten these strings and use the center function
const char str_WaitForHF[] = " Await Tx ";
const char str_Running[]   = " Running  "; 
const char str_Break[]     = "  Break   ";
const char str_PWR_low[]   = " PWR low  ";
const char str_Ready[]     = "  Ready   ";

const char* str_TUNE_State[6] = {
  str_SpaceLine,
  str_WaitForHF,
  str_Running,
  str_Break,
  str_PWR_low,
  str_Ready };


 const char NameEditChar[] =" 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ?!/+-#%$_";

 
#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */

