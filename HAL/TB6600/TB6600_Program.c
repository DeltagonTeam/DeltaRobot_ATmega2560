/**********************************************************************
 * Title		: TB6600 Stepper Motor Driver Program File
 * Layer		:
 * Author		:
 * Last Update	: Dec 12, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "TB6600_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: TB6600_Init			: Initializes the TB6600
 * Input1 	: incpy_u8MotorNumber	: Motor number		: TB_MOTOR0 - TB_MOTOR3
 * Return 	: 						: Error Status of function
 */
ErrorStatus TB6600_Init(u8 incpy_u8MotorNumber)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;
	switch (incpy_u8MotorNumber)
	{
	case TB_MOTOR0:
		Loc_ErrorStatusReturn = DIO_PinInit(TB0_DIR_PORT, TB0_DIR_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB0_ENA_PORT, TB0_ENA_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB0_PUL_PORT, TB0_PUL_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR1_Init(TMR1_PWM, TB_PRESCALER);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		break;

	case TB_MOTOR1:
		Loc_ErrorStatusReturn = DIO_PinInit(TB1_DIR_PORT, TB1_DIR_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB1_ENA_PORT, TB1_ENA_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB1_PUL_PORT, TB1_PUL_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR4_Init(TMR4_PWM, TB_PRESCALER);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		break;

	case TB_MOTOR2:
		Loc_ErrorStatusReturn = DIO_PinInit(TB2_DIR_PORT, TB2_DIR_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB2_ENA_PORT, TB2_ENA_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB2_PUL_PORT, TB2_PUL_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR5_Init(TMR5_PWM, TB_PRESCALER);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		break;

	case TB_MOTOR3:
		Loc_ErrorStatusReturn = DIO_PinInit(TB3_DIR_PORT, TB3_DIR_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB3_ENA_PORT, TB3_ENA_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = DIO_PinInit(TB3_PUL_PORT, TB3_PUL_PIN, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR3_Init(TMR3_PWM, TB_PRESCALER);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		break;

	default:	return INVALID_PARAMETERS;
	}
	return Loc_ErrorStatusReturn;
}

/* 
 * Function	: TB6600_Move			: Moves the motor
 * Input1 	: incpy_u8MotorNumber	: Motor number						: TB_MOTOR0 - TB_MOTOR3
 * Input2 	: incpy_u8Dir			: Motor direction					: TB_DIR_CW, TB_DIR_CCW
 * Input3 	: incpy_u8Speed			: Motor speed in pulses per second
 * Input4 	: inptr_vdISR			: Pointer to Function				: Function to be executed
 * Return 	: 						: Error Status of function
 */
ErrorStatus TB6600_Move(u8 incpy_u8MotorNumber, u8 incpy_u8Dir, u8 incpy_u8Speed, void (*inptr_vdISR) (void))
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	switch (incpy_u8MotorNumber)
	{
	case TB_MOTOR0:
		Loc_ErrorStatusReturn = DIO_WritePin(TB0_DIR_PORT, TB0_DIR_PIN, incpy_u8Dir);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR1_PWMStart(incpy_u8Speed, TRUE, inptr_vdISR);
		break;

	case TB_MOTOR1:
		Loc_ErrorStatusReturn = DIO_WritePin(TB1_DIR_PORT, TB1_DIR_PIN, incpy_u8Dir);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR4_PWMStart(incpy_u8Speed, TRUE, inptr_vdISR);
		break;

	case TB_MOTOR2:
		Loc_ErrorStatusReturn = DIO_WritePin(TB2_DIR_PORT, TB2_DIR_PIN, incpy_u8Dir);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR5_PWMStart(incpy_u8Speed, TRUE, inptr_vdISR);
		break;

	case TB_MOTOR3:
		Loc_ErrorStatusReturn = DIO_WritePin(TB3_DIR_PORT, TB3_DIR_PIN, incpy_u8Dir);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		Loc_ErrorStatusReturn = TMR3_PWMStart(incpy_u8Speed, TRUE, inptr_vdISR);
		break;

	default:	return INVALID_PARAMETERS;
	}

	return Loc_ErrorStatusReturn;
}

/* 
 * Function	: TB6600_Stop			: Stops the motor
 * Input1 	: incpy_u8MotorNumber	: Motor number		: TB_MOTOR0 - TB_MOTOR3
 * Return 	: 						: Error Status of function
 */
ErrorStatus TB6600_Stop(u8 incpy_u8MotorNumber)
{
	switch (incpy_u8MotorNumber)
	{
	case TB_MOTOR0:
		return TMR1_Stop();
		break;

	case TB_MOTOR1:
		return TMR4_Stop();
		break;

	case TB_MOTOR2:
		return TMR5_Stop();
		break;

	case TB_MOTOR3:
		return TMR3_Stop();
		break;

	default:	return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}
