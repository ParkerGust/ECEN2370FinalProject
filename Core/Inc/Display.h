
#include "stm32f4xx_hal.h"

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdio.h>
#include <stdbool.h>
#include "LCD_Driver.h"

#define boardColumns 7
#define boardRows 6

void Display_Init(void);

void Screen1_Display(void);
void Screen2_DisplayBoard(uint8_t gameBoard[boardColumns][boardRows]);
void Screen2_DisplayMoveChip(uint8_t chipLoc, bool player1turn);
void Screen3_Display(uint8_t gameBoard[boardColumns][boardRows], uint8_t player1_Score, uint8_t player2_Score);

void startTimer(void);
void endTimer(void);

#endif