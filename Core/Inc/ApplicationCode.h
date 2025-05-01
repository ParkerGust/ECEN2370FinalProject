

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

void checkPlayerMode(void);
void newGame(void);

void drop(void);
#if GYRO_MOVEMENT
void moveGyro(void);
#else
void move(void);
#endif

void playGame(void);
void startGame(void);
void appDelay(uint32_t delayTime);


#endif /* INC_APPLICATIONCODE_H_ */
