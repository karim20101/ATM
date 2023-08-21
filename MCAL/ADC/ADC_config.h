/*************************************************************************/
/* !File Name:         ADC_config.h                                      */
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         25 AUG, 2021                                      */
/* !Version  :         v1.0                                              */
/*************************************************************************/
#ifndef		ADC_CONFIG_H
#define		ADC_CONFIG_H

/* Options:
			ADC_AREF	
			ADC_AVCC    
			ADC_INTERNAL
*/
#define		ADC_REFVOLT		ADC_AVCC


/* Options:
			ENABLE	
            DISABLE
*/
#define		ADC_ADJUST_CTRL		 LEFT

#define     ADC_PRESCALAR_VAL    ADC_PRESCALAR_BY_2


#endif
