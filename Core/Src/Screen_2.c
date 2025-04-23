#include "Screen_2.h"


void Screen2_NewGame(void){
	LCD_Clear(0, LCD_COLOR_GREY);
	for (int i = 0; i<boardColumns; i++){
		for (int j = 0; j<boardRows; j++){
	        gameBoard[i][j] = 0;
		}
	}
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


void Screen2_StartTimer(void){

}

void Screen2_Drop(void){
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

void Screen2_Move(void){
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

void Screen2_MoveAI(void){

}

uint8_t Screen2_CheckState(void){
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
        if ((j+dir_j*k)>boardColumns || (j+dir_j*k)<0){
            return false;
        } 
        if (gameBoard[i][j] != gameBoard[i+dir_i*k][j+dir_j*k]){
            return false;
        }

    }
    return true;

}
