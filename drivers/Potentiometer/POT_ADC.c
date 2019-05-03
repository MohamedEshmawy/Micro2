#include "UART2.h"
#include "POT_ADC.h"

void Init_ADC(){
		SYSCTL_RCGCGPIO_R |= 0x10; /* enable clock to GPIO_PORTE (AIN0 is on PE3) */
		SYSCTL_RCGCADC_R |= 1; /* enable clock to ADC0 */
		GPIO_PORTE_AFSEL_R |= 8; /* enable alternate function */
		GPIO_PORTE_DEN_R &= ~8; /* disable digital function */
		GPIO_PORTE_AMSEL_R |= 8; /* enable analog function */
		ADC0_ACTSS_R &= ~8; /* disable SS3 during configuration */
		ADC0_EMUX_R &= ~0xF000; /* software trigger conversion */
		ADC0_SSMUX3_R = 0; /* get input from channel 0 */
		ADC0_SSCTL3_R |= 6; /* take one sample at a time, set flag at 1st sample */
		ADC0_ACTSS_R |= 8; /* enable ADC0 sequencer 3 */
}

void SendSample(){
		volatile int result;
		char c;
		ADC0_PSSI_R |= 8; /* start a conversion sequence 3 */
		while((ADC0_RIS_R & 8) == 0) ; /* wait for conversion complete */
		result = ADC0_SSFIFO3_R; /* read conversion result */
		ADC0_ISC_R = 8; /* clear completion flag */
		result=result*9/4095;	
		c='0'+result;
		UART2Tx(c);
}