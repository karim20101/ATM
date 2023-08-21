/*
 * UART_Interface.h
 *
 *  Created on: Jan 21, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_UART_UART_INTERFACE_H_
#define INCLUDE_MCAL_UART_UART_INTERFACE_H_

typedef enum
{
	INTERRUPT_DATA_REGISTER_EMPTY=0,
	INTERRUPT_TX_COMPLETE,
	INTERRUPT_RX_COMPLETE

}INTERRUPT_E;

typedef enum
{
	INTERRUPT_DISABLE=0,
	INTERRUPT_ENABLE

}INTERRUPT_STATE_E;

typedef enum
{
	FIVE_BITS=0,
	SIX_BITS,
	SEVEN_BITS,
	EIGHT_BITS,
	NINE_BITS=7
}DATA_BITS_E;

typedef enum
{
	ASYNCHRONOUS=0,
	SYNCHRONOUS
}OPERATION_MODE_E;

typedef enum
{
	P_DISABLED=0,
	P_EVEN=2,
	P_ODD
}PARITY_MODE_E;

typedef enum
{
	ONE_STOP_BIT=0,
	TWO_STOP_BIT,
}STOP_E;

typedef enum
{
	NORMAL_SPEED=0,
	DOUBLE_SPEED,
}SPEED_MODE_E;

void MUART_voidInit ();
void MUART_voidSendByteSynchBlocking (u8 A_u8Byte);
void MUART_voidSendString (const u8 *A_Pu8String);
void MUART_voidSendByteAsynch (u8 A_u8Byte);
u8 MUART_u8ReadByteSynchBlocking (void);
u8 MUART_u8ReadByteSynchNonBlocking (void);
u8 MUART_u8ReadByteASync (void);
void MUART_voidSetCallBack (INTERRUPT_E A_eInteeruptID, void (*A_PtrFunc)(void));






#endif /* INCLUDE_MCAL_UART_UART_INTERFACE_H_ */
