#include "UART22.h"


void SendChar_u2(char x){
	while((UART2_FR_R &0x20) !=0);
	UART2_DR_R = x;
}
void Uart2_Init(void){
		int delay = 0;
		SYSCTL_RCGCUART_R |= 4; 													/* provide clock to UART2 */
		SYSCTL_RCGCGPIO_R |= 8; 													/* enable clock to PORTD */
		delay++;
		GPIO_PORTD_LOCK_R |= GPIO_LOCK_KEY;
		GPIO_PORTD_CR_R |= 0xC0;
		UART2_CTL_R = 0; 																/* disable UART0 */
		UART2_IBRD_R = 104;															 /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
		UART2_FBRD_R = 11; 															/* fraction part, see Example 4-4 */
		//UART0_CC_R = 0; 															/* use system clock */
		UART2_LCRH_R = 0X71;														/* 8-bit, no parity, 1-stop bit, no FIFO */
		//UART2_IM_R |= 0x0010; 													/* enable RX interrupt */
		UART2_CTL_R = 0x301; 														/* enable UART0, TXE, RXE */	
		GPIO_PORTD_DEN_R |= 0xC0; 											/* Make PD7 and PD6 as digital */
		GPIO_PORTD_DIR_R |= 0xC0;
		GPIO_PORTD_AMSEL_R &= ~0xC0;
		GPIO_PORTD_AFSEL_R |= 0xC0; 										/* Use PD7,PD6 alternate function */
		GPIO_PORTD_PCTL_R |= 0x11000000; 								/* configure PD6 and PD7 for UART 2*/
}

char getChar_u2_Wait(void)
{
	char c;
	while((UART2_FR_R & 0x10) != 0); // wait until the buffer is not empty 
	c = UART2_DR_R; 								 // read the received data 
	return c; // and return it 
}
char getChar_u2(void)
{
	char c;
	if((UART2_FR_R & 0x10) == 0) // wait until the buffer is not empty 
	{		c = UART2_DR_R; 								 // read the received data 
			return c; // and return it 
	}
	else 
		return 0;
}