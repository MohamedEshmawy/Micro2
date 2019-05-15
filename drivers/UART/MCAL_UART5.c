// File:  MCAL_UART.c
// Author: JSpicer
// Date:  9/9/17
// Purpose: UART configuration and read/write utilities
// Hardware:  TM4C123 Tiva board

#include <stdint.h>
#include "tm4c123gh6pm.h"

void UART5_init (void){
	//U5RX is PE4 and U5TX is PE5
	//int delay = 0;
	SYSCTL_RCGCUART_R |= 0x20; //open clock for UART5
	SYSCTL_RCGCGPIO_R |= 0x10; //open clock for port E
	//delay--;
	//delay--;		
	UART5_CTL_R = 0; //disable UART5
	UART5_IBRD_R = 104; //set baudrate
	UART5_FBRD_R = 11; 
	//UART5_CC_R = 0; //????
	UART5_LCRH_R = 0x70; //set width of UART data to 8 bit
	UART5_CTL_R = 0x301; //enable UART5 and enable both receive and transmit
	GPIO_PORTE_DEN_R |= 0x30; //put PD4 and PD5 as digital i/o
	GPIO_PORTE_AFSEL_R  |= 0x30; //set alternate function PD4 and PD5
	GPIO_PORTE_PCTL_R |= 0x000110000; //set PD4 and PD5 alternate function as UART
}

void UART5_printChar(char x){
	while((UART5_FR_R &0x20) !=0);
	UART5_DR_R = x;
}

char UART5_getChar(_Bool waitUntilAvailable){
	char c;
	if(waitUntilAvailable)
	{
		while((UART5_FR_R & 0x10) != 0);  //wait until the buffer is not empty 
		c = UART5_DR_R; 								  //read the received data 

	}
	else if((UART5_FR_R & 0x10) != 0)
		c = UART5_DR_R;
	else
		c = '0'; //no data read
	
	return c;  //and return it 
}


void UART5_Iterrupt_Init(){
	//U5RX is PE4 and U5TX is PE5
	//int delay = 0;
	SYSCTL_RCGCUART_R |= 0x20; //open clock for UART5
	SYSCTL_RCGCGPIO_R |= 0x10; //open clock for port E
	//delay--;
	//delay--;		
	UART5_CTL_R = 0; //disable UART5
	UART5_IBRD_R = 104; //set baudrate
	UART5_FBRD_R = 11; 
	//UART5_CC_R = 0; //????
	UART5_LCRH_R = 0x60; //set width of UART data to 8 bit
	UART5_CTL_R = 0x301;
	
	GPIO_PORTE_DEN_R |= 0x30; //put PD4 and PD5 as digital i/o
	GPIO_PORTE_AFSEL_R  |= 0x30; //set alternate function PD4 and PD5
	GPIO_PORTE_PCTL_R |= 0x000110000; //set PD4 and PD5 alternate function as UART
	 					/* enable UART5, TXE, RXE */
	UART5_IM_R |= 0x0010; 				/* enable RX interrupt */
	NVIC_PRI15_R = 3 << (5+8); 						/* set interrupt priority to 3 */
	NVIC_EN1_R |= 0x20000000;			//enable interrupt request number 77th in Enable register
}
