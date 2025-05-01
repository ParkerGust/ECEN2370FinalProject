#include "Display.h"

static uint32_t startTime;
static uint32_t endTime;
static uint32_t timePlayed;

void Display_Init(void){
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);
	InitializeLCDTouch();
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

void Screen2_DisplayBoard(uint8_t gameBoard[boardColumns][boardRows]){
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

void Screen2_DisplayMoveChip(uint8_t chipLoc,  bool player1turn){
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

void Screen3_Display(uint8_t gameBoard[boardColumns][boardRows], uint8_t player1_Score, uint8_t player2_Score){
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

    LCD_SetTextColor(LCD_COLOR_BLUE);
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

    LCD_SetTextColor(LCD_COLOR_RED);
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

    LCD_SetTextColor(LCD_COLOR_BLACK);
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
	char sec_1 = (char)(((seconds / 1000) %10)+48);
	char sec_2 = (char)(((seconds / 100) %10)+48);
	char sec_3 = (char)(((seconds / 10) %10)+48);
	char sec_4 = (char)((seconds %10)+48);
	LCD_DisplayChar(150, 70, sec_1);
	LCD_DisplayChar(160, 70, sec_2);
	LCD_DisplayChar(170, 70, sec_3);
	LCD_DisplayChar(180, 70, sec_4);
    LCD_DisplayChar(190, 70, 's');
    
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
}

void startTimer(void){
	startTime = HAL_GetTick();
}

void endTimer(void){
    endTime = HAL_GetTick();
	timePlayed = endTime-startTime;
}