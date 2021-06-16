/*
 * main.h
 *
 *  Created on: Jun 10, 2021
 *      Author: paulp
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_


  uint8_t temp_Celsius = 0;

  //Local Variables
  uint16_t V_rpn = 2500;           //Threshold for Reverse Polarity, anything above 2V is assumed to be RPP
  uint16_t Vbat_detect = 2000;     //Minimum voltage to detect battery
  uint16_t Vintbat_low = 2000;     //Min. Threshold for charging internal battery, 12.5V voltage divided
  uint16_t Vemg_thresh = 1000;
  uint16_t V_extbat_full = 3000;  //MUST CORRESPOND TO 14.7V AFTER VOLTAGE DIVIDER

  uint16_t temp_max = 60;       //Should correspond to max temperature of 50 degrees Celsius
  uint16_t temp_Stable = 45;


#endif /* INC_MAIN_H_ */
