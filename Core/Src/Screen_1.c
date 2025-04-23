#include "Screen_1.h"


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


void Screen1_CheckPlayerMode(void){
	STMPE811_TouchData touch;
	touch.pressed = STMPE811_State_Released;
	while(touch.pressed == STMPE811_State_Released){
		returnTouchStateAndLocation(&touch);
	}
	if (touch.x < LCD_PIXEL_WIDTH/2){
		TwoPlayerMode = LEFT_TOUCH;
	}
	TwoPlayerMode = RIGHT_TOUCH;
}
