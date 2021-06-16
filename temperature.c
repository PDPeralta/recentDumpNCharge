/*
 * temperature.c
 *
 *  Created on: Jun 9, 2021
 *      Author:
 */

#include <temperature.h>
#include <stdint.h>

#define NUM_ELEMENTS(a) (sizeof(a) / sizeof(*a))

extern uint32_t temp_mV;

typedef struct
{
    uint16_t adcv;    //Temp ADC mV
    int8_t temperature; //C
} tempuratureStruct_t;

//Based upon RT1 NCP18WF104
//R38 = TBD
tempuratureStruct_t code temperaturelookup[] =
{
    { 1008, -40 },
    { 779 , -35 },
    { 594 , -30 },
    { 451 , -25 },
    { 341 , -20 },
    { 258 , -15 },
    { 195 , -10 },
    { 149 , -5  },
    { 114 , 0 },
    { 88  , 5 },
    { 68  , 10  },
    { 53  , 15  },
    { 41  , 20  },
    { 33  , 25  },
    { 26  , 30  },
    { 21  , 35  },
    { 17  , 40  },
    { 13  , 45  },
    { 11  , 50  },
    { 9 , 55  },
    { 7 , 60  },
    { 6 , 65  },
    { 5 , 70  },
    { 4 , 75  },
    { 3 , 80  },
    { 3 , 85  },
    { 2 , 90  },
    { 2 , 95  },
    { 2 , 100 },
    { 2 , 105 },
    { 1 , 110 },
    { 1 , 115 },
    { 1 , 120 },
    { 1 , 125 }
};

int GetTemperature(void)
{
  uint16_t adcv = temp_mV;
  int j=NUM_ELEMENTS(temperaturelookup);
int i;
  for (i = 0; i < j; i++)
  {
    if (adcv > temperaturelookup[i].adcv)
    {
      return temperaturelookup[i].temperature;
    }
  }

  return 25;
}


