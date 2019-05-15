

#ifndef UART_MCAL_H
#define UART_MCAL_H

#include <stdint.h>

void UART5_init (void);
void UART5_printChar(char x);
char UART5_getChar(_Bool waitUntilAvailable);
void UART5_Iterrupt_Init(void);
#endif
