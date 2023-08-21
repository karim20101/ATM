/*************************************************************************/
/* !File Name:         ADC_program.h                                     */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         25 AUG, 2021                                      */
/* !Version  :         v1.0                                              */
/*************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../DIO/DIO_interface.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

u8 ADC_u8BusyFlag = NOTBUSY;

u8 ADC_u8Result;

void (*ADC_pvNotificationFunction)(void) = NULL_POINTER;

/* Function to initiate the ADC Peripheral using prebuild configuration concept*/
void ADC_voidInit(void)
{
	/*Set Reference Voltage*/
	#if		ADC_REFVOLT == ADC_AREF
		CLR_BIT(ADMUX, ADMUX_REFS0);
		CLR_BIT(ADMUX, ADMUX_REFS1);
	#elif   ADC_REFVOLT == ADC_AVCC
		SET_BIT(ADMUX, ADMUX_REFS0);
		CLR_BIT(ADMUX, ADMUX_REFS1);
	#elif   ADC_REFVOLT == ADC_INTERNAL
		SET_BIT(ADMUX, ADMUX_REFS0);
		SET_BIT(ADMUX, ADMUX_REFS1);
	#else
		#error "Error in ADC Reference volt configuration"
	#endif
	
	
	/*Activate The Left Adjust*/
	#if	ADC_ADJUST_CTRL == LEFT
		SET_BIT(ADMUX, ADMUX_ADLAR);
	#elif ADC_ADJUST_CTRL == RIGHT
		CLR_BIT(ADMUX, ADMUX_ADLAR);
	#else
		#error "Error in ADC_ADJUST_CTRL Configuration"
	#endif
	
	/*Set The Prescalar Configuration*/
	ADCSRA &= ADC_PRES_MASK;
	ADCSRA |= ADC_PRESCALAR_VAL;
	
	/*Enable the ADC Peripheral*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}


u8 ADC_u8StartConversionSynchronus(u8 Copy_u8ChannelNum)
{
	if(ADC_u8BusyFlag == BUSY)
	{
		return BUSY;
	}
	else
	{
		ADC_u8BusyFlag = BUSY;
		/*Set the required channel into the MUX bits in ADMUX Register*/
		ADMUX &= ADC_CHANNEL_MASK;			// Bit Masking
		ADMUX |= Copy_u8ChannelNum;

		/*Start Conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/*Polling (Busy Waiting) until the conversion is complete*/
		while(GET_BIT(ADCSRA, ADCSRA_ADIF) == 0);

		/*Conversion completed*/
		/*Clear the flag*/
		SET_BIT(ADCSRA, ADCSRA_ADIF);

		ADC_u8BusyFlag = NOTBUSY;

		return ADCH;
	}
}

u8 ADC_u8StartConversionAsynchronus(u8 Copy_u8ChannelNum, void (*Copy_pvCallBackFunctionPtr)(void))
{
	if(  (ADC_u8BusyFlag == BUSY) || (Copy_pvCallBackFunctionPtr == NULL_POINTER)  )
	{
		return 0;
	}
	else
	{
		ADC_u8BusyFlag = BUSY;
		/*Set the required channel into the MUX bits in ADMUX Register*/
		ADMUX &= ADC_CHANNEL_MASK;			// Bit Masking
		ADMUX |= Copy_u8ChannelNum;

		/*Set the Callback function*/
		ADC_pvNotificationFunction = Copy_pvCallBackFunctionPtr;

		/*Start Conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/*ADC interrupt Enable*/
		SET_BIT(ADCSRA, ADCSRA_ADIE);

		return ADC_u8Result;
	}
}



void __vector_16 (void)   __attribute__((signal));
void __vector_16 (void)
{

	/*Read ADC Result*/
	ADC_u8Result = ADCH;

	/*Make The ADC State to be NOTBUSY because it finished*/
	ADC_u8BusyFlag = NOTBUSY;

	/*Invoke the callback function*/
	ADC_pvNotificationFunction();

	/*Disable ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);
}





