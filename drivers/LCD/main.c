#include"lcd.h"
#include "tm4c123gh6pm.h"
void SystemInit(){
	Uart0_Initt();
	LCD_Init();
}
int main(){

display();


}