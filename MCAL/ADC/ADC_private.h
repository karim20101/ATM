/*************************************************************************/
/* !File Name:         ADC_private.h                                     */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         25 AUG, 2021                                      */
/* !Version  :         v1.0                                              */
/*************************************************************************/

#ifndef		ADC_PRIVATE_H
#define		ADC_PRIVATE_H


#define     ADMUX        *((volatile u8 *)(0x27))
#define     ADMUX_MUX0   0
#define     ADMUX_MUX1   1
#define     ADMUX_MUX2   2
#define     ADMUX_MUX3   3
#define     ADMUX_MUX4   4
#define     ADMUX_ADLAR  5
#define     ADMUX_REFS0  6
#define     ADMUX_REFS1  7

#define     ADCSRA       *((volatile u8 *)(0x26))
#define     ADCSRA_ADPS0  0
#define     ADCSRA_ADPS1  1
#define     ADCSRA_ADPS2  2
#define     ADCSRA_ADIE   3
#define     ADCSRA_ADIF   4
#define     ADCSRA_ADATE  5
#define     ADCSRA_ADSC   6
#define     ADCSRA_ADEN   7

#define		ADCH		*((volatile u8 *)(0x25))

#define		ADC_AREF	  0
#define     ADC_AVCC      1
#define     ADC_INTERNAL  2	

#define     LEFT		  1
#define     RIGHT         0


#define		ADC_PRES_MASK		0b11111000
#define		ADC_CHANNEL_MASK	0b11100000

#define		NOTBUSY			0
#define		BUSY			1


#define		NULL_POINTER	(void *) 0







#endif
