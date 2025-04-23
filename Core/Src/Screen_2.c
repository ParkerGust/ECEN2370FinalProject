#include "Screen_2.h"


void Screen2_NewGame(void){
	for (int i = 0; i<boardRows; i++){
		for (int j = 0; j<boardColumns; j++){
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
    while (gameBoard[chipLoc][j] == 0){
        j++;
    }
    if (player1turn){
        gameBoard[chipLoc][j-1] = 1;
    }
    else{
        gameBoard[chipLoc][j-1] = 2;
    }
    player1turn != player1turn;
    chipLoc = 3;
    dropped = true;
}

void Screen2_Move(void){
    if ()
    STMPE811_TouchData touch;
    touch.pressed = STMPE811_State_Released;
    while(touch.pressed == STMPE811_State_Released && dropped == false){
        returnTouchStateAndLocation(&touch);
    }
    if(touch.pressed == STMPE811_State_Pressed){
        if (touch.x < LCD_PIXEL_WIDTH/2){
            chipLoc--;
        }
        else{
            chipLoc++
        }
    }
}

void Screen2_MoveAI(uint8_t){

}

void Screen2_CheckState(void){

}
