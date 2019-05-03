#include "StepperMotor.h"

StepperMotor initMotor(IC_L293D ic_L293D ,int gearToothNum)
{
	StepperMotor m;
	m.ic_L293D = ic_L293D;
	m.gearToothNum = gearToothNum; //24 for our project
	
	enableSide1(&m.ic_L293D , 1);
	enableSide2(&m.ic_L293D , 1);
	
	return m;
}

void rotateDegrees(StepperMotor m, int degrees, _Bool direction)
{
	int i;
	int degreesPerStep = 360 / m.gearToothNum;
	int numOfSteps = (degrees/degreesPerStep)+1; //+1 for error
	_Bool toggle = 0;
	
	enableSide1(&m.ic_L293D, 1);
	enableSide2(&m.ic_L293D, 1);
	
	for (i = 0; i < numOfSteps; i++)
	{
		if(direction)
			driveSide1(&m.ic_L293D, toggle);
		else if (!direction)
			driveSide2(&m.ic_L293D, toggle);
		toggle = !toggle;
		SysTick_Wait_ms(100);
	}
	enableSide1(&m.ic_L293D, 0);
	enableSide2(&m.ic_L293D, 0);
}
