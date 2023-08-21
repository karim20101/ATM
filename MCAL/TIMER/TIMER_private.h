/*************************************************************************/
/* !File Name:         TIMER_private.h                                   */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         29 AUG, 2021                                      */
/* !Version  :         v1.0                                              */
/*************************************************************************/

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H
/****************************************** TIMER 0 REGISTERS *************************************/
#define     TCCR0		      *((volatile u8 *)(0x53))		// Timer/Counter0 Control Register
#define     TCCR0_FOC0        7								// Force On Compare
#define     TCCR0_WGM00       6                             // Wave Generation Mode 0
#define     TCCR0_COM01       5                             // Compare match output mode 1
#define     TCCR0_COM00       4                             // Compare match output mode 0
#define     TCCR0_WGM01       3                             // Wave Generation Mode 1
#define     TCCR0_CS02        2                             // Clock Select 02
#define     TCCR0_CS01        1                             // Clock Select 01
#define     TCCR0_CS00        0                             // Clock Select 00

#define     TCNT0		      *((volatile u8 *)(0x52))		// Timer/Counter0 Register

#define     OCR0		      *((volatile u8 *)(0x5C))		// Output Compare0 Register

#define     TIMSK		      *((volatile u8 *)(0x59))		// Timer0 Mask Register
#define     TIMSK_TOIE0       0								// Timer Overflow Interrupt Enable
#define     TIMSK_OCIE0       1                             // Timer On Compare Interrupt Enable
#define		TIMSK_TOIE1		  2								// Timer/Counter1 Overflow Interrupt Enable
#define		TIMSK_OCIE1B	  3								// Timer/Counter1 Output Compare B Interrupt Enable
#define		TIMSK_OCIE1A	  4								// Timer/Counter1 Output Compare A Interrupt Enable
#define		TIMSK_TICIE1	  5								// Timer/Counter1 Input Capture Interrupt Enable
#define     TIMSK_TOIE2       6								// Timer/Counter2 Overflow Interrupt Enable
#define     TIMSK_OCIE2       7								// Timer/Counter2 Output Compare Interrupt Enable

#define     TIFR              *((volatile u8 *)(0x58))		// Timer/Counter0 Interrupt Flag
#define     TIFR_TOV0         0								// Timer/Counter0 Overflow flag
#define     TIFR_OCF0         1                             // Timer/Counter0 Output Compare flag
#define		TIFR_TOV1		  2								// Timer/Counter1 Overflow Flag
#define		TIFR_OCF1B		  3								// Timer/Counter1 Output Compare B Flag
#define		TIFR_OCF1A		  4								// Timer/Counter1 Output Compare A Flag
#define		TIFR_ICF1		  5								// Timer/Counter1 Input Capture Flag
#define     TIFR_TOV2         6								// Timer/Counter2 Overflow flag
#define     TIFR_OCF2         7                             // Timer/Counter2 Output Compare flag


/****************************************** TIMER 1 REGISTERS *************************************/
#define		TCCR1A			         *((volatile u8 *)(0x4F))		// Timer/Counter 1 Control Register A
#define     TCCR1A_WGM10	         0								// Wave Generation Mode 0 Bit
#define     TCCR1A_WGM11	         1								// Wave Generation Mode 1 Bit
#define     TCCR1A_FOC1B	         2								// Force Output Compare B Bit
#define     TCCR1A_FOC1A	         3								// Force Output Compare A Bit
#define     TCCR1A_COM1B0	         4								// Compare Output Mode Channel B 0 Bit
#define     TCCR1A_COM1B1	         5								// Compare Output Mode Channel B 1 Bit
#define     TCCR1A_COM1A0	         6								// Compare Output Mode Channel A 0 Bit
#define     TCCR1A_COM1A1	         7								// Compare Output Mode Channel A 1 Bit


#define		TCCR1B			         *((volatile u8 *)(0x4E))		// Timer/Counter 1 Control Register B
#define     TCCR1B_CS10				 0								// Clock Selection 0 Bit
#define     TCCR1B_CS11				 1								// Clock Selection 1 Bit
#define     TCCR1B_CS12				 2								// Clock Selection 2 Bit
#define     TCCR1B_WGM12 			 3								// Wave Generation Mode 2 Bit
#define     TCCR1B_WGM13			 4								// Wave Generation Mode 3 Bit
#define     TCCR1B_ICES1			 6								// Input Capture Edge Select
#define     TCCR1B_ICNC1			 7								// Input Capture Noise Canceler


#define		TCNT1L					*((volatile u8 *)(0x4C))		// Timer/Counter 1 Low Register
#define		TCNT1H					*((volatile u8 *)(0x4D))		// Timer/Counter 1 High Register
#define		TCNT1					*((volatile u16 *)(0x4C))		// Timer/Counter 1 Register

#define		OCR1AL					*((volatile u8 *)(0x4A))		// Output Compare 1 Channel A Low Register
#define		OCR1AH					*((volatile u8 *)(0x4B))		// Output Compare 1 Channel A High Register
#define     OCR1A					*((volatile u16 *)(0x4A))		// Output Compare 1 Channel A Register

#define		OCR1BL					*((volatile u8 *)(0x48))		// Output Compare 1 Channel B Low Register
#define		OCR1BH					*((volatile u8 *)(0x49))		// Output Compare 1 Channel B High Register
#define     OCR1B					*((volatile u16 *)(0x48))		// Output Compare 1 Channel B Register

#define		ICR1L					*((volatile u8 *)(0x46))		// Input Capture 1 Low Register
#define		ICR1H					*((volatile u8 *)(0x47))		// Input Capture 1 High Register
#define     ICR1					*((volatile u16 *)(0x46))		// Input Capture 1 Register


#define     NULL_POINTER      (void *)0						// NULL_POINTER Definition

#endif
