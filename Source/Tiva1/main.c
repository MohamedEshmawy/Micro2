#include "Switch.h"
#include "POT_ADC.h"
#include "LCD.h"
#include "UART0.h"
#include "MCAL/MCAL.h"
#include "extra/qeue.h"

Qeue q;
Pin blue, red;

void SystemInit(){
	blue = initPin('f', 2 , OUTPUT);
	red = initPin('f', 1 , OUTPUT);
	SW2_Init();
	SW1_Init();
	Init_ADC();
	LCD_init_V2();
	//UART5_init();
	UART5_Iterrupt_Init();
	//Uart0_Init();
	
	q = initQeue();
}
int __main()
{		
	char x;
	char Pot_sample = SendSample();
	char Last_pot_sample;
	UART5_printChar(Pot_sample);
	
	__enable_irq();	

	ptintStringg("TEMPERATURE =",0,0); //third there means to be in the first line,1 measns to be in the second line
	ptintStringg("HAVE A NICE DAY ",0,1); 
		while(1)
		{
			
		if (!isEmpty(&q))
		{
			x = removeData(&q);
			display_num(x);
			setPin(&red , 1);
			delay_milli(100);
			setPin(&red , 0);
			delay_milli(100);
		}
			
			//UART5_printChar(210);
			Pot_sample = SendSample();
			if(Pot_sample != Last_pot_sample)
			{
				UART5_printChar(Pot_sample);		//this send the state of Switches
				Last_pot_sample = Pot_sample;
			}
			
			read_send2();
			//SendSample();   //this sends the value of the Potentiometer 
			//x = getChar_wait();
			//SendChar('x');
			//display_num(x);
			//setPin(&blue , 1);
			//delay_milli(200);
			//setPin(&blue , 0);
			delay_milli(50);
			//pot_sample = SendSample();
	}
}


void UART5_Handler(void)
{
	volatile int readback;
	char x;
	if (UART5_MIS_R & 0x0010) 	 
					insert(&q, UART5_getChar(1));							/* insert the received data into a qeue*/

	UART5_ICR_R |= 0x0010;
	readback = UART5_ICR_R;
			return ;
}
