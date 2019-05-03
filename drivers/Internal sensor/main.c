#include "ADC.h"

void SystemInit(){
	Uart0_Initt();
	ADC_Init();
}

int __main(){
	
	while(1){
		send_temperature();
	}
}


