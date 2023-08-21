/*************************************************************************/
/* !File Name:         TIMER_program.c                                   */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         30 AUG, 2021                                      */
/* !Version  :         v2.0                                              */
/*************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMER_interface.h"
#include "Timer_private.h"
#include "Timer_config.h"


void (* TIMER_pvTimer0NotificationFunction)(void) = NULL_POINTER; 
void (* TIMER_pvICUNotificationFunction)(void) = NULL_POINTER;

void TIMER_voidTimer0Init(void)
{
	/*Set Timer 0 in Fast PWM Mode*/
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
	
	/*Set The Prescaler to be 8*/
	CLR_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);

	/*Set The Set On TOP, Clear On Compare Mode (Non-Inverted)*/
	CLR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
}


void TIMER_voidTimer1Init(void)
{
	/*Select The Normal Mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TCCR1B, TCCR1B_WGM13);

	/*Set Prescaler to be 8*/
	CLR_BIT(TCCR1B, TCCR1B_CS10);
	SET_BIT(TCCR1B, TCCR1B_CS11);
	CLR_BIT(TCCR1B, TCCR1B_CS12);
}


void TIMER_voidTimer1ASetCompareValue(u16 Copy_u16CompareValue)
{
	/* Set The Compare Value To OCR1 Channel A Register*/
	OCR1A = Copy_u16CompareValue;
}

void TIMER_voidTimer1BSetCompareValue(u16 Copy_u16CompareValue)
{
	/* Set The Compare Value To OCR1 Channel B Register*/
	OCR1B = Copy_u16CompareValue;
}

void TIMER_voidTimer1SetInputCaptureValue(u16 Copy_u16CaptureValue)
{
	/*Set The Input Capture Value to ICR1 Register*/
	ICR1 = Copy_u16CaptureValue;
}


void TIMER_voidTimer0SetCompareValue(u8 Copy_u8CompareValue)
{
	/*Set The Compare Value to the OCR0 Register*/
	OCR0 = Copy_u8CompareValue;
}

void TIMER_voidTimer0SetCallBack(void (*Copy_pvNotificationFunction)(void))
{
	/*Assign the function address to the global pointer to function*/
	TIMER_pvTimer0NotificationFunction = Copy_pvNotificationFunction;
}


void ICU_voidInit(void)
{
	/*Set Trigger to rising edge initially*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable The ICU Interrupt*/
	SET_BIT(TIMSK, TIMSK_TICIE1);
}



void ICU_voidSetTrigger(u8 Copy_u8TriggerSource)
{
	switch(Copy_u8TriggerSource)
	{
		case RISING_EDGE:
			/*Set The Rising Edge to be the trigger source*/
			SET_BIT(TCCR1B, TCCR1B_ICES1);
			break;
		case FALLING_EDGE:
			/*Set The Falling Edge to be the trigger source*/
			CLR_BIT(TCCR1B, TCCR1B_ICES1);
			break;
		default:
			break;
	}
}

u16 ICU_u16ReadInputCapture(void)
{
	/*Get The Captured Value From ICR1 Register*/
	return ICR1;
}

void ICU_voidInterruptDisbale(void)
{
	/*Disable The ICU Interrupt*/
	CLR_BIT(TIMSK, TIMSK_TICIE1);
}

void ICU_voidSetCallBack(void (*Copy_pvNotificationFunction)(void))
{
	TIMER_pvICUNotificationFunction = Copy_pvNotificationFunction;
}

/*ISR for Timer0 Compare Match Event */
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	/*Check if the global pointer to function is changed or not*/
	if(TIMER_pvTimer0NotificationFunction != NULL_POINTER)
	{
		/*Execute the global pointer to function*/
		TIMER_pvTimer0NotificationFunction();
	}
}

/*ISR For ICU Capture Event*/
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(TIMER_pvICUNotificationFunction != NULL_POINTER)
	{
		TIMER_pvICUNotificationFunction();
	}
	else
	{
		/*Do Nothing*/
	}
}

