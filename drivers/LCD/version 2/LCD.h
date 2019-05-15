#include "MCAL/MCAL.h"

void delay_milli(int n);
void delay_micro(int n);
void LCD_init(void);
void LCD_init_V2(void);
void LCD_Init_Pins(void);
void LCD_CHAR(int num  );
void LCD_CMD(unsigned char command);
void LCD_STR(char * str,int position,int length);
void  display_num (int x);
void LCD_CHAR2(char num ,int p);
void ptintStringg(char* x,int begining,int firstOrSecond);

