/*******************************************************************************************
* ! Title          : WDT_program
* ! File Name      : WDT_program.c
* ! Layer          : MCAL
* ! Compiler       : GNU winAVR Cross Compiler
* ! Target         : Atmega32 Microcontroller
********************************************************************************************/
/*******************************************************************************************
* LOG :
* VERSION    AUTHOR                                   DESCRIPTION
* v1.0       Abdullah Mustafa  			              - Initial creation
********************************************************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_config.h"

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR, WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	/*Set WDTOE and WDE in the same operation*/
	WDTCR = (1 << WDTCR_WDTOE) | (1 << WDTCR_WDE);	
	/*Within The Next Four Clock Cycles, Write Logic 0 to WDE*/
	WDTCR = 0;
}


void WDT_voidSleep(u8 Copy_u8SleepTimeOut)
{
	if(Copy_u8SleepTimeOut < MAX_NUMBER_FOR_PRESCALER)
	{
		WDTCR &= PRESCALER_RESET_MASK;
		WDTCR |= Copy_u8SleepTimeOut;
	}
	else
	{
		/* An Error To Be Displayed */
	}
}






