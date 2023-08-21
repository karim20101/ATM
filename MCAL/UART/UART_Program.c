/*
 * UART_Program.c
 *
 *  Created on: Jan 21, 2023
 *      Author: abdelrahmanhossam
 */


#include <util/delay.h>
#include "..\..\LIB/STD_TYPES.h"
#include "..\..\LIB/BIT_MATH.h"

#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Cfg.h"

#define NULL 0
void (*FuncPTR[3])(void)= {NULL,NULL,NULL};

void MUART_voidInit ()
{
	u16 local_u16BaudRateValue = BAUD_RATE_EQUATION;
	u8 local_bit2Value = GET_BIT(CHARACTER_SIZE,2);
	u8 local_bit1Value = GET_BIT(CHARACTER_SIZE,1);
	u8 local_bit0Value = GET_BIT(CHARACTER_SIZE,0);

	if (SPEED_MODE == NORMAL_SPEED)
	{
		CLR_BIT(UCSRA,1);
	}
	else if (SPEED_MODE == DOUBLE_SPEED)
	{
		SET_BIT(UCSRA,1);
		local_u16BaudRateValue *= 2;
	}

	/* Store the low byte of the UBBR*/
	UBRRL = (u8)local_u16BaudRateValue;
	/* Store the high byte of the UBBR*/
	UBRRH = (u8) (local_u16BaudRateValue>>8);

	UCSRB &= (0b00000011);

	UCSRB |= ((local_bit2Value<<2)|(RX_INTERRUPT_ENABLE<<7)|(TX_INTERRUPT_ENABLE<<6)|
			  (DATA_REG_EMPTY_INTERRUPT_ENABLE<<5)|(1<<4)|(1<<3));

	u8 local_uscrcValue = ((1<<7)|(MODE_OF_OPERATION<<6)|(PARITY_MODE<<4)|(STOP_BITS<<3)
						 |(local_bit1Value<<2)|(local_bit0Value<<1)) ;

	UCSRC = local_uscrcValue;

}

void MUART_voidSendByteSynchBlocking (u8 A_u8Byte)
{
	/* Check the UDRE if the UDR register empty or not */
	while(GET_BIT(UCSRA,5)==0);

	// Set data at UDR
	UDR = A_u8Byte;

	// Check on transmission complete flag
	while(GET_BIT(UCSRA,5)==0);

	// Clear transmission flag
	SET_BIT(UCSRA,6);
}

void MUART_voidSendByteSynchNonBlocking (u8 A_u8Byte)
{
	u32 local_u32TimeOut = 0;
	/* Check the UDRE if the UDR register empty or not */
	while(GET_BIT(UCSRA,5)==0)
	{
		local_u32TimeOut++;
		if (local_u32TimeOut == NON_BLOCKING_TIME_OUT)
		{
			break;
		}
	}

	if (local_u32TimeOut != NON_BLOCKING_TIME_OUT)
	{
		local_u32TimeOut = 0;
		// Set data at UDR
		UDR = A_u8Byte;
		while(GET_BIT(UCSRA,5)==0)
		{
			local_u32TimeOut++;
			if (local_u32TimeOut == NON_BLOCKING_TIME_OUT)
			{
				break;
			}
		}
		// Clear transmission flag
		SET_BIT(UCSRA,6);
	}
}

void MUART_voidSendString (const u8 *A_Pu8String)
{
	while (*A_Pu8String>0)
	{
		MUART_voidSendByteSynchNonBlocking (*A_Pu8String++);
	}
}


void MUART_voidSendByteAsynch (u8 A_u8Byte)
{
	if(GET_BIT(UCSRA,5)==1)
	{
		UDR = A_u8Byte;
	}
}

u8 MUART_u8ReadByteSynchBlocking (void)
{
	// check on receiving flag
	while(GET_BIT(UCSRA,7)==0);
	return UDR;
}

u8 MUART_u8ReadByteSynchNonBlocking (void)
{
	u32 local_u32TimeOut = 0;
	u8 local_u8ReturnValue = RETURN_NO_RECEIVED_DATA;
	// check on receiving flag
	while(GET_BIT(UCSRA,7)==0)
	{
		local_u32TimeOut++;
		if (local_u32TimeOut == NON_BLOCKING_TIME_OUT)
		{
			break;
		}
	}
	if (local_u32TimeOut != NON_BLOCKING_TIME_OUT)
	{
		local_u8ReturnValue = UDR;
	}

	return local_u8ReturnValue;
}

u8 MUART_u8ReadByteASync (void)
{
	return UDR;
}


void MUART_voidSetCallBack (INTERRUPT_E A_eInteeruptID, void (*A_PtrFunc)(void))
{
	if (   (A_eInteeruptID >=INTERRUPT_DATA_REGISTER_EMPTY)
		&& (A_eInteeruptID <=INTERRUPT_RX_COMPLETE )
		&& (A_PtrFunc!=NULL))
	{
		FuncPTR[A_eInteeruptID] = A_PtrFunc;
	}
}


void __vector_13(void)	__attribute__((signal));
void __vector_13(void)
{
	if (FuncPTR[INTERRUPT_RX_COMPLETE]!=NULL)
	{
		FuncPTR[INTERRUPT_RX_COMPLETE]();
	}
}

void __vector_14(void)	__attribute__((signal));
void __vector_14(void)
{
	if (FuncPTR[INTERRUPT_DATA_REGISTER_EMPTY]!=NULL)
	{
		FuncPTR[INTERRUPT_DATA_REGISTER_EMPTY]();
	}
}

void __vector_15(void)	__attribute__((signal));
void __vector_15(void)
{
	if (FuncPTR[INTERRUPT_TX_COMPLETE]!=NULL)
	{
		FuncPTR[INTERRUPT_TX_COMPLETE]();
	}
}
