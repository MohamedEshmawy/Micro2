
#include "Switch.h"

unsigned char SW1_Input(void){
return GPIO_PORTF_DATA_R&0x10;
}
unsigned char SW2_Input(void){
return GPIO_PORTF_DATA_R&1;
}
void read_send2(void){
	if(!SW1_Input() && SW2_Input())
			{UART5_printChar('R');
				delay_milli(500);
			while(!SW1_Input() && SW2_Input());}
		
	if(SW1_Input() &&  !SW2_Input())
			{UART5_printChar('L');
			delay_milli(500);
			while(SW1_Input()&& !SW2_Input());}
	{}
}