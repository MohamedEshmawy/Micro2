#ifndef _UARTINIT_H_
#define _UARTINIT_H_
#include "tm4c123gh6pm.h"
void Uart0_Initt(void);
void UART0_printChar(char x);
char UART0_getChar(void);
void Uart1_Initt(void);
void UART1_printChar(char x);
char UART1_getChar(void);
void delayMs(int n);
	

#endif

