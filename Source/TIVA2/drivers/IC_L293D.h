
#include "../MCAL/MCAL.h"

#ifndef DIO_IC_L293D_H
#define DIO_IC_L293D_H

typedef struct
{
	Pin enable1, enable2,input1,input2,input3,input4;
} IC_L293D;

IC_L293D initL293D(Pin enable1,Pin input1,Pin input2,
					Pin enable2,Pin input3,Pin input4);
void enableSide1(IC_L293D* ic, _Bool value);
void enableSide2(IC_L293D* ic, _Bool value);
void driveSide1(IC_L293D* ic, _Bool direction);
void driveSide2(IC_L293D* ic, _Bool direction);

#endif
