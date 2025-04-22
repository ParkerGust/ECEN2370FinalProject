/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */


#include "stm32f4xx_hal.h"

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

#include <stdio.h>
#include "Screen_1.h"
#include "Screen_2.h"
#include "Screen_3.h"

void ApplicationInit(void);
void LCD_Visual_Demo(void);

void startGame(void)
void appDelay(uint32_t delayTime);



#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1)

#endif /* INC_APPLICATIONCODE_H_ */
