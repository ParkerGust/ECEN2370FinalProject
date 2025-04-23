/*
 * ApplicationCode.c
 *
 *      Author: Parker
 */

#include "ApplicationCode.h"

/* Static variables */

static bool playing = false;

#define FIRST_NAME_LENGTH 6

extern void initialise_monitor_handles(void); 

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);
	InitializeLCDTouch();
	startGame();
}

void startGame(void){
	Screen1_Display();
	Screen1_CheckPlayerMode();
	Screen2_StartTimer();
	playing = true;
	Screen2_NewGame();
	playGame();
}

void playGame(){
	while (playing == true){
		Screen2_Display();
		if(TwoPlayerMode == false && player1turn == false){
			Screen2_MoveAI();
		}
		else{
			Screen2_Move();
		}
		Screen2_Display();
		playing = Screen2_CheckState();
	}
}


void appDelay(uint32_t delayTime){
	char name[] = {'p','a','r','k','e','r'};
	[[maybe_unused]]char destinationArray[FIRST_NAME_LENGTH];
	for (int i = 0; i <delayTime; i++){
		for (int j = 0; j < FIRST_NAME_LENGTH; j++){
			destinationArray[j] = name[j];
		}
	}
}

	
void EXTI0_IRQHandler(){
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	if(playing){
		Screen2_Drop();
	}
	else{
		playing = true;
		Screen2_NewGame();
		Screen2_Display();
	}
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
	

