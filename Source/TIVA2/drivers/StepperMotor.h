
#include "../MCAL/MCAL.h"
#include "IC_L293D.h"

typedef struct
{
	IC_L293D ic_L293D;
	int gearToothNum;
} StepperMotor;

StepperMotor initMotor(IC_L293D ic_L293D ,int gearToothNum);
void rotateDegrees(StepperMotor m, int degrees, _Bool direction);
void Rotate(char x);
void init_stepper_motor(void );
