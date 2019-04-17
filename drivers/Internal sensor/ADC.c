
#include "ADC.h"
int delay;
unsigned long ADC0_InSeq3(void){  
	unsigned long result;
  ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
  return result;
}

void Uart_Initt(){
		SYSCTL_RCGCUART_R |= 1; 
		SYSCTL_RCGCGPIO_R |= 1; 
		SYSCTL_RCGCGPIO_R |= 0x20; 
		UART0_CTL_R = 0; 
		UART0_IBRD_R = 104; 
		UART0_FBRD_R = 11; 
		UART0_CC_R = 0;            
		UART0_LCRH_R = 0x60; 
		UART0_CTL_R = 0x301; 
		
}
void ADC_Init(){
	SYSCTL_RCGC0_R |= 0x00010000;         //enable clock for the ADC
	delay = SYSCTL_RCGC2_R; 
	SYSCTL_RCGCWTIMER_R |= 1;							// enabling timer0 clock
	ADC0_ACTSS_R     		&= ~0x08;					// disable first ADC while configuarion ,sequencer 3
	ADC0_EMUX_R 				&= ~0xF000;				// typcally unknown
	//ADC0_EMUX_R      		|=  0x5000;				// enable triggering by Timer
	ADC0_SSCTL3_R     	|= 0xA;						// let the fourth sequencer read from temp sensor and enableing only reading from it
	ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
	//WTIMER0_CTL_R        = 0; 						/* disable WTimer before initialization */
	//WTIMER0_CFG_R        = 0x04; 					/* 32-bit option */
	//WTIMER0_TAMR_R       = 0x02; 					/* periodic mode and down-counter */
	//WTIMER0_TAILR_R      = 16000000; 			/* WTimer A interval load value reg (1 s) */
	//WTIMER0_CTL_R        |= 0x20; 				/* timer triggers ADC */
	//WTIMER0_CTL_R        |= 0x01; 				/* enable WTimer A after initialization */
	//*/
	ADC0_ACTSS_R		     |= 0x08;					//enable sample sequencer after configuration
	
	//ADC0_RIS_R =   0;  //to check end of conversion finished or not ,,fourth bit must be cleared after reading
	//	ADC0_SSFIFO3_R   to take result from here
	
}
void printChar(char x){
	while((UART0_FR_R &0x20) !=0);
	UART0_DR_R = x;
}
char getChar(void)
{
	char c;
	while((UART0_FR_R & 0x10) != 0); /* wait until the buffer is not empty */
	c = UART0_DR_R; 								 /* read the received data */
	return c; /* and return it */
}

char* getString(){
	char *str;int i;
	for(i=0;i<10;i++)
		{str[i] = getChar();
		printChar(str[i]); 
		if(str[i] == 13)break;
		}
	printChar(10);
	return str;
}


void UART_Init(void){
  SYSCTL_RCGC1_R |= 0x01; // activate UART0
  
  UART0_CTL_R  = 0;      // disable UART
  UART0_IBRD_R = 27;                    // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
  UART0_FBRD_R = 8;                     // FBRD = int(0.1267 * 64 + 0.5) = 8
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = 0x60;
  UART0_CTL_R |= 0x301;       // enable UART

}







