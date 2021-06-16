/*
 * Functions.c
 *
 *  Created on: May 28, 2021
 *      Author: paulp
 */
#include <Functions.h>
#include <pins.h>

extern enum { IDLE, CRG_INT, CRG_EXT, JUMP, CRG_ERROR, ERROR } state;  //Initialize to IDLE state



void transition_Idle()
{
  LED_RED = 0, LED_ON = 0, AC_OUT = 0, OUTPUT = 0, DC_OUT = 0, CRG_OUT = 0, JUMP_OUT = 0;

  state = IDLE;
}

void transition_IntCrg()
{
  LED_RED = 0, DC_CNT = 0, CRG_OUT = 0, JUMP_OUT = 0;
  LED_ON = 1, AC_OUT = 1, OUTPUT= 1, DC_OUT = 1;

  state = CRG_INT;
}

void transition_ExtCrg()
{
  LED_RED = 0, LED_ON = 0, DC_CNT = 0, DC_OUT = 0, JUMP_OUT = 0;
  AC_OUT = 1, OUTPUT = 1, CRG_OUT = 1;

  state = CRG_EXT;
}

void transition_Jump()
{
  LED_RED = 0, AC_OUT = 0, OUTPUT= 0, DC_OUT= 0, CRG_OUT = 0;
  LED_ON = 1, JUMP_OUT = 1;

  state = JUMP;
}

void transition_Error()
{
  LED_ON = 0, AC_OUT = 0, OUTPUT = 0, DC_OUT = 0, CRG_OUT = 0, JUMP_OUT = 0;
  LED_RED = 1;

  state = ERROR;
}

