/*************************************************************************/
/* !File Name:         SPI_program.c                                     */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         1 SEP, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"




void SPI_voidMasterInit(void)
{
	/*Set The Node To Be Master Node*/
	SET_BIT(SPCR, SPCR_MSTR);
	/*Set The MSB to be sent first*/
	CLR_BIT(SPCR, SPCR_DORD);

	/*Set The Leading Edge To be The Rising Edge*/
	CLR_BIT(SPCR, SPCR_CPOL);

	/*Sample At Leading Edge*/
	CLR_BIT(SPCR, SPCR_CPHA);

	/*Clock Prescaler, divide by 16*/
	SET_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
	CLR_BIT(SPSR, SPSR_SPI2X);
	/*Enable The SPI*/
	SET_BIT(SPCR, SPCR_SPE);
}

void SPI_voidSlaveInit(void)
{
	/*Set The Node To Be Salve Node*/
	CLR_BIT(SPCR, SPCR_MSTR);
	/*Set The MSB to be sent first*/
	CLR_BIT(SPCR, SPCR_DORD);

	/*Set The Leading Edge To be The Rising Edge*/
	CLR_BIT(SPCR, SPCR_CPOL);

	/*Sample At Leading Edge*/
	CLR_BIT(SPCR, SPCR_CPHA);
	/*Enable The SPI*/
	SET_BIT(SPCR, SPCR_SPE);
}


u8 SPI_u8Tranceive(u8 Copy_u8Data)
{
	/*Set The Data in SPDR Register To Send*/
	SPDR = Copy_u8Data;

	/*Polling (Busy Waiting) until the transfer complete*/
	while(GET_BIT(SPSR, SPSR_SPIF) == 0);

	/*Clear The Flag*/
	SET_BIT(SPSR, SPSR_SPIF);

	/*Get The Exchanged Data*/
	return SPDR;

}








