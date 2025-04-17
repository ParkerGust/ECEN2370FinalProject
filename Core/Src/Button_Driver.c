#include "Button_Driver.h"



void Button_Init_Interrupt(){
	GPIO_InitTypeDef PinConfig;
	PinConfig.Mode = GPIO_MODE_IT_RISING;
	PinConfig.Speed = GPIO_SPEED_FREQ_MEDIUM;
	PinConfig.Pull = GPIO_NOPULL;
	PinConfig.Pin = GPIO_PIN_0;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &PinConfig);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

bool isPressed(){

	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == PRESSED){
		return true;
	}
	else{
		return false;
	}
}
