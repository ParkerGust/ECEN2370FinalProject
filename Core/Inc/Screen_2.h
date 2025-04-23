#ifndef SCREEN_2_H_
#define SCREEN_2_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "LCD_Driver.h"
#include "Gyro.h"
#include "AI.h"

#define boardColumns 7
#define boardRows 6

static int chipLoc = 3;
static bool player1turn = true;
static bool startPlayer1 = true;
static bool dropped = false;
static int gameBoard[boardColumns][boardRows];

void Screen2_NewGame(void);

void Screen2_Display(void);

void Screen2_StartTimer(void);

void Screen2_Drop(void);

void Screen2_Move(void);

void Screen2_MoveAI(uint8_t);

bool Screen2_CheckState(void);


#endif
