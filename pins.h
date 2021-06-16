/*
 * pins.h
 *
 *  Created on: Jun 1, 2021
 *      Author: paulp
 */

#ifndef INC_PINS_H_
#define INC_PINS_H_


#include <SI_EFM8BB1_Register_Enums.h>                // SFR declarations



//Pin Name Assignments------------------------------
SI_SBIT(LED_ON, SFR_P0, 4);
SI_SBIT(LED_RED, SFR_P0, 5);
SI_SBIT(DC_CNT, SFR_P0, 7);
SI_SBIT(JUMP_OUT, SFR_P1, 0);
SI_SBIT(JUMP_DET, SFR_P1, 1);
SI_SBIT(AC_OUT, SFR_P1, 2);
SI_SBIT(OUTPUT, SFR_P1, 4);
SI_SBIT(DC_OUT, SFR_P1, 5);
SI_SBIT(CRG_OUT, SFR_P1, 6);


#endif /* INC_PINS_H_ */
