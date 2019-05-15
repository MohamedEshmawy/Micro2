#include "StepperMotor.h"
StepperMotor motor;
void SysTick_Wait_ms(int n);
void init_stepper_motor(void);
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
void SysTick_Wait_ms(int n){
			int i, j;
			for(i = 0 ; i < n; i++){
					for(j = 0; j < 3180; j++){}		
}
}
void init_stepper_motor(void )
{
	Pin enable1,enable2,input1,input2,input3,input4;
	IC_L293D ic;
	
	//CHANGE THESE PINS
	enable1 = initPin('a', 7 ,OUTPUT);
	input1  = initPin('d', 3 ,OUTPUT);
	input2  = initPin('e', 1 ,OUTPUT);
	enable2 =	initPin('a', 6 ,OUTPUT);
	input3  = initPin('e', 2 ,OUTPUT);
	input4  = initPin('e', 3 ,OUTPUT);
	
	ic = initL293D(enable1,input1,input2,enable2,input3,input4);
	motor = initMotor(ic ,24);
}
void Rotate(char x){
		if(x == 'L')
			rotateDegrees(motor, 30, 1);
		else if(x == 'R')
			rotateDegrees(motor, 30, 0);
}
