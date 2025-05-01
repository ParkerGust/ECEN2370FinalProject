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
uint32_t lastMoveTime = 0;


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
	Screen2_DisplayBoard();
	playGame();
}

void playGame(void){
	while (winner == 0){
		Screen2_DisplayMoveChip();
		if(TwoPlayerMode == false && player1turn == false){
			chipLoc = moveAI();
			drop();
			Screen2_DisplayBoard();
		}
		else{
			moveGyro();
		}
		Screen2_DisplayMoveChip();
		winner = checkState(gameBoard);
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
    Screen2_DisplayBoard();
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

uint8_t checkState(uint8_t checkBoard[boardColumns][boardRows]){
    int playerChecking = 0;
    dropped = false;
    for (int i = 0; i< boardColumns; i++){
        for (int j = 0; j < boardRows; j++){
            playerChecking = checkBoard[i][j];
            if (playerChecking != 0){
                if (checkDirection(checkBoard, i, j, 1, 0)|| //checking horizontal
                    checkDirection(checkBoard, i, j, 0, 1)|| //checking vertical 
                    checkDirection(checkBoard, i, j, 1, 1)|| //checking / diagonal
                    checkDirection(checkBoard, i, j, 1, -1)){ //checking \ diagonal
                        return checkBoard[i][j];
                }
            }
        }
    }
	return 0;
}
bool checkDirection(uint8_t checkBoard[boardColumns][boardRows], int i, int j, int dir_i, int dir_j){
    for (int k = 1; k < 4; k++){
        if ((i+dir_i*k)>=boardColumns || (i+dir_i*k)<0){
            return false;
        } 
        if ((j+dir_j*k)>=boardRows || (j+dir_j*k)<0){
            return false;
        } 
        if (checkBoard[i][j] != checkBoard[i+dir_i*k][j+dir_j*k]){
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
    LCD_DisplayChar(20, 25, 'C');
    LCD_DisplayChar(40, 25, 'O');
    LCD_DisplayChar(60, 25, 'N');
    LCD_DisplayChar(80, 25, 'N');
    LCD_DisplayChar(100, 25, 'E');
    LCD_DisplayChar(120, 25, 'C');
    LCD_DisplayChar(140, 25, 'T');
    LCD_DisplayChar(180, 25, '4');

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

void Screen2_DisplayBoard(void){
    LCD_Clear(0, LCD_COLOR_GREY);
    
    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(20, 25, 'C');
    LCD_DisplayChar(40, 25, 'O');
    LCD_DisplayChar(60, 25, 'N');
    LCD_DisplayChar(80, 25, 'N');
    LCD_DisplayChar(100, 25, 'E');
    LCD_DisplayChar(120, 25, 'C');
    LCD_DisplayChar(140, 25, 'T');
    LCD_DisplayChar(180, 25, '4');

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

void Screen2_DisplayMoveChip(void){
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

}

void Screen3_Display(void){
    LCD_Clear(0, LCD_COLOR_GREY);
    
    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(20, 15, 'C');
    LCD_DisplayChar(40, 15, 'O');
    LCD_DisplayChar(60, 15, 'N');
    LCD_DisplayChar(80, 15, 'N');
    LCD_DisplayChar(100, 15, 'E');
    LCD_DisplayChar(120, 15, 'C');
    LCD_DisplayChar(140, 15, 'T');
    LCD_DisplayChar(180, 15, '4');

    char score1 = (char)(player1_Score+48);
	char score2 = (char)(player2_Score+48);

    LCD_SetFont(&Font12x12);
	LCD_DisplayChar(20, 40, 'P');
    LCD_DisplayChar(30, 40, 'L');
    LCD_DisplayChar(40, 40, 'A');
    LCD_DisplayChar(50, 40, 'Y');
    LCD_DisplayChar(60, 40, 'E');
    LCD_DisplayChar(70, 40, 'R');
    LCD_DisplayChar(85, 40, '1');
    LCD_DisplayChar(25, 55, 'S');
    LCD_DisplayChar(35, 55, 'C');
    LCD_DisplayChar(45, 55, 'O');
    LCD_DisplayChar(55, 55, 'R');
	LCD_DisplayChar(65, 55, 'E');
	LCD_DisplayChar(75, 55, ':');
	LCD_DisplayChar(85, 55, score1);

    LCD_DisplayChar(140, 40, 'P');
    LCD_DisplayChar(150, 40, 'L');
    LCD_DisplayChar(160, 40, 'A');
    LCD_DisplayChar(170, 40, 'Y');
    LCD_DisplayChar(180, 40, 'E');
    LCD_DisplayChar(190, 40, 'R');
    LCD_DisplayChar(205, 40, '2');
    LCD_DisplayChar(145, 55, 'S');
    LCD_DisplayChar(155, 55, 'C');
    LCD_DisplayChar(165, 55, 'O');
    LCD_DisplayChar(175, 55, 'R');
	LCD_DisplayChar(185, 55, 'E');
	LCD_DisplayChar(195, 55, ':');
	LCD_DisplayChar(205, 55, score2);

	LCD_DisplayChar(40, 70, 'T');
	LCD_DisplayChar(50, 70, 'I');
	LCD_DisplayChar(55, 70, 'M');
	LCD_DisplayChar(65, 70, 'E');
	LCD_DisplayChar(80, 70, 'P');
	LCD_DisplayChar(90, 70, 'L');
	LCD_DisplayChar(100, 70, 'A');
	LCD_DisplayChar(110, 70, 'Y');
	LCD_DisplayChar(120, 70, 'E');
	LCD_DisplayChar(130, 70, 'D');

	uint32_t seconds = timePlayed/1000;
	uint32_t minutes = seconds/60;
	seconds = seconds-(minutes*60);
	char msb_min = (char)((minutes/10)+48);
	char lsb_min = (char)((minutes-((minutes/10)*10))+48);
	char msb_sec = (char)((seconds/10)+48);
	char lsb_sec = (char)((seconds-((seconds/10)*10))+48);
	LCD_DisplayChar(150, 70, msb_min);
	LCD_DisplayChar(160, 70, lsb_min);
	LCD_DisplayChar(167, 70, ':');
	LCD_DisplayChar(170, 70, msb_sec);
	LCD_DisplayChar(180, 70, lsb_sec);
    
    LCD_DisplayChar(15, 85, 'P');
	LCD_DisplayChar(25, 85, 'R');
	LCD_DisplayChar(35, 85, 'E');
	LCD_DisplayChar(45, 85, 'S');
	LCD_DisplayChar(55, 85, 'S');
	LCD_DisplayChar(70, 85, 'B');
	LCD_DisplayChar(80, 85, 'U');
	LCD_DisplayChar(90, 85, 'T');
	LCD_DisplayChar(100, 85, 'T');
	LCD_DisplayChar(110, 85, 'O');
    LCD_DisplayChar(120, 85, 'N');
    LCD_DisplayChar(135, 85, 'T');
    LCD_DisplayChar(145, 85, 'O');
    LCD_DisplayChar(160, 85, 'R');
    LCD_DisplayChar(170, 85, 'E');
    LCD_DisplayChar(180, 85, 'S');
    LCD_DisplayChar(190, 85, 'T');
    LCD_DisplayChar(200, 85, 'A');
    LCD_DisplayChar(210, 85, 'R');
    LCD_DisplayChar(220, 85, 'T');

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

int scoreDirection(uint8_t board[boardColumns][boardRows], int i, int j, int dir_i, int dir_j){
    int count = 0;
    int empty = 0;
    int dirScore =0;
    // score winability of the direction
    for (int k = 0; k < 4; k++) {
        if (!((i+dir_i*k)>=boardColumns || (i+dir_i*k)<0||(j+dir_j*k)>=boardRows || (j+dir_j*k)<0)){
            if(board[i+dir_i*k][j+dir_j*k] == board[i][j]){
                count++;
            }
            else if (board[i+dir_i*k][j+dir_j*k] == 0){
                empty++;
            }
        }
    }
    if (count == 3 && empty == 1) dirScore += 50;
    else if (count == 2 && empty == 2) dirScore += 10;
    return dirScore;
}
int scorePosition(uint8_t board[boardColumns][boardRows], int i, int j){
    int posScore = 0;
    //score winability of the position
    posScore += scoreDirection(board, i, j, 1,0);
    posScore += scoreDirection(board, i, j, 0,1);
    posScore += scoreDirection(board, i, j, 1,1);
    posScore += scoreDirection(board, i, j, 1,-1);
    return posScore;
}

int scoreMove(uint8_t board[boardColumns][boardRows]) {
    int score = 0;
    // prefers the center columns
    int center_col = boardColumns / 2;
    for (int row = 0; row < boardRows; row++) {
        if (board[center_col][row] == AI)
            score += 6; 
    }
    //score winability of the temp board
    for (int r = 0; r < boardRows; r++) {
        for (int c = 0; c < boardColumns; c++) {
            score += scorePosition(board, c, r);
        }
    }

    return score;
}

int moveAI() {
    int best_col = -1;
    int best_score = -1;

    for (int col = 0; col < boardColumns; col++) {
        if (gameBoard[col][0] == 0) {
            int row = 0;
            while (row < boardRows && gameBoard[col][row] == 0) {
                row++;
            }
            if (row == 0) continue; 
            row--;  // simulated row drop
        
            //check win
            uint8_t tempBoard[boardColumns][boardRows];
            for (int i = 0; i < boardColumns; i++) {
                for (int j = 0; j < boardRows; j++) {
                    tempBoard[i][j] = gameBoard[i][j];
                }
            }
            tempBoard[col][row] = 2;
            if (checkState(tempBoard) == 2) return col;
        
            //check block
            tempBoard[col][row] = 1;
            if (checkState(tempBoard) == 1) return col;
        
            //otherwise score move
            tempBoard[col][row] = 2;
            int score = scoreMove(tempBoard);
            if (score > best_score) {
                best_score = score;
                best_col = col;
            }
        }
    }

    return best_col;
}




	
void EXTI0_IRQHandler(){
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	if(winner == 0){
		drop();
        Screen2_DisplayBoard();
	}
	else{
		newGame();
	}
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
	

