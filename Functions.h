/*
 * Functions.h
 *
 *  Created on: May 28, 2021
 *      Author: paulp
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

void transition_Idle();
void transition_IntCrg();
void transition_ExtCrg();
void transition_Jump();
void transition_Error();

void adcMeasure();

#endif /* INC_FUNCTIONS_H_ */
