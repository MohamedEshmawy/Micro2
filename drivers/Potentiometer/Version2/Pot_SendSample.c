#include "POT_ADC.h"
char SendSample() {
	volatile int result;
	char c;
	ADC0_PSSI_R |= 8; /* start a conversion sequence 3 */
	while ((ADC0_RIS_R & 8) == 0); /* wait for conversion complete */
	result = ADC0_SSFIFO3_R; /* read conversion result */
	ADC0_ISC_R = 8; /* clear completion flag */
	result = result * 9 / 4095;
	//if (result == lastResult) return;
	//lastResult = result;
	c = '0' + result;
	return c;
	//UART5_printChar(c);

}
