#include "PWM.h"
void Uart0_Initt(void){
		SYSCTL_RCGCUART_R |= 1; 
		SYSCTL_RCGCGPIO_R |= 1; 
		
	//SYSCTL_RCGCGPIO_R |= 0x20; 
		delay --;
		delay--;	
		UART0_CTL_R = 0; 
		UART0_IBRD_R = 104; 
		UART0_FBRD_R = 11; 
		UART0_CC_R = 0;            
		UART0_LCRH_R = 0x60; 
		UART0_CTL_R = 0x301; 
		GPIO_PORTA_DEN_R = 0x03; 
		GPIO_PORTA_AFSEL_R = 0x03; 
		GPIO_PORTA_PCTL_R = 0x11; 
}
void UART0_printChar(char x){
	while((UART0_FR_R &0x20) !=0);
	UART0_DR_R = x;
}
char UART0_getChar(void){
	char c;
	while((UART0_FR_R & 0x10) != 0); /* wait until the buffer is not empty */
	c = UART0_DR_R; 								 /* read the received data */
	return c; /* and return it */
}
