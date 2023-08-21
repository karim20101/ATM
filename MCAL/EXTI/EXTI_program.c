/*
 * EXTI_Program.c
 *
 *  Created on: Dec 17, 2022
 *      Author: abdelrahmanhossam
 */



#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Cfg.h"

#define NULL (void*)0

void (*EXTI0_callBack) (void) = NULL;
void (*EXTI1_callBack) (void) = NULL;
void (*EXTI2_callBack) (void) = NULL;

void MEXTI_voidSetCfg (const u8 A_u8EXTI, const u8 A_u8SenseControl)
{
	if ((A_u8EXTI <= EXTI2) && (A_u8SenseControl<= RISING_EDGE))
	{
		switch (A_u8EXTI)
		{
		case EXTI0:	MCUCR &= ~(SENSE_MODE_MASK<<EXTI0_SENSE_BIT_0); // clear 2 bits
					MCUCR |= (A_u8SenseControl<<EXTI0_SENSE_BIT_0); // set sense control
					break;

		case EXTI1: MCUCR &= ~(SENSE_MODE_MASK<<EXTI1_SENSE_BIT_0);
				    MCUCR |= (A_u8SenseControl<<EXTI1_SENSE_BIT_0);
				    break;

		case EXTI2: switch (A_u8SenseControl)
					{
					case FALLING_EDGE: CLR_BIT(MCUCSR,EXTI2_SENSE_BIT_0); break;
					case RISING_EDGE : SET_BIT(MCUCSR,EXTI2_SENSE_BIT_0); break;
					}
					break;
		}
	}
}


void MEXTI_voidEnableINT (const u8 A_u8EXTI)
{
	if (A_u8EXTI <= EXTI2)
	{
		switch (A_u8EXTI)
		{
		case EXTI0:	SET_BIT(GICR,EXTI0_ENABLE_BIT); break;
		case EXTI1: SET_BIT(GICR,EXTI1_ENABLE_BIT); break;
		case EXTI2: SET_BIT(GICR,EXTI2_ENABLE_BIT); break;
		}
	}
}


void MEXTI_voidDisableINT (const u8 A_u8EXTI)
{
	if (A_u8EXTI <= EXTI2)
	{
		switch (A_u8EXTI)
		{
		case EXTI0:	CLR_BIT(GICR,EXTI0_ENABLE_BIT); break;
		case EXTI1: CLR_BIT(GICR,EXTI1_ENABLE_BIT); break;
		case EXTI2: CLR_BIT(GICR,EXTI2_ENABLE_BIT); break;
		}
	}
}


void MEXTI_voidClearFlag (const u8 A_u8EXTI)
{
	if (A_u8EXTI <= EXTI2)
	{
		switch (A_u8EXTI)
		{
		case EXTI0:	SET_BIT(GIFR,EXTI0_FLAG_BIT); break;
		case EXTI1: SET_BIT(GIFR,EXTI1_FLAG_BIT); break;
		case EXTI2: SET_BIT(GIFR,EXTI2_FLAG_BIT); break;
		}
	}
}

void MEXTI_voidSetCallback (const u8 A_u8EXTI, void (*ptrToFunc)(void))
{
	if ((A_u8EXTI <= EXTI2)&&(ptrToFunc!=NULL))
	{
		switch (A_u8EXTI)
		{
		case EXTI0:	EXTI0_callBack = ptrToFunc; break;
		case EXTI1: EXTI1_callBack = ptrToFunc; break;
		case EXTI2: EXTI2_callBack = ptrToFunc; break;
		}
	}
}

void __vector_1(void)	__attribute__((signal));
void __vector_1(void)
{
	if (EXTI0_callBack != NULL)
	{
		EXTI0_callBack();
	}
}

void __vector_2(void)	__attribute__((signal));
void __vector_2(void)
{
	if (EXTI1_callBack != NULL)
	{
		EXTI1_callBack();
	}
}

void __vector_3(void)	__attribute__((signal));
void __vector_3(void)
{
	if (EXTI2_callBack != NULL)
	{
		EXTI2_callBack();
	}
}

