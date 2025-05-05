/** 
 * @file AI.h
 * @brief functionality for the AI and checking the board for winners included in application code
 */

#include "stm32f4xx_hal.h"

#ifndef INC_AI_H_
#define INC_AI_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PERSON 1
#define AI 2
#define boardColumns 7
#define boardRows 6

/** 
 * @brief Calculates a score of a direction /, \, |, - 
 * @param board game board with test piece placed
 * @param i Column
 * @param j Row
 * @param dir_i if checking in column direction = 1 or -1
 * @param dir_j if checking in row direction = 1 or -1
 * @return the score in the given direction
 */
int scoreDirection(uint8_t board[boardColumns][boardRows], int i, int j, int dir_i, int dir_j);
/** 
 * @brief Calculates a score for the position by checking in all directions
 * @param board game board with test piece placed
 * @param i Column
 * @param j Row
 * @return the score with chip in the given position
 */
int scorePosition(uint8_t board[boardColumns][boardRows], int i, int j);
/** 
 * @brief Calculates a score for the board by checking all positions
 * @param board game board with test piece placed
 * @return  the score of the board with the chip in the position
 */
int scoreMove(uint8_t board[boardColumns][boardRows]);
/** 
 * @brief Moves the piece to the best position based on scores
 * @param gameBoard current game board with no test peices
 * @return best column for the chip to be placed in 
 */
int moveAI(uint8_t gameBoard[boardColumns][boardRows]);

/** 
 * @brief Checks if a game has been won given the board
 * @param checkBoard is a game board that you want checked
 * @return 0 if no winner, 1 if player 1 wins, 2 if player 2 wins
 */
uint8_t checkState(uint8_t checkBoard[boardColumns][boardRows]);

/** 
 * @brief helper function for checkState that checks in directions
 * @param checkBoard is a game board that you want checked
 * @param i Column
 * @param j Row
 * @param dir_i if checking in column direction = 1 or -1
 * @param dir_j if checking in row direction = 1 or -1
 * @return false if no winer, true if winner
 */
bool checkDirection(uint8_t checkBoard[boardColumns][boardRows], int i, int j, int dir_i, int dir_j);


#endif /* INC_APPLICATIONCODE_H_ */