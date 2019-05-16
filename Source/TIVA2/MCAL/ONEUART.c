#include "ONEUART.h"

int delayyy;
void Uart0_Init(void){
		SYSCTL_RCGCUART_R |= 1;            	/* provide clock to UART0 */
		SYSCTL_RCGCGPIO_R |= 1;            	/* enable clock to PORTA */
		UART0_CTL_R = 0; 										/* disable UART0 */
		UART0_IBRD_R = 104; 								/* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
		UART0_FBRD_R = 11; 									/* fraction part, see Example 4-4 */
		UART0_CC_R = 0; 									/* use system clock */
		UART0_LCRH_R = 0x70; 								/* 8-bit, no parity, 1-stop bit, no FIFO */
		//UART0_IM_R |= 0x0010; 							/* enable RX interrupt */
		UART0_CTL_R = 0x301; 								/* enable UART0, TXE, RXE */	
		GPIO_PORTA_DEN_R = 0x03; 						/* Make PA0 and PA1 as digital */
		GPIO_PORTA_AFSEL_R = 0x03; 					/* Use PA0,PA1 alternate function */
		GPIO_PORTA_PCTL_R = 0x11; 					/* configure PA0 and PA1 for UART */
		
	
}
void SendChar(char x){
	while((UART0_FR_R &0x20) !=0);
	UART0_DR_R = x;
}
char GetChar(void)
{
	char c;
	if((UART0_FR_R & 0x10) == 0) // wait until the buffer is not empty 
	{		c = UART0_DR_R; 								 // read the received data 
			return c; // and return it 
	}
	else 
		return '0';
}
