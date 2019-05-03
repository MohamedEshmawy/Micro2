#include "PWM.h"
void SystemInit(){
	Uart0_Initt();
	pwm_init();
}
int main(void)
{		 
	  

		while(1)
		{
			LED();        //to switch the led with signal of Pot of other Tiva 
			//PWM1_3_CMPA_R = (15999-((UART0_getChar()-48)/9.0)*15999); this is to be on UART0 for testing 
		}
} 

