// File:  MCAL_DIO.h
// Author: MohamedEshmawy
// Date:  15/4/19
// Purpose: DIO utilities
// Hardware:  TM4C123 Tiva board

#ifndef DIO_MCAL_H
#define DIO_MCAL_H

#include <stdint.h>

//the diffrence between the base of each port and the preceding port ie.(portA is at 0x40004000 ,portB at 0x40005000)
#define offset 0x1000
//return the index of the port ie.(if port = 'c' return 3 ,port = 'A' return 0)
#define getPort(port) port<97?(port-65):(port-97)
//return the base address of a port

#define BasePort(port) port=='e'||port=='E'?0x40024000:port=='f'||port=='F'?0x40025000:0x40004000+((getPort(port))*offset)

#define GPIO_PORTX_DATA_R(port)		(*((volatile unsigned long *) ((BasePort(port)) +0x3FC)))	// Data Register
#define GPIO_PORTX_DIR_R(port)     	(*((volatile unsigned long *) ((BasePort(port)) +0x400)))	// Direction Register
#define GPIO_PORTX_AFSEL_R(port)   	(*((volatile unsigned long *) ((BasePort(port)) +0x420)))	// Alternate Function Select
#define GPIO_PORTX_PUR_R(port)     	(*((volatile unsigned long *) ((BasePort(port)) +0x510)))  // Pull-Up Select
#define GPIO_PORTX_DEN_R(port)     	(*((volatile unsigned long *) ((BasePort(port)) +0x51C)))	// Digital Enable
#define GPIO_PORTX_LOCK_R(port)		(*((volatile unsigned long *) ((BasePort(port)) +0x520)))	// Lock
#define GPIO_PORTX_CR_R(port)      	(*((volatile unsigned long *) ((BasePort(port)) +0x524)))	// Commit
#define GPIO_PORTX_AMSEL_R(port)   	(*((volatile unsigned long *) ((BasePort(port)) +0x528)))	// Analog Mode Select
#define GPIO_PORTX_PCTL_R(port)    	(*((volatile unsigned long *) ((BasePort(port)) +0x52C)))	// Port Control
	
#define GPIO_PX_M(x)	(1 << x)													//mask for pin x
#define GPIO_PCTL_PX_M(x) (15<<(4*x)) 									//mask for PCTL for pin x
#define SYSCTL_RCGCGPIO_RX(port) (1 << (getPort(port))) //mask for RCGCGPIO to enable clock for port X

#define INPUT 1
#define OUTPUT 0
#define HIGH 1
#define LOW 0

typedef struct {
	int pinNum;
	unsigned char portIndex;
	_Bool state;
} Pin;

Pin initPin(char portIndex, int pinNum ,_Bool ioState);
void setPin(Pin *pin, unsigned char out);
void setPins(Pin *pin, unsigned char out , int length);
unsigned char readPin(Pin *pin);

#endif
