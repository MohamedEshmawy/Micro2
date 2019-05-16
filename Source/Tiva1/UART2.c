    
#include "UART2.h"
#include "POT_ADC.h"

void UART2_init(){
		SYSCTL_RCGCUART_R |= 4; /* provide clock to UART2 */
		SYSCTL_RCGCGPIO_R |= 8; /* enable clock to PORTC */
		UART2_CTL_R = 0; /* disable UART2 */
		UART2_IBRD_R = 104; /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
		UART2_FBRD_R = 11; /* fraction part, see Example 4-4 */
		UART2_CC_R = 0; /* use system clock */
		UART2_LCRH_R = 0x60; /* 8-bit, no parity, 1-stop bit, no FIFO */
		UART2_IM_R |= 0x0010; /* enable RX interrupt */
		UART2_CTL_R = 0x301; /* enable UART2, TXE, RXE */	
	  GPIO_PORTD_LOCK_R = 0x4C4F434B; /*unclock PORTD */
	  GPIO_PORTD_CR_R=0xC0;
		GPIO_PORTD_DEN_R = 0xC0; /* Make PD6 and PD7 as digital */
		GPIO_PORTD_AFSEL_R = 0xC0; /* Use PD6,PD7 alternate function */
		GPIO_PORTD_PCTL_R = 0x11000000; /* configure PD6 and PD7 for UART */
	
}

void UART2Tx(char c)
{
			while((UART2_FR_R & 0x20) != 0); /* wait until Tx buffer not full */
			UART2_DR_R = c; /* before giving it another byte */
}
