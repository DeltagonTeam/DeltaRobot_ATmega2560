/**********************************************************************
 * Title		: Joystick Program File
 * Layer		: HAL
 * Author		: Ali Azmy, Mostafa Rashad
 * Last Update	: Apr 06, 2023
 **********************************************************************/


/*Include Needed Files*/
#include "JOY_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: JOY_Init			: Initializes the Joystick
 * Input1 	: incpy_u8JoyNumber	: Joystick number	: JOYSTICK0 - JOYSTICK7
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus JOY_Init(u8 incpy_u8JoyNumber)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;
	switch (incpy_u8JoyNumber)
	{
	case JOYSTICK0:
		Loc_ErrorStatusReturn = ADC_Init(JOY0_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY0_Y);
		break;

	case JOYSTICK1:
		Loc_ErrorStatusReturn = ADC_Init(JOY1_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY1_Y);
		break;

	case JOYSTICK2:
		Loc_ErrorStatusReturn = ADC_Init(JOY2_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY2_Y);
		break;

	case JOYSTICK3:
		Loc_ErrorStatusReturn = ADC_Init(JOY3_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY3_Y);
		break;

	case JOYSTICK4:
		Loc_ErrorStatusReturn = ADC_Init(JOY4_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY4_Y);
		break;

	case JOYSTICK5:
		Loc_ErrorStatusReturn = ADC_Init(JOY5_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY5_Y);
		break;

	case JOYSTICK6:
		Loc_ErrorStatusReturn = ADC_Init(JOY6_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY6_Y);
		break;

	case JOYSTICK7:
		Loc_ErrorStatusReturn = ADC_Init(JOY7_X);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		return ADC_Init(JOY7_Y);
		break;

	default:
		return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}

/*
 * Function	: JOY_Read				    : Reads Joy Stick values
 * Input1 	: incpy_u8JoyNumber	        : Joystick number			: JOYSTICK0 - JOYSTICK7
 * Output1	: outptr_JOY_StatusReturn   : Joystick Status (XPercent, YPercent)
 * Return 	: ErrorStatus				: Error Status of function
 */
ErrorStatus JOY_Read(u8 incpy_u8JoyNumber, JOY_Status* outptr_JOY_StatusReturn)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;
	u16 Loc_u16ADC_Out = 0;
	if (NULL == outptr_JOY_StatusReturn)
	{
		return NULL_POINTER_PASSED;
	}
	switch (incpy_u8JoyNumber)
	{
	case JOYSTICK0:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY0_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY0_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	case JOYSTICK1:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY1_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY1_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	case JOYSTICK2:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY2_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY2_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	case JOYSTICK3:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY3_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY3_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	case JOYSTICK4:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY4_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY4_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	case JOYSTICK5:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY5_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY5_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	case JOYSTICK6:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY6_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY6_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	case JOYSTICK7:
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY7_X, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> XPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		Loc_ErrorStatusReturn = ADC_ReadChannel(JOY7_Y, &Loc_u16ADC_Out);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		outptr_JOY_StatusReturn -> YPercent = ( Loc_u16ADC_Out * 42 / ADC_MAX_VALUE * 5) - 105 ;
		break;

	default:
		return INVALID_PARAMETERS;
	}

	if(outptr_JOY_StatusReturn -> XPercent > 0)
	{
		outptr_JOY_StatusReturn -> XPercent -= 5;
		if (outptr_JOY_StatusReturn -> XPercent < 0)
		{
			outptr_JOY_StatusReturn -> XPercent = 0;
		}
	}
	else if (outptr_JOY_StatusReturn -> XPercent < 0)
	{
		outptr_JOY_StatusReturn -> XPercent += 5;
		if(outptr_JOY_StatusReturn -> XPercent > 0)
		{
			outptr_JOY_StatusReturn -> XPercent = 0;
		}
	}
	else
	{
		/*If already zero, Do Nothing*/
	}
	if(outptr_JOY_StatusReturn -> YPercent > 0)
	{
		outptr_JOY_StatusReturn -> YPercent -= 5;
		if (outptr_JOY_StatusReturn -> YPercent < 0)
		{
			outptr_JOY_StatusReturn -> YPercent = 0;
		}
	}
	else if (outptr_JOY_StatusReturn -> YPercent < 0)
	{
		outptr_JOY_StatusReturn -> YPercent += 5;
		if(outptr_JOY_StatusReturn -> YPercent > 0)
		{
			outptr_JOY_StatusReturn -> YPercent = 0;
		}
	}
	else
	{
		/*If already zero, Do Nothing*/
	}
	return NO_ERROR;
}
