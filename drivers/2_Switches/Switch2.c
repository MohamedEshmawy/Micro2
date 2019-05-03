#include "Switch.h"
#include "UartInit.h"
#include "tm4c123gh6pm.h"
void SW1_Init(void){
volatile unsigned long delay;
  SYSCTL_RCGCGPIO_R |= 0x20;  
  delay = 2;        				
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   			  
  GPIO_PORTF_CR_R |= 0x10;          	 
  GPIO_PORTF_AMSEL_R &= ~0x10;      
  GPIO_PORTF_PCTL_R &= ~GPIO_PCTL_PF4_M;  
  GPIO_PORTF_AFSEL_R &= ~0x10;      
	GPIO_PORTF_DIR_R &= ~0x10;
	GPIO_PORTF_PUR_R |= 0x10;
  GPIO_PORTF_DEN_R |= 0x10;			
}
void SW2_Init(void){
volatile unsigned long delay;
  SYSCTL_RCGCGPIO_R |= 0x20;  
  delay = SYSCTL_RCGCGPIO_R;        				
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   			  
  GPIO_PORTF_CR_R |= 1;          	 
  GPIO_PORTF_AMSEL_R &= ~1;      
  GPIO_PORTF_PCTL_R &= ~GPIO_PCTL_PF0_M;  
  GPIO_PORTF_AFSEL_R &= ~1;      
	GPIO_PORTF_DIR_R &= ~1;
	GPIO_PORTF_PUR_R |= 1;
  GPIO_PORTF_DEN_R |= 1;		
}
unsigned char SW1_Input(void){
return GPIO_PORTF_DATA_R&16;
}
unsigned char SW2_Input(void){
return GPIO_PORTF_DATA_R&1;
}
void read_send0(void){
	if(SW1_Input() == 0 && SW2_Input() == 1)
			{UART0_printChar('R'); while(SW1_Input() == 0 && SW2_Input() == 1);}
		
			else if(SW2_Input() == 0)
			{UART0_printChar('L');while(SW2_Input() == 0);}
			else if(SW1_Input() == 0 && SW2_Input() == 0)
			{}
}
void read_send2(void){
	if(SW1_Input() == 0 && SW2_Input() == 1)
			{UART2_printChar('R'); while(SW1_Input() == 0 && SW2_Input() == 1);}
		
			else if(SW2_Input() == 0)
			{UART2_printChar('L');while(SW2_Input() == 0);}
			else if(SW1_Input() == 0 && SW2_Input() == 0)
			{}
}

