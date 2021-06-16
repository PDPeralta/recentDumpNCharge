/*
 * adcMeasure.h
 *
 *  Created on: Jun 14, 2021
 *      Author: paulp
 */

#ifndef INC_ADCMEASURE_H_
#define INC_ADCMEASURE_H_

#include "SI_EFM8BB1_Register_Enums.h"

void ADC0_startConversion(void);
bool ADC0_isConversionComplete(void);
uint16_t ADC0_getResult(void);
uint16_t ADC0_convertSampleToMillivolts(uint16_t sample);



#endif /* INC_ADCMEASURE_H_ */
