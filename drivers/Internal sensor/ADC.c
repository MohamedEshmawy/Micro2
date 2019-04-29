#include "ADC.h"

int delay;
void ADC_Init(void){																								//Latest

	//temperature sensor
	/* enable clocks */
    SYSCTL_RCGCADC_R |= 1;       /* enable clock to ADC0 */
    SYSCTL_RCGCWTIMER_R |= 1;    /* enable clock to WTimer Block 0 */

    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;          /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;
    ADC0_EMUX_R |= 0x5000;       /* timer trigger conversion seq 0 */
    ADC0_SSMUX3_R = 0;           /* get input from channel 0 */
    ADC0_SSCTL3_R |= 0x0E;       /* take chip temperature, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;           /* enable ADC0 sequencer 3 */

    /* initialize wtimer 0 to trigger ADC at 1 sample/sec */
    WTIMER0_CTL_R = 0;           /* disable WTimer before initialization */
    WTIMER0_CFG_R = 0x04;        /* 32-bit option */
    WTIMER0_TAMR_R = 0x02;       /* periodic mode and down-counter */
    WTIMER0_TAILR_R = 16000000;  /* WTimer A interval load value reg (1 s) */
    WTIMER0_CTL_R |= 0x20;       /* timer triggers ADC */
    WTIMER0_CTL_R |= 0x01;       /* enable WTimer A after initialization */

}
char* number(int x){
	char* u;
	u[0] = x/10;
	u[1] = x%10;
	return u;
	
}
int ADC0_GetSample(void){
		
		int result = 0;
		//ADC0_PSSI_R |= 0x8;			// Start conversion
	
		while((ADC0_RIS_R & 0x8) == 0);
		
		// Get value from associated FIFO
		result = ADC0_SSFIFO3_R;
		
		// Clear Sample done interrupt flag
		ADC0_ISC_R = 0x8;
		
		return result;
}


void printChar(char x){
	while((UART0_FR_R &0x20) !=0);
	UART0_DR_R = x;
}
void Uart0_Initt(void){
		SYSCTL_RCGCUART_R |= 1; 
		SYSCTL_RCGCGPIO_R |= 1; 
		
	//SYSCTL_RCGCGPIO_R |= 0x20; 
		delay --;
		delay--;	
		UART0_CTL_R = 0; 
		UART0_IBRD_R = 104; 
		UART0_FBRD_R = 11; 
		UART0_CC_R = 0;            
		UART0_LCRH_R = 0x60; 
		UART0_CTL_R = 0x301; 
		GPIO_PORTA_DEN_R = 0x03; 
		GPIO_PORTA_AFSEL_R = 0x03; 
		GPIO_PORTA_PCTL_R = 0x11; 
}
void send_temperature(){
			int x = 147 - (247 * ADC0_GetSample()) / 4096;
			//int u = x/10;
			//printChar(u+48);
			//u = x%10;
			//printChar(u+48);
			printChar(x);
}
