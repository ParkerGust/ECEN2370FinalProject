

#include "stm32f4xx_hal.h"

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

#include <stdio.h>
#include <stdbool.h>
#include "Gyro.h"
#include "AI.h"
#include "Display.h"
#include "Button_Driver.h"

void ApplicationInit(void);


#define boardColumns 7
#define boardRows 6
#define ONE_PLAYER_MODE 0
#define TWO_PLAYER_MODE 1 
#define DEBOUNCE_TIME 80 // ms
#define MOVE_THRESHOLD 2000

void checkPlayerMode(void);
void newGame(void);

void drop(void);
void move(void);
void moveGyro(void);


void playGame(void);
void startGame(void);
void appDelay(uint32_t delayTime);


#endif /* INC_APPLICATIONCODE_H_ */
