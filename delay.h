/*
 * delay.h
 *
 *  Created on: May 7, 2021
 *      Author: paulp
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "intrins.h"
#include "globals.h" // F_CPU and CPU_DIV

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define SYSCLK_MS  ((F_CPU / CPU_DIV) / 1000.0) / 60.0 // Convert to oscillations per ms
#define SYSCLK_US  ((F_CPU / CPU_DIV) / 1000000.0) // Convert to oscillations per us
#define SUBSTRACT_MS 7500.0 / 60.0 / CPU_DIV

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void _delay_ms(uint32_t ms);
void _delay_us(uint16_t us);

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

/* _______________________________________________________________
 *   _delay_ms - works only with CPU_DIV 8 or less
 *
 *  Calculates the number of NOPs for a delay in milliseconds
 * Relatively accurate
 *  @param [ms] number of milliseconds to delay
 * _______________________________________________________________*/
void _delay_ms(uint32_t ms){
 // Substract n clock cycles for every ms to account for the time that the loop takes
 uint32_t clockCycles = SYSCLK_MS * ms;
 uint32_t substract = (SUBSTRACT_MS * ms) + 34;

 if(clockCycles > substract) clockCycles -= substract;

 while(clockCycles-- > 0){
  _nop_();
 }
}


/* _______________________________________________________________
 *   _delay_us - works only with CPU_DIV 1
 *
 *  Calculates the number of NOPs for a delay in microseconds
 *  Not very accurate
 *  @param [us] number of microseconds to delay
 * _______________________________________________________________*/
void _delay_us(uint16_t us){
 uint16_t clockCycles = (1 * us) + 55;

 while(clockCycles-- > 0){
  _nop_();
 }
}



#endif /* INC_DELAY_H_ */
