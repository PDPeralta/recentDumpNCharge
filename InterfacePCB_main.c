//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                // SFR declarations
#include <main.h>
#include <temperature.h>
#include <delay.h>
#include <Functions.h>
#include <globals.h>
#include <InitDevice.h>
#include <pins.h>
//-----------------------------------------------------------------------------


// SiLabs_Startup() Routine
void SiLabs_Startup (void)
{
  // Disable the watchdog here
}

//External Variables--------------------------
extern uint32_t batt_adc_mV;
extern uint32_t dadbod_mV;
//extern uint8_t sysTick;

enum { IDLE, CRG_INT, CRG_EXT, JUMP, CRG_ERROR, ERROR } state = IDLE;  //Initialize to IDLE state

int main (void)
{
  enter_DefaultMode_from_RESET();

  IE_EA = 1;                          // Enable global interrupts

  while (1) {

//   while (sysTick == 1){}  //  <-- better way of implementing delay.
//    sysTick = 1;

      _delay_ms(100);   //Delay 100ms

      adcMeasure();     //Initiate ADC conversion & stores pin voltages into variables

      temp_Celsius = GetTemperature();   //Read converted temperature into temp_Celsius variable

      if (temp_Celsius >= temp_max)   // Temp. check prior to entering state machine
        {
          state = ERROR;
        }

      switch (state){

          case IDLE:

//                      AC present             Int. Bat. low              No RP detected             temp. good
                  if ( (DC_CNT != 0) && (batt_adc_mV < Vintbat_low) && (dadbod_mV <= V_rpn) && (temp_Celsius < temp_max) )
                    {
                      transition_IntCrg();
                    }
//                            AC present          Int. Bat. good                Ext. Bat. Detected           No RP detected       No Jump Signal            temp. good
                  else if ( (DC_CNT != 0) && (batt_adc_mV > Vintbat_low) && (dadbod_mV >= Vbat_detect) && (dadbod_mV <= V_rpn) && (JUMP_DET != 0) && (temp_Celsius < temp_max) )
                    {
                      transition_ExtCrg();
                    }
//                             Int. Bat. good                  Ext. Bat. Detected           No RP detected         Jump Detected           temp. good
                  else if ( (batt_adc_mV > Vintbat_low) && (dadbod_mV >= Vbat_detect) && (dadbod_mV <= V_rpn) && (JUMP_DET == 0) && (temp_Celsius < temp_max) )
                    {
                      transition_Jump();
                    }
//                               RP Detected             temp. Too High
                  else if ( (dadbod_mV >= V_rpn) || (temp_Celsius > temp_max) )
                    {
                      transition_Error();
                    }
                  else {}

          break;

          case CRG_INT:
            if  ( (DC_CNT == 0) || (temp_Celsius >= temp_max) )
                {
                  state = ERROR;
                }
            else if (batt_adc_mV > Vintbat_low)  //-- Were we going to have some hysteresis implemented with a V_intbat_stable value??
                {
                  transition_Idle();
                }

          break;

          case CRG_EXT:

              if ( temp_Celsius > temp_max )
                {
                  state = ERROR;
                }
              else if (DC_CNT == 0)   //AC Disconnected
                {
                  state = CRG_ERROR;
                }
              else if (dadbod_mV > V_extbat_full)     //Charge internal battery Overrides if low voltage detected
                {
                  transition_Idle();
                }

          break;

          case JUMP:

              if ( (dadbod_mV > V_rpn) || (temp_Celsius >= temp_max) )
                {
                  state = ERROR;
                }
              else if ( (batt_adc_mV < Vintbat_low) || (dadbod_mV < Vbat_detect) )  //Int. Batt. voltage drops too low, jump acc. disconnected, or leads are taken off of battery
                {
                  transition_Idle();            //--Actual battery voltage might drop during a jump
                }

          break;

          case CRG_ERROR:
//                  AC Detected       Ext. Bat. Disconnected
              if ( (DC_CNT != 0) || (dadbod_mV <= Vbat_detect) )
                {
                  transition_Idle();
                }

          break;

          case ERROR:
//                   RPN corrected                temp. good
              if ( (dadbod_mV < V_rpn) && (temp_Celsius < temp_Stable) )
                {
                  transition_Idle();
                }

          break;

      }       //end switch statement

  }       //end while loop
}  //end main

