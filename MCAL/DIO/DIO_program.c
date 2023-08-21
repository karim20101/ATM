/*
 * DIO_program.c
 *
 *  Created on: Dec 2, 2022
 *      Author: abdelrahmanhossam
 */

#include "..\..\LIB\STD_TYPES.h"
#include  "..\..\LIB\BIT_MATH.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "DIO_Cfg.h"


void MDIO_voidInit(void)
{
	// Set PORT A Pins Directions
	DDRA_REG = CONC_BIT(PORTA_PIN7_DIRECTION,PORTA_PIN6_DIRECTION,PORTA_PIN5_DIRECTION,
						PORTA_PIN4_DIRECTION,PORTA_PIN3_DIRECTION,PORTA_PIN2_DIRECTION,
						PORTA_PIN1_DIRECTION,PORTA_PIN0_DIRECTION);
	// Set PORT B Pins Directions
	DDRB_REG = CONC_BIT(PORTB_PIN7_DIRECTION,PORTB_PIN6_DIRECTION,PORTB_PIN5_DIRECTION,
						PORTB_PIN4_DIRECTION,PORTB_PIN3_DIRECTION,PORTB_PIN2_DIRECTION,
						PORTB_PIN1_DIRECTION,PORTB_PIN0_DIRECTION);
	// Set PORT C Pins Directions
	DDRC_REG = CONC_BIT(PORTC_PIN7_DIRECTION,PORTC_PIN6_DIRECTION,PORTC_PIN5_DIRECTION,
						PORTC_PIN4_DIRECTION,PORTC_PIN3_DIRECTION,PORTC_PIN2_DIRECTION,
						PORTC_PIN1_DIRECTION,PORTC_PIN0_DIRECTION);
	// Set PORT D Pins Directions
	DDRD_REG = CONC_BIT(PORTD_PIN7_DIRECTION,PORTD_PIN6_DIRECTION,PORTD_PIN5_DIRECTION,
						PORTD_PIN4_DIRECTION,PORTD_PIN3_DIRECTION,PORTD_PIN2_DIRECTION,
						PORTD_PIN1_DIRECTION,PORTD_PIN0_DIRECTION);

	PORTA_REG= CONC_BIT(PORTA_PIN7_VALUE,PORTA_PIN6_VALUE,PORTA_PIN5_VALUE,
						PORTA_PIN4_VALUE,PORTA_PIN3_VALUE,PORTA_PIN2_VALUE,
						PORTA_PIN1_VALUE,PORTA_PIN0_VALUE);

	PORTB_REG= CONC_BIT(PORTB_PIN7_VALUE,PORTB_PIN6_VALUE,PORTB_PIN5_VALUE,
						PORTB_PIN4_VALUE,PORTB_PIN3_VALUE,PORTB_PIN2_VALUE,
						PORTB_PIN1_VALUE,PORTB_PIN0_VALUE);

	PORTC_REG= CONC_BIT(PORTC_PIN7_VALUE,PORTC_PIN6_VALUE,PORTC_PIN5_VALUE,
						PORTC_PIN4_VALUE,PORTC_PIN3_VALUE,PORTC_PIN2_VALUE,
						PORTC_PIN1_VALUE,PORTC_PIN0_VALUE);

	PORTD_REG= CONC_BIT(PORTD_PIN7_VALUE,PORTD_PIN6_VALUE,PORTD_PIN5_VALUE,
						PORTD_PIN4_VALUE,PORTD_PIN3_VALUE,PORTD_PIN2_VALUE,
						PORTD_PIN1_VALUE,PORTD_PIN0_VALUE);
}


/******************************************************************************/
/* Function: MDIO_voidSetPinDirection                        				  */
/* I/P Parameters: A_u8Port,  A_u8Pin, A_u8Direction			          	  */
/* Returns:N/A				                                				  */
/* Desc:This Function Sets the direction of a given pin				       	  */
/******************************************************************************/
/* Options																	  */
/******************************************************************************/
/* A_u8Port     : DIO_PORTA - DIO_PORTB - DIO_PORTC - DIO_PORTD 			  */
/* A_u8Pin      : PIN0 ... PIN7       			                          	  */
/* A_u8Direction: DIO_INPUT - DIO_OUTPUT                        			  */
/******************************************************************************/
void MDIO_voidSetPinDirection (const u8 A_u8Port, const u8 A_u8Pin, const u8 A_u8Direction)
{
	// Input validation
	if ((A_u8Port <= DIO_PORTD) && (A_u8Pin <= PIN7) && (A_u8Direction <= DIO_OUTPUT))
	{
		switch (A_u8Port)
		{
		case DIO_PORTA:
			switch (A_u8Direction)
			{
			case DIO_INPUT : CLR_BIT(DDRA_REG,A_u8Pin);	break;
			case DIO_OUTPUT: SET_BIT(DDRA_REG,A_u8Pin);	break;
			}
			break;

		case DIO_PORTB:
			switch (A_u8Direction)
			{
			case DIO_INPUT : CLR_BIT(DDRB_REG,A_u8Pin);	break;
			case DIO_OUTPUT: SET_BIT(DDRB_REG,A_u8Pin);	break;
			}
			break;

		case DIO_PORTC:
			switch (A_u8Direction)
			{
			case DIO_INPUT : CLR_BIT(DDRC_REG,A_u8Pin);	break;
			case DIO_OUTPUT: SET_BIT(DDRC_REG,A_u8Pin);	break;
			}
			break;

		case DIO_PORTD:
			switch (A_u8Direction)
			{
			case DIO_INPUT : CLR_BIT(DDRD_REG,A_u8Pin);	break;
			case DIO_OUTPUT: SET_BIT(DDRD_REG,A_u8Pin);	break;
			}
			break;

		default: break;
		}
	}
}


/******************************************************************************/
/* Function: MDIO_voidSetPinValue	                        				  */
/* I/P Parameters: A_u8Port,  A_u8Pin, A_u8Value				          	  */
/* Returns:N/A				                                				  */
/* Desc:This Function Sets the value of a given pin in case of O/P      	  */
/*	    This Function Sets PULLUP state in case of I/P				      	  */
/******************************************************************************/
/* Options																	  */
/******************************************************************************/
/* A_u8Port     : DIO_PORTA - DIO_PORTB - DIO_PORTC - DIO_PORTD 			  */
/* A_u8Pin      : PIN0 ... PIN7       			                          	  */
/* A_u8Value:	I/P --> DIO_FLOATING - DIO_PULLUP                      		  */
/*				O/P --> DIO_LOW      - DIO_HIGH                      		  */
/******************************************************************************/
void MDIO_voidSetPinValue     (const u8 A_u8Port, const u8 A_u8Pin, const u8 A_u8Value)
{
	// Input validation
	if ((A_u8Port <= DIO_PORTD) && (A_u8Pin <= PIN7) && (A_u8Value <= DIO_HIGH))
	{
		switch (A_u8Port)
		{
		case DIO_PORTA:
			switch (A_u8Value)
			{
			case DIO_LOW   : CLR_BIT(PORTA_REG,A_u8Pin);	break;
			case DIO_HIGH  : SET_BIT(PORTA_REG,A_u8Pin);	break;
			}
			break;

		case DIO_PORTB:
			switch (A_u8Value)
			{
			case DIO_LOW   : CLR_BIT(PORTB_REG,A_u8Pin);	break;
			case DIO_HIGH  : SET_BIT(PORTB_REG,A_u8Pin);	break;
			}
			break;

		case DIO_PORTC:
			switch (A_u8Value)
			{
			case DIO_LOW   : CLR_BIT(PORTC_REG,A_u8Pin);	break;
			case DIO_HIGH  : SET_BIT(PORTC_REG,A_u8Pin);	break;
			}
			break;

		case DIO_PORTD:
			switch (A_u8Value)
			{
			case DIO_LOW   : CLR_BIT(PORTD_REG,A_u8Pin);	break;
			case DIO_HIGH  : SET_BIT(PORTD_REG,A_u8Pin);	break;
			}
			break;

		default: break;
		}
	}
}

u8 MDIO_u8GetPinValue(const u8 A_u8Port, const u8 A_u8Pin)
{
	u8 local_u8PinValue=255;
	if ((A_u8Port <= DIO_PORTD) && (A_u8Pin <= PIN7))
	{
		switch (A_u8Port)
		{
		case DIO_PORTA:	local_u8PinValue = GET_BIT(PINA_REG,A_u8Pin); break;
		case DIO_PORTB: local_u8PinValue = GET_BIT(PINB_REG,A_u8Pin); break;
		case DIO_PORTC: local_u8PinValue = GET_BIT(PINC_REG,A_u8Pin); break;
		case DIO_PORTD: local_u8PinValue = GET_BIT(PIND_REG,A_u8Pin); break;
		default 	  : break;
		}
	}
	return local_u8PinValue;
}


void MDIO_voidSetPortDirection (const u8 A_u8Port,const u8 A_u8Direction)
{
	if (A_u8Port <= DIO_PORTD)
	{
		switch (A_u8Port)
		{
		case DIO_PORTA:	DDRA_REG = A_u8Direction; break;
		case DIO_PORTB:	DDRB_REG = A_u8Direction; break;
		case DIO_PORTC:	DDRC_REG = A_u8Direction; break;
		case DIO_PORTD:	DDRD_REG = A_u8Direction; break;
		default		  : break;
		}
	}
}


void MDIO_voidSetPortValue     (const u8 A_u8Port,const u8 A_u8Value)
{
	if (A_u8Port <= DIO_PORTD)
	{
		switch (A_u8Port)
		{
		case DIO_PORTA:	PORTA_REG = A_u8Value; break;
		case DIO_PORTB:	PORTB_REG = A_u8Value; break;
		case DIO_PORTC:	PORTC_REG = A_u8Value; break;
		case DIO_PORTD:	PORTD_REG = A_u8Value; break;
		default		  : break;
		}
	}
}


void MDIO_voidTogglePin (const u8 A_u8Port, const u8 A_u8Pin)
{
	if ((A_u8Port <= DIO_PORTD) && (A_u8Pin <= PIN7))
	{
		switch (A_u8Port)
		{
		case DIO_PORTA: TOGGLE_BIT(PORTA_REG,A_u8Pin); break;
		case DIO_PORTB:	TOGGLE_BIT(PORTB_REG,A_u8Pin); break;
		case DIO_PORTC:	TOGGLE_BIT(PORTC_REG,A_u8Pin); break;
		case DIO_PORTD:	TOGGLE_BIT(PORTD_REG,A_u8Pin); break;
		default		  : break;
		}
	}
}

u8 MDIO_u8GetPortValue (const u8 A_u8Port)
{
	u8 local_u8PortValue = 0;
	if (A_u8Port <= DIO_PORTD)
	{
		switch (A_u8Port)
		{
		case DIO_PORTA: local_u8PortValue = PINA_REG; break;
		case DIO_PORTB:	local_u8PortValue = PINB_REG; break;
		case DIO_PORTC:	local_u8PortValue = PINC_REG; break;
		case DIO_PORTD:	local_u8PortValue = PIND_REG; break;
		default		  : break;
		}
	}
	return local_u8PortValue;
}
