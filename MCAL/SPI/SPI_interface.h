/*************************************************************************/
/* !File Name:         SPI_interface.h                                   */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         1 SEP, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/
#ifndef		SPI_INTERFACE_H
#define		SPI_INTERFACE_H

void SPI_voidMasterInit(void);
void SPI_voidSlaveInit(void);
u8 SPI_u8Tranceive(u8 Copy_u8Data);



#endif
