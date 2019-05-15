#include "IC_L293D.h"
 

IC_L293D initL293D(Pin enable1,Pin input1,Pin input2,Pin enable2,Pin input3,Pin input4)
{
	IC_L293D ic;
	ic.enable1 = enable1;
	ic.input1 = input1;
	ic.input2 = input2;
	ic.enable2 = enable2;
	ic.input3 = input3;
	ic.input4 = input4;
	return ic;
}

void enableSide1(IC_L293D* ic, _Bool value)
{
	setPin(&ic->enable1 , value);
	if (!value)
	{
		setPin(&ic->input1 , 0);
		setPin(&ic->input2 , 0);
	}
}

void enableSide2(IC_L293D* ic, _Bool value)
{
	setPin(&ic->enable2 , value);
	setPin(&ic->input3 , 0);
	setPin(&ic->input4 , 0);
}

void driveSide1(IC_L293D* ic, _Bool direction)
{
	setPin(&ic->input1 , direction);
	setPin(&ic->input2 , !direction);
}

void driveSide2(IC_L293D* ic, _Bool direction)
{
	setPin(&ic->input3 , direction);
	setPin(&ic->input4 , !direction);
}
