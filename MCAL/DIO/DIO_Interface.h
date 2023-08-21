/*
 * DIO_Interface.h
 *
 *  Created on: Dec 2, 2022
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_DIO_DIO_INTERFACE_H_
#define INCLUDE_MCAL_DIO_DIO_INTERFACE_H_

#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3

#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

#define DIO_INPUT	 0
#define DIO_OUTPUT	 1

#define DIO_HIGH	 1
#define DIO_LOW 	 0

#define DIO_FLOATING 0
#define DIO_PULLUP	 1


void MDIO_voidInit(void);

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
void MDIO_voidSetPinDirection (const u8 A_u8Port, const u8 A_u8Pin, const u8 A_u8Direction);


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
void MDIO_voidSetPinValue     (const u8 A_u8Port, const u8 A_u8Pin, const u8 A_u8Value);

u8 MDIO_u8GetPinValue(const u8 A_u8Port, const u8 A_u8Pin);
void MDIO_voidSetPortDirection (const u8 A_u8Port,const u8 A_u8Direction);
void MDIO_voidSetPortValue     (const u8 A_u8Port,const u8 A_u8Value);
void MDIO_voidTogglePin        (const u8 A_u8Port, const u8 A_u8Pin);
u8 MDIO_u8GetPortValue (const u8 A_u8Port);
#endif /* INCLUDE_MCAL_DIO_DIO_INTERFACE_H_ */
