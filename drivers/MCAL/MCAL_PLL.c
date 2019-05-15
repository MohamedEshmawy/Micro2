// File:  HAL_PLL.c
// Author: JSpicer
// Date:  9/9/17
// Purpose: PLL and bus clock utilities
// Hardware:  TM4C123 Tiva board

#include <stdint.h>
#include "tm4c123gh6pm.h"

// Holds the currently configured bus clock frequency.
static uint32_t busClockFreq_;

//------------------------- PLL_Init80MHz ----------------------------
// Initializes the PLL to a bus clock frequency of 80MHz.
// Inputs:  none.
// Outputs:  none.
void PLL_Init80MHz(void)
{
	
	// 0) Set USERCC2 bit in order to use RCC2
	SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
	
	// 1) Set the BYPASS bit to bypass PLL while initializing.
	SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

	// 2) Clear and set the XTAL bits to 16MHz
	SYSCTL_RCC_R = ((SYSCTL_RCC_R & ~SYSCTL_RCC_XTAL_M) | SYSCTL_RCC_XTAL_16MHZ);
	
	// 3)	Clear the OSCSRC2 bits to configure for Main OSC
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
	
	// 4) Activate PLL by clearing PWRDN.
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
	
	// 5) Use 400 MHz PLL
	SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400 ;
	
	// 6) Clear the SYSDIV2 bits and set to 0x4 = 80MHz
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~(SYSCTL_RCC2_SYSDIV2_M | SYSCTL_RCC2_SYSDIV2LSB)) | (0x4 << 22);  
	
	// 7) Wait for the PLL to lock
	while ((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0)
	{
	}
	
	// 8) Clear BYPASS to enable PLL.
	SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
	
	busClockFreq_ = 80000000;
	
}

//----------------------- PLL_GetBusClockFreq ------------------------
// Gets the PLL bus clock frequency.
// Inputs:  none.
// Outputs:  the configured bus clock frequency or zero if uninitialized.
uint32_t PLL_GetBusClockFreq(void)
{
	return busClockFreq_;
}

