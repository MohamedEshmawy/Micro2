
#ifndef _ONEUART_H_
#define _ONEUART_H_
#include "tm4c123gh6pm.h"

void Uart0_Init(void);
void SendChar(char x);
char GetChar(void);


#endif
