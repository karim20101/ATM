/*******************************************************************************************
* ! Title          : WDT_private
* ! File Name      : WDT_private.h
* ! Layer          : MCAL
* ! Compiler       : GNU winAVR Cross Compiler
* ! Target         : Atmega32 Microcontroller
********************************************************************************************/
/*******************************************************************************************
* LOG :
* VERSION    AUTHOR                                   DESCRIPTION
* v1.0       Abdullah Mustafa  			              - Initial creation
********************************************************************************************/


#ifndef WDT_PRIVATE_H
#define WDT_PRIVATE_H

#define		WDTCR			*((volatile u8 *)(0x41))			// Watchdog Timer Control Register
#define 	WDTCR_WDP0		0									// Watchdog Timer Prescaler 0
#define 	WDTCR_WDP1		1									// Watchdog Timer Prescaler 1
#define 	WDTCR_WDP2		2									// Watchdog Timer Prescaler 2
#define 	WDTCR_WDE		3									// Watchdog Timer Enable
#define 	WDTCR_WDTOE		4									// Watchdog Timer Turn-off Enable


#define 	PRESCALER_RESET_MASK		0xF8					// Reset Mask For the first three bits 0b11111000 
#define		MAX_NUMBER_FOR_PRESCALER	8						// The Maximum Value That Prescaler Has

#endif