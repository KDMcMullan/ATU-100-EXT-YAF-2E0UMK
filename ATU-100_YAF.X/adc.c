/**
 * ATU-100_EXT_YAF 
 * Yet Another Firmware
 * by DG4SN
 *
 *  * File:   defines.h
 * (Presumably) created around March 2022 by DG4SN
 *
 * Modified 05-Nov-2026 2E0UMK
 * Added a sawtooth pattern to simulate a forward RF during debugging.
 * Should have done that months ago!
 * 
 *
 * ADC functions
 */
#include "defines.h"

#define mV_per_Digit    4

#define AVERAGE_DEEP  10

static int16_t f_buffer[AVERAGE_DEEP];
static int16_t r_buffer[AVERAGE_DEEP];


void ADC_Init(void)
{

  //Set Ports
  //ANSELAbits.ANSELA = 0;

  ADC_REVERSE_DIR = DIR_INPUT;
  ADC_REVERSE_SEL = 1;

  ADC_FORWARD_DIR = DIR_INPUT;
  ADC_FORWARD_SEL = 1;




  FVRCON = 0b10000011; // ADC 4096 mV Vref
  //while (FVRCONbits.FVRRDY == 0);

  //ADCON1 settings 
  ADCON1bits.ADFM = 1; //right justified format 
  ADCON1bits.ADCS = 2; //Fosc/32

  ADCON1bits.ADNREF = 0; //negative Ref to Vss
  ADCON1bits.ADPREF = 3; //positive Ref to FVR module


  //ADCON0 settings
  ADCON0bits.ADON = 1;
}

int16_t ADC_GetSample(uint8_t ch)
{
  ADCON0bits.CHS = ch;
  DELAY_5_us();
  ADCON0bits.ADGO = 1; /* start A/D */
  while (ADCON0bits.ADGO == 1);
  int16_t hi = ADRESH;
  
  return (((hi << 8) + ADRESL) * mV_per_Digit);
  
}


void ADC_Run(void)
{
    static int16_t mock_adc = RAMP_MIN;
    static uint8_t ramp_up = 1;
    static uint8_t ramp_period_count = 0;

    int16_t f_sample;
    int16_t r_sample;

    int32_t f_sum = 0;
    int32_t r_sum = 0;

    uint8_t i;
    uint8_t s;

    // Generate mock ADC ramp when SimRF is enabled
    if (global.flags & FLAG_SIM_ADC_MASK)
    {
        // Update ramp every RAMP_PERIOD milliseconds
        if (++ramp_period_count >= RAMP_PERIOD)
        {
            ramp_period_count = 0;

            if (ramp_up)
            {
                mock_adc += RAMP_INC;

                if (mock_adc > RAMP_MAX)
                {
                    mock_adc = RAMP_MAX;
                    ramp_up = 0;
                }
            }
            else
            {
                mock_adc -= RAMP_INC;

                if (mock_adc < RAMP_MIN)
                {
                    mock_adc = RAMP_MIN;
                    ramp_up = 1;
                }
            }
        }

        // Convert raw ADC count to millivolts
        f_sample = mock_adc * mV_per_Digit;
        r_sample = 0;
    }
    else
    {
        // Read real ADC channels
        f_sample = ADC_GetSample(ADC_FORWARD_CH);
        r_sample = ADC_GetSample(ADC_REVERSE_CH);
    }

    // Move buffer
    s = 0;
    for (i = 0; i < (AVERAGE_DEEP - 1); i++)
    {
        s++;
        f_sum += f_buffer[i] = f_buffer[s];
        r_sum += r_buffer[i] = r_buffer[s];
    }

    f_sum += f_buffer[s] = f_sample;
    r_sum += r_buffer[s] = r_sample;

    // Calculate average
    global.adc_f_mV = (int16_t)(f_sum / AVERAGE_DEEP);
    global.adc_r_mV = (int16_t)(r_sum / AVERAGE_DEEP);

} // ADC_Run
