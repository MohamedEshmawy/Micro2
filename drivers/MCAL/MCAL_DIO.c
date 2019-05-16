// File:  MCAL_DIO.c
// Author: MohamedEshmawy
// Date:  15/4/19
// Purpose: DIO utilities
// Hardware:  TM4C123 Tiva board

#include <stdint.h>
#include "MCAL.h"
#include "tm4c123gh6pm.h"

Pin initPin(char portIndex, int pinNum ,_Bool ioState) // PORt A ro B //Number of pin//INPUt or Output
{
		
	volatile unsigned long delay; 
	unsigned long pinMask = GPIO_PX_M(pinNum);
	unsigned long pctlPinMask = GPIO_PCTL_PX_M(pinNum);
	
	Pin pin;
	pin.pinNum = pinNum;
	pin.portIndex = portIndex;
	pin.state = ioState;

	  			         				
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_RX(portIndex);	// Port clock enable
	delay = SYSCTL_RCGCGPIO_R; // Delay
	delay = SYSCTL_RCGCGPIO_R; // Delay
	GPIO_PORTX_LOCK_R(portIndex) = GPIO_LOCK_KEY; //unlock the port

	 
	if (pin.state == INPUT)
	{		  
		GPIO_PORTX_CR_R(portIndex) |= pinMask;          	 
		GPIO_PORTX_AMSEL_R(portIndex) &= ~pinMask;      
		GPIO_PORTX_PCTL_R(portIndex) &= ~pctlPinMask;  
		GPIO_PORTX_AFSEL_R(portIndex) &= ~pinMask;      
		GPIO_PORTX_DIR_R(portIndex) &= ~pinMask;
		GPIO_PORTX_PUR_R(portIndex) |= pinMask;
		GPIO_PORTX_DEN_R(portIndex) |= pinMask;	
	}
	else if (pin.state == OUTPUT)
	{
		GPIO_PORTX_CR_R(portIndex) |= pinMask;          // Allow changes to Pin     
		GPIO_PORTX_AMSEL_R(portIndex) &= ~pinMask;      // Disable analog function
		GPIO_PORTX_PCTL_R(portIndex) &= ~pctlPinMask;  // GPIO clear bit PCTL  
		GPIO_PORTX_AFSEL_R(portIndex) &= ~pinMask;      // No alternate function
		GPIO_PORTX_DIR_R(portIndex) |= pinMask;         // Pin state is output
		GPIO_PORTX_DEN_R(portIndex) |= pinMask;         // Enable digital pins PF4-PF0
		GPIO_PORTX_DATA_R(portIndex) &= ~pinMask;			// Initalize Pin to be off
	}
	
	
	return pin;
}




void setPin(Pin *pin , unsigned char out)		//given address of pin name and HIGH Or LOW
{
	if (pin->state == INPUT) return;
	if (out == 1)
		GPIO_PORTX_DATA_R(pin->portIndex) |= GPIO_PX_M(pin->pinNum);
	else if (out == 0)
		GPIO_PORTX_DATA_R(pin->portIndex) &= ~(GPIO_PX_M(pin->pinNum));
		//GPIO_PORTX_DATA_R(pin->portIndex) &= !GPIO_PX_M(pin->pinNum);
}

void setPins(Pin *pin, unsigned char out , int length)	//given array of pins and length of them
	
{
	_Bool maskedOut;
	char i;
	for (i = 0; i<length; i++)
	{
		maskedOut = (1<<i) & out;
		setPin(&(pin[i]) , maskedOut);
	}
}

unsigned char readPin(Pin *pin)
{
	return ((GPIO_PORTX_DATA_R(pin->portIndex) & GPIO_PX_M(pin->pinNum))!=GPIO_PX_M(pin->pinNum));
}
