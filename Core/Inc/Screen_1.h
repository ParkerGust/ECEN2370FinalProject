#ifndef SCREEN_1_H_
#define SCREEN_1_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "LCD_Driver.h"

static bool TwoPlayerMode;
#define ONE_PLAYER_MODE 0
#define TWO_PLAYER_MODE 1 

void Screen1_Display(void);
void Screen1_CheckPlayerMode(void);

#endif