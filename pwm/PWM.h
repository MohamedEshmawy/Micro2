#include "stdint.h"
#include "tm4c123gh6pm.h"

void Uart0_Initt(void);
void d_c (int c);
unsigned char UART2Rx(void);
void uart2_init (void);
void pwm_init(void);
void UART0_printChar(char x);
char UART0_getChar(void);
char UART2_getChar(void);
void delayMs(int n);
void LED(void);
