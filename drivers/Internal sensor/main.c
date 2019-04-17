#include "ADC.h"

void SystemInit(){}
int __main(){
	double temp;char x;
	UART_Init();
	ADC_Init();
	
	while(1){
		temp = 147 - (247 * ADC0_InSeq3()) / 4096;
		x = temp;
		printChar(x);
	}
}





