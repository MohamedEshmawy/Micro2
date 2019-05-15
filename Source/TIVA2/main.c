
#include "drivers/StepperMotor.h"
#include "drivers/IC_L293D.h"
#include "MCAL/MCAL.h"
#include "MCAL/ADC.h"
#include "MCAL/ONEUART.h"
#include "MCAL/UART22.h"
#include "MCAL/PWM.h"
#include "extra/qeue.h"


Qeue q;
Pin red, green;
void SystemInit(){
	red = initPin('f', 1 ,OUTPUT);
	//green = initPin('f', 3 ,OUTPUT);
	
	init_stepper_motor(); //change contents of this function to suit your pin configuration
	//Uart2_Init();
  pwm_initt();
	ADC_Init();
	UART5_Iterrupt_Init();
	//UART5_init();
	Uart0_Init();
	q = initQeue();
}
int __main(){
		char x;
		__enable_irq();
		while(1){

		if (!isEmpty(&q))
		{
			x = removeData(&q);
			if(x== 'R' || x == 'L')
					{Rotate(x);}
			else if(x >= '0' && x <= '9')
					LED(x);
			setPin(&red , 1);
			delayMs(100);
			setPin(&red , 0);
			delayMs(100);
		}

			UART5_printChar(send_temperature());
			//SendChar('E');
			//UART5_printChar('A');
			//UART5_printChar('B');
			//UART5_printChar('C');
			//delayMs(100);
			//SendChar(UART5_getChar(1));
			//SendChar(UART5_getChar(1));
			//SendChar(UART5_getChar(1));
			//SendChar(10);
			//setPin(&green , 1);
			//delayMs(200);
			//setPin(&green , 0);
			delayMs(200);
		}
}

void UART5_Handler(void)
{
	volatile int readback;
	char x;
	if (UART5_MIS_R & 0x0010) 	 
	{
		while((UART5_FR_R & 0x10) == 0)
			insert(&q, UART5_getChar(1));		
		//insert(&q, UART5_getChar(1));		
	}
		
		//insert(&q, UART5_DR_R &0xff);
		/* insert the received data into a qeue*/

	UART5_ICR_R |= 0x0010;
	readback = UART5_ICR_R;
			return ;
}

