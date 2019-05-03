#include "PWM.h"
int delay;
void pwm_init(){
SYSCTL_RCGCPWM_R |= 2; 
SYSCTL_RCGCGPIO_R |= 0x20; 
SYSCTL_RCC_R &= ~0x00100000; 
GPIO_PORTF_AFSEL_R |= 8;
GPIO_PORTF_PCTL_R &= ~0x0000F000;
GPIO_PORTF_PCTL_R |= 0x00005000;
//GPIO_PORTF_DIR_R  |= 0x00001000;	
GPIO_PORTF_DEN_R |= 8; 
PWM1_3_CTL_R  = 0; 
PWM1_3_GENB_R |= 0x0000008C; 
PWM1_3_LOAD_R |= 16000; 
PWM1_3_CMPA_R |= 15999;   //almost led is off
PWM1_3_CTL_R |= 1; 
PWM1_ENABLE_R = 0x80;
}
void uart2_init (){
SYSCTL_RCGCUART_R |= 0x04; 
SYSCTL_RCGCGPIO_R |= 0x04;
delay --;
delay--;		
UART2_CTL_R = 0; 
UART2_IBRD_R = 104;
UART2_FBRD_R = 11; 
UART2_CC_R = 0; 
UART2_LCRH_R = 0x60; 
UART2_CTL_R = 0x301; 
GPIO_PORTD_DEN_R = 0xC0; 
GPIO_PORTD_AFSEL_R  = 0xC0; 
GPIO_PORTD_PCTL_R = 0x11000000; 
}




char UART2_getChar(void){
	char c;
	while((UART2_FR_R & 0x10) != 0); /* wait until the buffer is not empty */
	c = UART2_DR_R; 								 /* read the received data */
	return c; 
}
void delayMs(int n){
			int i, j;
			for(i = 0 ; i < n; i++){
					for(j = 0; j < 3180; j++){}		
}
}
void LED(){ 
			PWM1_3_CMPA_R = (15999-((UART2_getChar()-48)/9.0)*15999);
}
