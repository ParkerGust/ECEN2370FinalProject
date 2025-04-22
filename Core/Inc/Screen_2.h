#ifndef SCREEN_2_H_
#define SCREEN_2_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "LCD_Driver.h"
#include "Gyro.h"
#include "AI.h"

static bool player1turn = true;
static bool startPlayer1 = true;
static uint8_t column;

void Screen2_NewGame(void);

void Screen2_Display(void);

void Screen2_StartTimer(void);

void Screen2_Drop(void);

void Screen2_Move(void);

void Screen2_MoveAI(uint8_t);

void Screen2_CheckState(void);


#endif
