/**********************************************************************
 * Title		: ADC Interface Header File
 * Layer		: MCAL
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Jan 7, 2023
 **********************************************************************/


#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H


/*Include Needed Files*/
#include "ADC_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
#define ADC_MAX_VALUE    (1023u)

    /*ADC Channels*/
#define ADC_CHANNEL0	    (0u)
#define ADC_CHANNEL1	    (1u)
#define ADC_CHANNEL2	    (2u)
#define ADC_CHANNEL3	    (3u)
#define ADC_CHANNEL4	    (4u)
#define ADC_CHANNEL5	    (5u)
#define ADC_CHANNEL6	    (6u)
#define ADC_CHANNEL7	    (7u)
#define ADC_CHANNEL8	    (8u)
#define ADC_CHANNEL9	    (9u)
#define ADC_CHANNEL10	    (10u)
#define ADC_CHANNEL11	    (11u)
#define ADC_CHANNEL12	    (12u)
#define ADC_CHANNEL13	    (13u)
#define ADC_CHANNEL14	    (14u)
#define ADC_CHANNEL15	    (15u)
#define ADC_NOT_A_CHANNEL   (16u)
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: ADC_Init					: Initializes the ADC
 * Input1 	: incpy_u8Channel			: The channel to be initialized		: ADC_CHANNEL0 - ADC_CHANNEL15
 * Return 	: ErrorStatus	    		: Error Status of function
 */
ErrorStatus ADC_Init(u8 incpy_u8Channel);

/*
 * Function	: ADC_ReadChannel		: Reads an analog input from the chosen channel
 * Input1 	: incpy_u8Channel		: Channel to read			: ADC_CHANNEL0 - ADC_CHANNEL15
 * Output1	: outptr_u16ADCVal		: Value of the ADC reading	: 0 - ADC_MAX_VALUE
 * Return 	: ErrorStatus	    	: Error Status of function
 */
ErrorStatus ADC_ReadChannel(u8 incpy_u8Channel, u16* outptr_u16ADCVal);


#endif /*ADC_INTERFACE_H*/
