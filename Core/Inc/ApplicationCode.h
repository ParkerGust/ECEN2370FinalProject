

#include "stm32f4xx_hal.h"

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

#include <stdio.h>
#include <stdbool.h>
#include "LCD_Driver.h"
#include "Gyro.h"
#include  "AI.h"
#include "Button_Driver.h"

void ApplicationInit(void);
void LCD_Visual_Demo(void);


#define boardColumns 7
#define boardRows 6
#define ONE_PLAYER_MODE 0
#define TWO_PLAYER_MODE 1 
#define DEBOUNCE_TIME 80 // ms
#define MOVE_THRESHOLD 2000

void Screen1_Display(void);
void checkPlayerMode(void);

void newGame(void);

void Screen2_DisplayBoard(void);
void Screen2_DisplayMoveChip(void);

void startTimer(void);

void drop(void);

void move(void);
void moveGyro(void);

void Screen3_Display(void);
void endTimer();

void playGame(void);
void startGame(void);
void appDelay(uint32_t delayTime);


#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1)

#endif /* INC_APPLICATIONCODE_H_ */
