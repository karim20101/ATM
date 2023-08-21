/*************************************************************************/
/* !File Name:         ADC_interface.h                                   */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         25 AUG, 2021                                      */
/* !Version  :         v1.0                                              */
/*************************************************************************/
#ifndef		ADC_INTERFACE_H
#define		ADC_INTERFACE_H




#define     ADC_PRESCALAR_BY_2         1
#define     ADC_PRESCALAR_BY_4         2
#define     ADC_PRESCALAR_BY_8         3
#define     ADC_PRESCALAR_BY_16        4
#define     ADC_PRESCALAR_BY_32        5
#define     ADC_PRESCALAR_BY_64        6
#define     ADC_PRESCALAR_BY_128       7


#define		ADC_CHANNEL_0				0
#define		ADC_CHANNEL_1				1
#define		ADC_CHANNEL_2				2
#define		ADC_CHANNEL_3				3
#define		ADC_CHANNEL_4				4
#define		ADC_CHANNEL_5				5
#define		ADC_CHANNEL_6				6
#define		ADC_CHANNEL_7				7
void ADC_voidInit(void);
u8 ADC_u8StartConversionSynchronus(u8 Copy_u8ChannelNum);
u8 ADC_u8StartConversionAsynchronus(u8 Copy_u8ChannelNum, void (*Copy_pvCallBackFunctionPtr)(void));


#endif
