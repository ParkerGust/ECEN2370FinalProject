
#include "stm32f4xx_hal.h"

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PERSON 1
#define AI 2
#define boardColumns 7
#define boardRows 6

int scoreDirection(uint8_t board[boardColumns][boardRows], int i, int j, int dir_i, int dir_j);
int scorePosition(uint8_t board[boardColumns][boardRows], int i, int j);
int scoreMove(uint8_t board[boardColumns][boardRows]);
int moveAI(uint8_t gameBoard[boardColumns][boardRows]);

uint8_t checkState(uint8_t checkBoard[boardColumns][boardRows]);
bool checkDirection(uint8_t checkBoard[boardColumns][boardRows], int i, int j, int dir_i, int dir_j);


#endif /* INC_APPLICATIONCODE_H_ */