/*************************************************************************/
/* !File Name:         TWI_program.c                                     */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         2 SEP, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/

#include "../../LIB/STD_TYPES.h"
#define F_CPU	8000000UL
#include <util/delay.h>

#include "../../MCAL/TWI/TWI_interface.h"
#include "../../MCAL/UART/UART_interface.h"
#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte)
{
	u8 Local_u8AddressPacket;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (A2_CONNECTION <<2) | (u8)(Copy_u16LocationAddress >>8);

	/*if 24C02 :
	 * 	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | A2_CONNECTION <<2 | A1_CONNECTION <<1 | A0_CONNECTION;
	 */

	/*Send start condition*/
	TWI_ErrorStatusSendStartConditionWithACK();

	/*Send the address packet*/
	TWI_ErrorStatusSendSlaveAddressWithWriteACK(Local_u8AddressPacket);

	/*Send the rest 8bits of the location address*/
	TWI_ErrorStatusMasterWriteDataByteWithACK((u8)Copy_u16LocationAddress);

	/*Send the data byte to the memory location*/
	TWI_ErrorStatusMasterWriteDataByteWithACK(Copy_u8DataByte);

	/*Send stop condition*/
	TWI_voidSendStopCondition();

	/*Delay until the write cycle is finished*/
	_delay_ms(10);
}

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress)
{
	u8 Local_u8AddressPacket, Local_u8Data;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (A2_CONNECTION <<2) | (u8)(Copy_u16LocationAddress >>8);

	/*if 24C02 :
	 * 	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | A2_CONNECTION <<2 | A1_CONNECTION <<1 | A0_CONNECTION;
	 */

	/*Send start condition*/
	TWI_ErrorStatusSendStartConditionWithACK();

	/*Send the address packet with write request*/
	TWI_ErrorStatusSendSlaveAddressWithWriteACK(Local_u8AddressPacket);

	/*Send the rest 8bits of the location address*/
	TWI_ErrorStatusMasterWriteDataByteWithACK((u8)Copy_u16LocationAddress);

	/*Send repeated start to change write request into read request*/
	TWI_ErrorStatusSendRepeatedStartConditionWithACK();

	/*Send the address packet with read request*/
	TWI_ErrorStatusSendSlaveAddressWithReadACK(Local_u8AddressPacket);
	
	/*Get the data from memory*/
	TWI_ErrorStatusMasterReadDataByteWithACK(&Local_u8Data);

	/*send the stop condition*/
	TWI_voidSendStopCondition();

	MUART_voidSendByteAsynch ( Local_u8Data);


	return Local_u8Data;

}
