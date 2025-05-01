/*
 * ApplicationCode.c
 *
 *      Author: Parker
 */

#include "ApplicationCode.h"

/* Static variables */

static uint8_t winner;
static uint8_t player1_Score;
static uint8_t player2_Score;

static bool TwoPlayerMode;
static uint8_t chipLoc = 3;
static bool player1turn = true;
static bool startPlayer1 = false;
static bool dropped = false;
static uint8_t gameBoard[boardColumns][boardRows];
uint32_t lastMoveTime = 0;


void ApplicationInit(void){
    Display_Init();
	Gyro_Init();
    HAL_Delay(100);
	Button_Init_Interrupt();
	startGame();
}

void startGame(void){
	Screen1_Display();
	checkPlayerMode();
	startTimer();
	winner = 0;
	newGame();
	Screen2_DisplayBoard(gameBoard);
    playGame();
}

void playGame(void){
	while (winner == 0){
		Screen2_DisplayMoveChip(chipLoc, player1turn);
		if(TwoPlayerMode == false && player1turn == false){
			chipLoc = moveAI(gameBoard);
			drop();
			Screen2_DisplayBoard(gameBoard);
		}
		else{
			moveGyro();
		}
		Screen2_DisplayMoveChip(chipLoc, player1turn);
		winner = checkState(gameBoard);
	}
	if(winner == 1){
		player1_Score++;
	}
	else{
		player2_Score++;
	}
	endTimer();
	Screen3_Display(gameBoard, player1_Score, player2_Score);
    while (winner != 0); // waiting for button interrupt
}


void checkPlayerMode(void){
	STMPE811_TouchData touch;
	touch.pressed = STMPE811_State_Released;
	while(touch.pressed == STMPE811_State_Released){
		returnTouchStateAndLocation(&touch);
	}
	if (touch.x > LCD_PIXEL_WIDTH/2){
		TwoPlayerMode = LEFT_TOUCH;
	}
	else{
		TwoPlayerMode = RIGHT_TOUCH;
	}
}

void newGame(void){
	startTimer();
	LCD_Clear(0, LCD_COLOR_GREY);
	if (startPlayer1 == true){
        startPlayer1 = false;
		player1turn = false;
	}
	else{
        startPlayer1 = true;
		player1turn = true;
	}
	winner = 0;
	for (int i = 0; i<boardColumns; i++){
		for (int j = 0; j<boardRows; j++){
	        gameBoard[i][j] = 0;
		}
	}
    chipLoc = 3;
    Screen2_DisplayBoard(gameBoard);
}


void drop(void){
    int j = 0;
    while (gameBoard[chipLoc][j] == 0 && j<boardRows){
        j++;
    }
    if(j>0){
		if (player1turn){
			gameBoard[chipLoc][j-1] = 1;
			player1turn = false;
		}
		else{
			gameBoard[chipLoc][j-1] = 2;
			player1turn = true;
		}
		chipLoc = 3;
		dropped = true;
    }
}

void move(void){
    STMPE811_TouchData touch;
    touch.pressed = STMPE811_State_Released;
    while(touch.pressed == STMPE811_State_Released && dropped == false){
        returnTouchStateAndLocation(&touch);
    }
    if(touch.pressed == STMPE811_State_Pressed){
        if (touch.x < LCD_PIXEL_WIDTH/2 && chipLoc<6){
            chipLoc++;
        }
        else if(chipLoc > 0){
            chipLoc--;
        }
    }
}



void moveGyro(void) {
    int16_t gyroLoc = Gyro_GetYLoc();
    uint32_t now = HAL_GetTick();

    if (now - lastMoveTime > DEBOUNCE_TIME) {
        if (gyroLoc > MOVE_THRESHOLD && chipLoc < 6) {
            chipLoc++;
            lastMoveTime = now;
        } else if (gyroLoc < -MOVE_THRESHOLD && chipLoc > 0) {
            chipLoc--;
            lastMoveTime = now;
        }
    }
}


	
void EXTI0_IRQHandler(){
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	if(winner == 0){
		drop();
        Screen2_DisplayBoard(gameBoard);
	}
	else{
		newGame();
	}
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
	

