/** 
 * @file Display.h
 * @brief Programs the display to output various screens
 */

#include "stm32f4xx_hal.h"

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdio.h>
#include <stdbool.h>
#include "LCD_Driver.h"

#define boardColumns 7
#define boardRows 6

/** 
 * @brief initializes the display and touch functionality
 */
void Display_Init(void);

/** 
 * @brief displays 1 or 2 player mode choice screen (startup)
 */
void Screen1_Display(void);
/** 
 * @brief displays the board and connect 4 lettering while playing the game 
 * @param gameBoard is the current board state
 */
void Screen2_DisplayBoard(uint8_t gameBoard[boardColumns][boardRows]);
/** 
 * @brief displays the moving chip at its given location
 * @param chipLoc current location of the chip
 * @param player1turn boolean of whos turn it is 
 */
void Screen2_DisplayMoveChip(uint8_t chipLoc, bool player1turn);
/** 
 * @brief displays end game screen with scores and time played
 * @param gameBoard is winned board state
 * @param player1_Score player 1's score 
 * @param player2_Score player 2's score 
 */
void Screen3_Display(uint8_t gameBoard[boardColumns][boardRows], uint8_t player1_Score, uint8_t player2_Score);

/** 
 * @brief starts the game timer
 */
void startTimer(void);
/** 
 * @brief ends the game timer
 */
void endTimer(void);

#endif