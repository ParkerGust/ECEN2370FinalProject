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

static uint32_t startTime;
static uint32_t endTime;
static uint32_t timePlayed;

static bool TwoPlayerMode;
static uint8_t chipLoc = 3;
static bool player1turn = true;
static bool startPlayer1 = true;
static bool dropped = false;
static uint8_t gameBoard[boardColumns][boardRows];
//static uint8_t gyroState=0;

#define FIRST_NAME_LENGTH 6


void ApplicationInit(void)
{
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);
	InitializeLCDTouch();
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
	playGame();
}

void playGame(void){
	while (winner == 0){
		Screen2_Display();
		if(TwoPlayerMode == false && player1turn == false){
			chipLoc = moveAI();
			drop();
		}
		else{
			moveGyro();
		}
		Screen2_Display();
		winner = checkState();
	}
	if(winner == 1){
		player1_Score++;
	}
	else{
		player2_Score++;
	}
	endTimer();
	Screen3_Display();
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
	}
	else{
		startPlayer1 = true;
	}
	winner = 0;
	for (int i = 0; i<boardColumns; i++){
		for (int j = 0; j<boardRows; j++){
	        gameBoard[i][j] = 0;
		}
	}
}


void drop(void){
    int j = 0;
    while (gameBoard[chipLoc][j] == 0 && j<6){
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
/*
void moveGyro(void){
    int16_t gyroLoc;
    gyroLoc = Gyro_GetYLoc();
    if(10000<gyroLoc || -10000>gyroLoc){
        if (10000<gyroLoc && chipLoc<6 && gyroState<2){
            gyroState++;
            HAL_Delay(500);
        }
        else if(chipLoc > 0 && gyroState<0){
            gyroState--;
            HAL_Delay(500);
        }
    }
    if (gyroState == 2 && chipLoc<6){
        chipLoc++;
        HAL_Delay(300);
        }
    else if(gyroState == 0 && chipLoc > 0){
        chipLoc--;
        	HAL_Delay(300);
        }
}
*/
#define DEBOUNCE_TIME 50 // ms
#define MOVE_THRESHOLD 5000
uint32_t lastMoveTime = 0;

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
uint8_t checkState(void){
    int playerChecking = 0;
    dropped = false;
    for (int i = 0; i< boardColumns; i++){
        for (int j = 0; j < boardRows; j++){
            playerChecking = gameBoard[i][j];
            if (playerChecking != 0){
                if (checkDirection(i, j, 1, 0)|| //checking horizontal
                    checkDirection(i, j, 0, 1)|| //checking vertical 
                    checkDirection(i, j, 1, 1)|| //checking / diagonal
                    checkDirection(i, j, 1, -1)){ //checking \ diagonal
                        return gameBoard[i][j];
                }
            }
        }
    }
	return 0;
}
bool checkDirection(int i, int j, int dir_i, int dir_j){
    for (int k = 1; k < 4; k++){
        if ((i+dir_i*k)>boardColumns || (i+dir_i*k)<0){
            return false;
        } 
        if ((j+dir_j*k)>boardRows || (j+dir_j*k)<0){
            return false;
        } 
        if (gameBoard[i][j] != gameBoard[i+dir_i*k][j+dir_j*k]){
            return false;
        }

    }
    return true;

}

void startTimer(void){
	startTime = HAL_GetTick();
}

void endTimer(){
    endTime = HAL_GetTick();
	timePlayed = endTime-startTime;
}


void Screen1_Display(void){
    LCD_Clear(0, LCD_COLOR_GREY);
    
    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(20, 20, 'C');
    LCD_DisplayChar(40, 20, 'O');
    LCD_DisplayChar(60, 20, 'N');
    LCD_DisplayChar(80, 20, 'N');
    LCD_DisplayChar(100, 20, 'E');
    LCD_DisplayChar(120, 20, 'C');
    LCD_DisplayChar(140, 20, 'T');
    LCD_DisplayChar(180, 20, '4');

    LCD_SetFont(&Font12x12);
    LCD_DisplayChar(20, 110, '1');
    LCD_DisplayChar(35, 110, 'P');
    LCD_DisplayChar(45, 110, 'L');
    LCD_DisplayChar(55, 110, 'A');
    LCD_DisplayChar(65, 110, 'Y');
    LCD_DisplayChar(75, 110, 'E');
    LCD_DisplayChar(85, 110, 'R');
    LCD_DisplayChar(40, 125, 'M');
    LCD_DisplayChar(50, 125, 'O');
    LCD_DisplayChar(60, 125, 'D');
    LCD_DisplayChar(70, 125, 'E');

    LCD_DisplayChar(140, 110, '2');
    LCD_DisplayChar(155, 110, 'P');
    LCD_DisplayChar(165, 110, 'L');
    LCD_DisplayChar(175, 110, 'A');
    LCD_DisplayChar(185, 110, 'Y');
    LCD_DisplayChar(195, 110, 'E');
    LCD_DisplayChar(205, 110, 'R');
    LCD_DisplayChar(160, 125, 'M');
    LCD_DisplayChar(170, 125, 'O');
    LCD_DisplayChar(180, 125, 'D');
    LCD_DisplayChar(190, 125, 'E');


    LCD_Draw_Circle_Fill(60, (LCD_PIXEL_HEIGHT/2)+20, 40, LCD_COLOR_RED);
    LCD_Draw_Circle_Fill(LCD_PIXEL_WIDTH-60, (LCD_PIXEL_HEIGHT/2)+20, 40, LCD_COLOR_BLUE);
}

void Screen2_Display(void){
    LCD_Clear(0, LCD_COLOR_GREY);
    
    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(20, 20, 'C');
    LCD_DisplayChar(40, 20, 'O');
    LCD_DisplayChar(60, 20, 'N');
    LCD_DisplayChar(80, 20, 'N');
    LCD_DisplayChar(100, 20, 'E');
    LCD_DisplayChar(120, 20, 'C');
    LCD_DisplayChar(140, 20, 'T');
    LCD_DisplayChar(180, 20, '4');
    
    for (int i = 0; i<boardColumns; i++){
        if (i == chipLoc){
            if (player1turn){
                LCD_Draw_Circle_Fill((i*30)+30, 80, 12, LCD_COLOR_BLUE);
            }
            else{
                LCD_Draw_Circle_Fill((i*30)+30, 80, 12, LCD_COLOR_RED);
            }
        }
        else{
            LCD_Draw_Circle_Fill((i*30)+30, 80, 12, LCD_COLOR_GREY);
        }
    }

    for (int i = 0; i<boardColumns; i++){
        for (int j = 0; j<boardRows; j++){
            if (gameBoard[i][j] == 1){
                LCD_Draw_Circle_Fill((i*30)+30, (j*30)+115, 12, LCD_COLOR_BLUE);
            }
            else if (gameBoard[i][j] == 2){
                LCD_Draw_Circle_Fill((i*30)+30, (j*30)+115, 12, LCD_COLOR_RED);
            }
            else{
                LCD_Draw_Circle_Fill((i*30)+30, (j*30)+115, 12, LCD_COLOR_BLACK);
            }
        }
    }
}

void Screen3_Display(void){
    LCD_Clear(0, LCD_COLOR_GREY);
    
    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(20, 20, 'C');
    LCD_DisplayChar(40, 20, 'O');
    LCD_DisplayChar(60, 20, 'N');
    LCD_DisplayChar(80, 20, 'N');
    LCD_DisplayChar(100, 20, 'E');
    LCD_DisplayChar(120, 20, 'C');
    LCD_DisplayChar(140, 20, 'T');
    LCD_DisplayChar(180, 20, '4');

    char score1 = (char)(player1_Score+48);
	char score2 = (char)(player2_Score+48);

    LCD_SetFont(&Font12x12);
	LCD_DisplayChar(20, 45, 'P');
    LCD_DisplayChar(30, 45, 'L');
    LCD_DisplayChar(40, 45, 'A');
    LCD_DisplayChar(50, 45, 'Y');
    LCD_DisplayChar(60, 45, 'E');
    LCD_DisplayChar(70, 45, 'R');
    LCD_DisplayChar(85, 45, '1');
    LCD_DisplayChar(25, 60, 'S');
    LCD_DisplayChar(35, 60, 'C');
    LCD_DisplayChar(45, 60, 'O');
    LCD_DisplayChar(55, 60, 'R');
	LCD_DisplayChar(65, 60, 'E');
	LCD_DisplayChar(75, 60, ':');
	LCD_DisplayChar(85, 60, score1);

    LCD_DisplayChar(140, 45, 'P');
    LCD_DisplayChar(150, 45, 'L');
    LCD_DisplayChar(160, 45, 'A');
    LCD_DisplayChar(170, 45, 'Y');
    LCD_DisplayChar(180, 45, 'E');
    LCD_DisplayChar(190, 45, 'R');
    LCD_DisplayChar(205, 45, '2');
    LCD_DisplayChar(145, 60, 'S');
    LCD_DisplayChar(155, 60, 'C');
    LCD_DisplayChar(165, 60, 'O');
    LCD_DisplayChar(175, 60, 'R');
	LCD_DisplayChar(185, 60, 'E');
	LCD_DisplayChar(195, 60, ':');
	LCD_DisplayChar(205, 60, score2);

	LCD_DisplayChar(40, 80, 'T');
	LCD_DisplayChar(50, 80, 'I');
	LCD_DisplayChar(55, 80, 'M');
	LCD_DisplayChar(65, 80, 'E');
	LCD_DisplayChar(80, 80, 'P');
	LCD_DisplayChar(90, 80, 'L');
	LCD_DisplayChar(100, 80, 'A');
	LCD_DisplayChar(110, 80, 'Y');
	LCD_DisplayChar(120, 80, 'E');
	LCD_DisplayChar(130, 80, 'D');
	uint32_t seconds = timePlayed/1000;
	uint32_t minutes = seconds/60;
	seconds = seconds-(minutes*60);
	char msb_min = (char)((minutes/10)+48);
	char lsb_min = (char)((minutes-((minutes/10)*10))+48);
	char msb_sec = (char)((seconds/10)+48);
	char lsb_sec = (char)((seconds-((seconds/10)*10))+48);
	LCD_DisplayChar(150, 80, msb_min);
	LCD_DisplayChar(160, 80, lsb_min);
	LCD_DisplayChar(167, 80, ':');
	LCD_DisplayChar(170, 80, msb_sec);
	LCD_DisplayChar(180, 80, lsb_sec);

    for (int i = 0; i<boardColumns; i++){
        for (int j = 0; j<boardRows; j++){
            if (gameBoard[i][j] == 1){
                LCD_Draw_Circle_Fill((i*30)+30, (j*30)+115, 12, LCD_COLOR_BLUE);
            }
            else if (gameBoard[i][j] == 2){
                LCD_Draw_Circle_Fill((i*30)+30, (j*30)+115, 12, LCD_COLOR_RED);
            }
            else{
                LCD_Draw_Circle_Fill((i*30)+30, (j*30)+115, 12, LCD_COLOR_BLACK);
            }
        }
    }
    while (winner != 0);
    playGame();
}

uint8_t moveAI(){
	uint8_t playerChecking =0;
	for (int i = 0; i< boardColumns; i++){
        for (int j = 0; j < boardRows; j++){
            playerChecking = gameBoard[i][j];
            if (playerChecking != 0){
                if(WinOrBlock(i, j)<8){
                    return WinOrBlock(i, j);
                }
            }
        }
    }
	for (int i = 0; i< boardColumns; i++){
        for (int j = 0; j < boardRows; j++){
            playerChecking = gameBoard[i][j];
            if (playerChecking != 0){
				if(twoAway(i, j)<8){
					return twoAway(i, j);
				}
            }
        }
    }
	return 3;
}

uint8_t WinOrBlock(uint8_t i, uint8_t j){
	if(CheckWinningMove(i, j, 1, 0)<8){
		return CheckWinningMove(i, j, 1, 0);
	}
	if(CheckWinningMove(i, j, 0, 1)<8){
		return CheckWinningMove(i, j, 0, 1);
	}
	if(CheckWinningMove(i, j, 1, 1)<8){
		return CheckWinningMove(i, j, 1, 1);
	}
	if(CheckWinningMove(i, j, 1, -1)){
		return CheckWinningMove(i, j, 1, 0);
	}
	return 8;
}

uint8_t CheckWinningMove(int i, int j, int dir_i, int dir_j){
    for (int k = 1; k < 3; k++){
        if ((i+dir_i*k)>boardColumns || (i+dir_i*k)<0){
            return 8;
        }
        if ((j+dir_j*k)>boardRows || (j+dir_j*k)<0){
            return 8;
        }
        if (gameBoard[i][j] != gameBoard[i+dir_i*k][j+dir_j*k]){
            return 8;
        }
    }
	if((i+dir_i*4)>boardColumns || (j+dir_j*4)>boardRows || gameBoard[i+dir_i*4][j+dir_j*4] != 0){
		return 8;
	}
    return i+dir_i*4;

}

uint8_t twoAway(uint8_t i, uint8_t j){
	if(CheckTwoAway(i, j, 1, 0)<8){
		return CheckTwoAway(i, j, 1, 0);
	}
	if(CheckTwoAway(i, j, 0, 1)<8){
		return CheckTwoAway(i, j, 0, 1);
	}
	if(CheckTwoAway(i, j, 1, 1)<8){
		return CheckTwoAway(i, j, 1, 1);
	}
	if(CheckTwoAway(i, j, 1, -1)){
		return CheckTwoAway(i, j, 1, 0);
	}
	return 8;
}

uint8_t CheckTwoAway(int i, int j, int dir_i, int dir_j){
    for (int k = 1; k < 2; k++){
        if ((i+dir_i*k)>boardColumns || (i+dir_i*k)<0){
            return 8;
        }
        if ((j+dir_j*k)>boardRows || (j+dir_j*k)<0){
            return 8;
        }
        if (gameBoard[i][j] != gameBoard[i+dir_i*k][j+dir_j*k]){
            return 8;
        }
    }
	if((i+dir_i*3)>boardColumns || (j+dir_j*3)>boardRows || gameBoard[i+dir_i*3][j+dir_j*3] != 0){
		return 8;
	}
    return i+dir_i*3;

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
	if(winner == 0){
		drop();
	}
	else{
		newGame();
	}
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
	

