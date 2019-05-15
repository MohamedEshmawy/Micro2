#include "ADC.h"
#include "ONEUART.h"
int delayy;

int ADC0_GetSample(void){
		
		int result = 0;
		ADC0_PSSI_R |= 0x8;			// Start conversion
		while((ADC0_RIS_R & 0x8) == 0);
		
		// Get value from associated FIFO
		result = ADC0_SSFIFO3_R;
		
		// Clear Sample done interrupt flag
		ADC0_ISC_R = 0x8;
		
		return result;
}

char send_temperature(){
			
			char x = 147 - (247 * ADC0_GetSample()) / 4096;
			return x;
			
}

