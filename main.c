#include "Switch.h"
#include "UartInit.h"
#define GPIO_PCTL_PF321_M		(GPIO_PCTL_PF3_M | GPIO_PCTL_PF2_M | GPIO_PCTL_PF1_M)


void SystemInit(){
	//Uart0_Initt();       //this was for testing
	Uart1_Initt();
	SW2_Init();
	SW1_Init();

}
int main(void)
{		 
		while(1)
		{
			read_send1();      //this function sends and receives on UART1
			//read_send0();      //this function sends and receives on UART0
		}
} 	
