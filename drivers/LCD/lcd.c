#include"lcd.h"
#include "tm4c123gh6pm.h"
void Uart_Init()
{
SYSCTL->RCGCUART |= 1; /* provide clock to UART */
SYSCTL->RCGCGPIO |= 1; /* enable clock to PORTA */
SYSCTL->RCGCGPIO |= 0x01; /* enable clock to PORTA */
 
 /* UART1 initialization */
 UART0->CTL = 0; /* disable UART0 */
 UART0->IBRD = 104; /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
 UART0->FBRD = 11; /* fraction part*/
 UART0->CC = 0; /* use system clock */
 UART0->LCRH = 0x60; /* 8-bit, no parity, 1-stop bit, no FIFO */
 UART0->CTL = 0x301; /* enable UART0, TXE, RXE */
 
 /* UART0 TX0 and RX0 use PA0 and PA1. Set them up. */
 GPIOA->DEN |= 0x03; /* Make PA0 and PA1 as digital */
 GPIOA->AFSEL |= 0x03; /* Use PA0,PA1 alternate function */
 GPIOA->PCTL |= 0x11; /* configure PA0 and PA1 for UART */
}
void LCD_init(void){

SYSCTL->RCGCGPIO |= 0x02;


GPIOB->DIR |=0xFC; //PORTB D4-D7
GPIOB->DEN |=0xFC; //PORTB D4-
delay_milli(20);
Lcd_Cmd(0x30);
delay_milli(5);
Lcd_Cmd(0x30);
delay_micro(100);
Lcd_Cmd(0x30);
	
Lcd_Cmd(0x28); //8-bits,2 display lines, 5x7 font
Lcd_Cmd(0x06); //increments automatically
Lcd_Cmd(0x01); //Turn on display
Lcd_Cmd(0x0F); //clear displa
 
}
void Lcd_Write(unsigned char data,unsigned char command ){


data &=0xF0;
command&=0x0F;
delay_micro(0);
GPIOB->DATA=data|command;
GPIOB->DATA=data|command|En;
delay_micro(0);
GPIOB->DATA=data;



}
 
void Lcd_Cmd(unsigned char command)
{

Lcd_Write(command&0xF0 ,0 ); //upper nibble
Lcd_Write(command<<4 ,0 );	
if(command <4) delay_milli(2); else delay_micro(40); } 

void Lcd_Data(unsigned char data) {
Lcd_Write(data&0xF0 , 0x08 );    //upper nibble
Lcd_Write(data<<4 , 0x08 );	
delay_micro(40);
}

void send_string(char *s){
   unsigned int i=0;
                for(;s[i]!=0;i++){
                 Lcd_Data(s[i]);
								delay_micro(40);
								}

}


void send_float(void){
while((UART0->FR & 0x10) != 0); /* wait until the buffer is not empty */
float myval = UART0->DR; 			
	
char mystring[ 5 ];
	
mystring[0] = 0;
mystring[1] = 0;
mystring[2] = '.';
mystring[3] = 0;
mystring[4] = 0;
while ( myval >= 10.0 ) {
  mystring[0]++;
    myval -= 10.0;
}

while ( myval >= 1.0 ) {
    mystring[1]++;
    myval -= 1.0;
}
while ( myval <= 0.9 && myval >= 0.1 ) {
   mystring[3]++;
   myval -= 0.1;
}
while ( myval >= 0.01 && myval < 0.1  ) {
   mystring[4]++;
   myval -= 0.01;
}
mystring[0] += 0x30;Lcd_Data(mystring[0]); delay_micro(40);
mystring[1] += 0x30;Lcd_Data(mystring[1]); delay_micro(40);

Lcd_Data(mystring[2]); delay_micro(40);
mystring[3] += 0x30;Lcd_Data(mystring[3]); delay_micro(40);
mystring[4] += 0x30;Lcd_Data(mystring[4]); delay_micro(40);

}
void delay_milli(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3180;j++)
{}
}
 
void delay_micro(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3;j++)
{}
}
void display(void) {
	
	
	Uart_Init();
        LCD_init();
	Lcd_Cmd(0x80);
	delay_milli(1000);
	send_string("TEMP :");
	delay_milli(1000);
	Lcd_Cmd(0xC0);
	delay_milli(500);
	send_string("cel:");
	delay_milli(1000);
	while (1){
	send_float();
	delay_milli(10000);
	
}
}
