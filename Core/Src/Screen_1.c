#include "Screen_1.h"


void Screen1_Display(void){
    LCD_Clear(0, LCD_COLOR_GREY);
    
    LCD_SetFont(Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_DisplayChar(20, 20, 'C');
    LCD_DisplayChar(40, 20, 'O');
    LCD_DisplayChar(60, 20, 'N');
    LCD_DisplayChar(80, 20, 'N');
    LCD_DisplayChar(100, 20, 'E');
    LCD_DisplayChar(120, 20, 'C');
    LCD_DisplayChar(140, 20, 'T');
    LCD_DisplayChar(180, 20, '4');

}

uint8_t Screen1_Poll(void){
    return(0);
}