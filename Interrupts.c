//=========================================================
// src/Interupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES			
#include <SI_EFM8BB1_Register_Enums.h>
#include <stdio.h>




uint8_t sysTick = 1;

SI_INTERRUPT(TIMER3_ISR, TIMER3_IRQn)
 {
   sysTick = 0;
 }

