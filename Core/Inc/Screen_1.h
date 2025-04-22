#ifndef SCREEN_1_H_
#define SCREEN_1_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "LCD_Driver.h"


void Screen1_Display(void);

uint8_t Screen1_Poll(void);


#endif