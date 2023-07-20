/**********************************************************************
 * Title		: ADC Program File
 * Layer		: MCAL
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Jan 7, 2023
 **********************************************************************/


/*Include Needed Files*/
#include "ADC_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: ADC_Init					: Initializes the ADC
 * Input1 	: incpy_u8Channel			: The channel to be initialized
 * Return 	: ErrorStatus	    		: Error Status of function
 */
ErrorStatus ADC_Init(u8 incpy_u8Channel)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;
	if (ADC_CHANNEL7 >= incpy_u8Channel) 		/*with PORTF*/
	{
		SET_BIT(DIDR0, incpy_u8Channel);		/*Disable Digital Input to reduce power consumption in the digital input buffer*/
		Loc_ErrorStatusReturn = DIO_PinInit (DIO_PORTF, incpy_u8Channel, DIO_PIN_INPUT, DIO_PIN_NOPULLUP);
	}
	else if (ADC_CHANNEL15 >= incpy_u8Channel) 	/*with PORTK*/
	{
		SET_BIT(DIDR2, incpy_u8Channel);		/*Disable Digital Input to reduce power consumption in the digital input buffer*/
		Loc_ErrorStatusReturn = DIO_PinInit (DIO_PORTK, incpy_u8Channel-ADC_CHANNEL8, DIO_PIN_INPUT, DIO_PIN_NOPULLUP);
	}
	else
	{
		return INVALID_PARAMETERS;
	}
	if (NO_ERROR != Loc_ErrorStatusReturn)
	{
		return Loc_ErrorStatusReturn;
	}

	/* ADMUX Register Bits Description:
	 * REFS1:0 (bits 7:6)   select reference voltage mode
	 * ADLAR   (bit 5)		0 to choose right adjusted
	 * MUX4:0  (bits 4:0)	to choose channel input channel
	 */
	ADMUX = ADC_REF_VOLTAGE << REFS0;

	/* ADCSRA Register Bits Description:
	 * ADEN		(bit 7)		1 to enable ADC
	 * ADSC		(bit 6)		start conversion
	 * ADATE	(bit 5)		0 to disable Auto Trigger
	 * ADIF		(bit 4)		ADC Interrupt Flag
	 * ADIE    	(bit 3)		0 to disable ADC Interrupt
	 * ADPS2:0  (bits 2:0)	choose ADC_Clock --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = ADC_PRESCALER;
	SET_BIT(ADCSRA, ADEN);
	return NO_ERROR;
}

/*
 * Function	: ADC_ReadChannel		: Reads an analog input from the chosen channel
 * Input1 	: incpy_u8Channel		: Channel to read			: ADC_CHANNEL0-ADC_CHANNEL15
 * Output1	: outptr_u16ADCVal		: Value of the ADC reading	: 0 - ADC_MAX_VALUE
 * Return 	: ErrorStatus	    	: Error Status of function
 */
ErrorStatus ADC_ReadChannel(u8 incpy_u8Channel, u16* outptr_u16ADCVal)
{
	u8 Loc_GlobINT_Status = 0;
	if (NULL == outptr_u16ADCVal)
	{
		return NULL_POINTER_PASSED;
	}
	/*MUX5 = 0 with PORTF or 1 with PORTK*/
	if (ADC_CHANNEL7 >= incpy_u8Channel) 		/*with PORTF*/
	{
		CLR_BIT(ADCSRB,MUX5);
	}
	else if (ADC_CHANNEL15 >= incpy_u8Channel) 	/*with PORTK*/
	{
		SET_BIT(ADCSRB,MUX5);
		incpy_u8Channel &= 0x07;
	}
	else
	{
		return INVALID_PARAMETERS;
	}
	ADMUX &= 0xE0; 						/* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before setting the required channel */
	ADMUX |= incpy_u8Channel; 			/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA, ADSC); 				/* Start conversion write '1' to ADSC */
	while(!GET_BIT(ADCSRA, ADIF))
	{
		/* Polling :- Wait for conversion to complete, ADIF becomes '1' */
	}
	SET_BIT(ADCSRA, ADIF); 				/* Clear ADIF by writing '1' to it */

	/*Disabling Global Interrupt while accessing a 16-bit register*/
	Loc_GlobINT_Status = GET_GLOB_INT(void);
	DISABLE_GLOB_INT(void);
	*outptr_u16ADCVal = ADC;			/* Read the digital value from the ADC data register */
	MAKE_GLOB_INT(Loc_GlobINT_Status);

	return NO_ERROR;
}
