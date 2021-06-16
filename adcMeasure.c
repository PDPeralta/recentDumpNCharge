/*
 * adcFunctions.c
 *
 *  Created on: Jun 1, 2021
 *      Author: paulp
 */

#include <SI_EFM8BB1_Register_Enums.h>
#include <adcMeasure.h>
#include <stdio.h>

// ADC Defines
//-----------------------------------------------------------------------------
#define VREF_MV         (3300UL)
#define ADC_MAX_RESULT  ((1 << 10)-1) // 10 bit ADC

uint32_t batt_adc_mV = 0;
uint32_t dadbod_mV = 0;
uint32_t temp_mV = 0;

int array1[30];
int n = 0;
int Max; int Min;

void adcMeasure()
{
  //--------Local Variables---------------
  uint32_t accumulator = 0;// Accumulator for averaging
  uint16_t measurements = 0;// Measurement counter (2048*3)
  uint32_t result = 0;

  for (measurements = 30; measurements > 0; --measurements)
    {
      ADC0_startConversion();                  //Start conversion
      while (!ADC0_isConversionComplete());    // Wait for conversion to complete
      ADC0CN0_ADBUSY = 0;                      //Terminate ADC conversion

      accumulator += ADC0_getResult();   //Store result into accumulator

      if ( array1[n] > array1[n-1] )
        {
          Max = array1[n];
        }

     if(measurements == 21)
       {
         result = accumulator / 10;
         accumulator = 0;
         batt_adc_mV = ADC0_convertSampleToMillivolts(result);

         array1[n] = ADC0_convertSampleToMillivolts(result);
         ++n;

         ADC0MX = ADC0MX_ADC0MX__ADC0P0; // Select PIN 0.1 to receive ADC values
       }

     if(measurements == 11)
       {
         result = accumulator / 10;
         accumulator = 0;
         dadbod_mV = ADC0_convertSampleToMillivolts(result);

         array1[n] = ADC0_convertSampleToMillivolts(result);
         ++n;

         ADC0MX = ADC0MX_ADC0MX__ADC0P0; // Select PIN 0.2 to receive ADC values
       }

     if(measurements == 1)
       {
         result = accumulator / 10;
         accumulator = 0;
         temp_mV = ADC0_convertSampleToMillivolts(result);

         array1[n] = ADC0_convertSampleToMillivolts(result);
         ++n;

         ADC0MX = ADC0MX_ADC0MX__ADC0P0; // // Select PIN 0.0 to receive ADC values
       }
    }
}

void ADC0_startConversion(void)
{
  uint8_t ADCM_save;

  // Save the conversion source and set to ADBUSY
  ADCM_save = ADC0CN0 & ADC0CN0_ADCM__FMASK;
  ADC0CN0 = (ADC0CN0 & ~ADC0CN0_ADCM__FMASK) | ADC0CN0_ADCM__ADBUSY;

  // Clear the conversion complete flag
  ADC0CN0_ADINT = 0;

  // Start a conversion by setting ADBUSY
  ADC0CN0_ADBUSY = 1;

  // Restore the conversion source
  ADC0CN0 |= ADCM_save;
}

bool ADC0_isConversionComplete(void)
{
  bool conversionComplete;
  conversionComplete = ADC0CN0_ADINT;
  return conversionComplete;
}

uint16_t ADC0_getResult(void)
{
  uint16_t result;
  result = ADC0;
  return result;
}

uint16_t ADC0_convertSampleToMillivolts(uint16_t sample)
{
  // The measured voltage applied to P1.7 is given by:
  //
  //                           Vref (mV)
  //   measurement (mV) =   --------------- * result (bits)
  //                       (2^10)-1 (bits)
  return ((uint32_t)sample * 3300) / ADC_MAX_RESULT;
}
