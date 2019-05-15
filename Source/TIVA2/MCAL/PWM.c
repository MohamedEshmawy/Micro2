#include "PWM.h"
#include "ONEUART.h"
int delay;
void pwm_init(){
SYSCTL_RCGCPWM_R |= 2; 
SYSCTL_RCGCGPIO_R |= 0x20; 
GPIO_PORTF_LOCK_R |= GPIO_LOCK_KEY;
GPIO_PORTF_CR_R   |= 0x1f;
delay ++;
delay++ ; 
SYSCTL_RCC_R &= ~0x00100000; 
GPIO_PORTF_AFSEL_R |= 8;
GPIO_PORTF_PCTL_R &= ~0x0000F000;
GPIO_PORTF_PCTL_R |= 0x00005000;
GPIO_PORTF_DIR_R  |= 0x00001000;	
GPIO_PORTF_DEN_R |= 8; 
PWM1_3_CTL_R  = 0; 
PWM1_3_GENB_R |= 0x0000008C; 
PWM1_3_LOAD_R |= 16000; 
PWM1_3_CMPA_R |= 15999;   //almost led is off
PWM1_3_CTL_R |= 1; 
PWM1_ENABLE_R = 0x80;
}
void pwm_initt(){
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
void delayMs(int n){
			int i, j;
			for(i = 0 ; i < n; i++){
					for(j = 0; j < 3180; j++){}		
}
}
void LED(int x){
       	int y =  (x-'0'+1)*1599;
			PWM1_3_CMPA_R = y;
} 
