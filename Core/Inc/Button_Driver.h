

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

// Pin AO is user button
#define BUTTON_PORT 0
#define BUTTON_PIN 0
#define PRESSED 1
#define UNPRESSED 0

void Button_Init();
void Button_Init_Interrupt();
bool isPressed();


#endif

