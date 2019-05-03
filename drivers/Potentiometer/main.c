#include "UART2.h"
#include "POT_ADC.h"

void SystemInit(void){
 UART2_init();
 Init_ADC();
}

int __main(void)
{
while(1)
 {
	SendSample();
 }
}