
/** 
 * @file ApplicationCode.h
 * @brief runs the game and stores static game variables
 */

#include "stm32f4xx_hal.h"

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

#define GYRO_MOVEMENT 1 //Compile swith for gyro movement

#include <stdio.h>
#include <stdbool.h>
#if GYRO_MOVEMENT
#include "Gyro.h"
#endif

#include "AI.h"
#include "Display.h"
#include "Button_Driver.h"

void ApplicationInit(void);

#define boardColumns 7
#define boardRows 6
#define ONE_PLAYER_MODE 0
#define TWO_PLAYER_MODE 1 
#if GYRO_MOVEMENT
#define DEBOUNCE_TIME 80 // ms
#define MOVE_THRESHOLD 2000
#else
#define DEBOUNCE_TIME 150 // ms

#endif

/** 
 * @brief Checks whether its one player mode or two player mode based on touch inputs and saves to static variable
 */
void checkPlayerMode(void);
/** 
 * @brief Creates a new gameboard, flips the starting player, and starts the timer
 */
void newGame(void);

/** 
 * @brief drops the chip to the lowest location for the given column in gameboard triggered by button interrupt or in AI sequence
 */
void drop(void);

/** 
 * @brief move function to change the column that the chip hovers over gyro or touch controlled based on compile switch
 */
#if GYRO_MOVEMENT
void moveGyro(void);
#else
void move(void);
#endif

/** 
 * @brief loop that runs the program to play the game 
 */
void playGame(void);

/** 
 * @brief starts a new game and sets scores to zero, displays screen 1 and sets player mode
 */
void startGame(void);

void appDelay(uint32_t delayTime);


#endif /* INC_APPLICATIONCODE_H_ */
