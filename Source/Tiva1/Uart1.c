#include "Uart1.h"

void Uart0_Initt(void){
		SYSCTL_RCGCUART_R |= 1; 
		SYSCTL_RCGCGPIO_R |= 1; 
		
	//SYSCTL_RCGCGPIO_R |= 0x20; 

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
void Uart1_Initt(void){
		SYSCTL_RCGCUART_R |= 3; 
		SYSCTL_RCGCGPIO_R |= 3; 
		
	//SYSCTL_RCGCGPIO_R |= 0x20; 

		UART1_CTL_R = 0; 
		UART1_IBRD_R = 104; 
		UART1_FBRD_R = 11; 
		UART1_CC_R = 0;            
		UART1_LCRH_R = 0x60; 
		UART1_CTL_R = 0x301; 
		GPIO_PORTB_DEN_R = 0x03; 													//UART2 is at PD6 and PD7
		GPIO_PORTB_AFSEL_R = 0x03; 
		GPIO_PORTB_PCTL_R = 0x11; 								//use the alternative function of the 8th and 7th pins 
}

void UART1_printChar(char x){
	while((UART1_FR_R &0x20) !=0);
	UART1_DR_R = x;
}
char UART1_getChar(void){
	char c;
	while((UART1_FR_R & 0x10) != 0); /* wait until the buffer is not empty */
	c = UART1_DR_R; 								 /* read the received data */
	return c; /* and return it */
}

void delayMs(int n){
			int i, j;
			for(i = 0 ; i < n; i++){
					for(j = 0; j < 3180; j++){}		
}
}
