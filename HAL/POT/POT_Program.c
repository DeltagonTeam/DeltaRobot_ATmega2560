/**********************************************************************
 * Title		: Potentiometer Program File
 * Layer		: HAL
 * Author		: Ashraf Ehab, Mohamed ElHaddad
 * Last Update	: Oct 31, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "POT_Private.h"


/*Public Functions Definitions*/
/* 
 * Function	: POT_Init		: Initializes the Potentiometer
 * Input1 	: incpy_u8Pot	: the Potentiometer to be read initialized
 * Return 	: 				: Error Status of function
 */
ErrorStatus POT_Init(u8 incpy_u8Pot)
{
	return ADC_Init(incpy_u8Pot);
}

/*
 * Function	: POT_Read				: Reads the Potentiometer
 * Input1 	: incpy_u8Pot			: the Potentiometer to be read
 * Output1	: outptr_f32PotAngleRad	: Potentiometer angle in Radians
 * Return 	: 						: Error Status of function
 */
ErrorStatus POT_Read(u8 incpy_u8Pot, f32* outptr_f32PotAngleRad)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;
	u16 Loc_u16ADC_Out = 0;
	if (NULL == outptr_f32PotAngleRad)
	{
		return NULL_POINTER_PASSED;
	}
	Loc_ErrorStatusReturn = ADC_ReadChannel(incpy_u8Pot, &Loc_u16ADC_Out);
	if (NO_ERROR == Loc_ErrorStatusReturn)
	{
		*outptr_f32PotAngleRad = ( ((f32)Loc_u16ADC_Out / (f32)ADC_MAX_VALUE) ) * POT_RANGE;
	}
	return Loc_ErrorStatusReturn;
}
