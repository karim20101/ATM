/*************************************************************************/
/* !File Name:         SPI_private.h                                     */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         1 SEP, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/
#ifndef		SPI_PRIVATE_H
#define		SPI_PRIVATE_H

#define		SPDR			*((volatile u8 *)(0x2F))			// SPI Data Register

#define		SPCR			*((volatile u8 *)(0x2D))			// SPI Control Register
#define     SPCR_SPR0		0									// SPI Prescaler Bit0
#define     SPCR_SPR1		1									// SPI Prescaler Bit1
#define     SPCR_CPHA		2									// Clock Phase
#define     SPCR_CPOL		3									// Clock Polarity
#define     SPCR_MSTR		4									// MASTER bit
#define     SPCR_DORD		5									// Data OverRun
#define     SPCR_SPE		6									// SPI Enable
#define     SPCR_SPIE		7									// SPI Interrupt Enable

#define		SPSR			*((volatile u8 *)(0x2E))			// SPI Status Register
#define		SPSR_SPI2X		0									// SPI Prescaler Bit2
#define		SPSR_WCOL		6									// SPI Write Collision Flag
#define		SPSR_SPIF		7									// SPI Interrupt Flag


#endif
