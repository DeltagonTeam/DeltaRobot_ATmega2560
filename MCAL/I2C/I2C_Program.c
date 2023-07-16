/**********************************************************************
 * Title		: I2C Program File
 * Layer		:
 * Author		:
 * Last Update	: Dec 12, 2022
 **********************************************************************/

#include "I2C_Private.h"

/* Function	: I2C_Init      	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_Init()
{
	TWBR = I2C_BITRATE;
	TWSR = I2C_PRESCALAR;
	TWAR = (I2C_OWN_ADDRESS << 1) & ENABLE_GENERAL_CALL;
	return NO_ERROR;
}
/***********************************************************************************************************
 * Function	: I2C_Start      	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_Start()
{
	TWCR = START_CONDITION;
	while (! GET_BIT(TWCR, TWINT));
	if(START_SENT != (TWSR & STATUS_MASK))
	{
		return I2C_StartNotSent;
	}
	return NO_ERROR;
}
/***********************************************************************************************************
 * Function	: I2C_RepeatedStart : Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_RepeatedStart()
{
	TWCR = START_CONDITION;
	while (! GET_BIT(TWCR, TWINT));
	if(REPEATED_START_SENT != (TWSR & STATUS_MASK))
	{
		return I2C_RepeatedStartNotSent;
	}
	return NO_ERROR;
}
/***********************************************************************************************************
 * Function	: I2C_Restart      	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_Restart()
{
	TWCR = RESTART_CONDITION;
	while (! GET_BIT(TWCR, TWINT));
	if(START_SENT != (TWSR & STATUS_MASK))
	{
		return I2C_StartNotSent;
	}
	return NO_ERROR;
}
/***********************************************************************************************************
 * Function	: I2C_SendTo      	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_SendTo(u8 incpy_u8SlaveAddress)
{
	TWDR = (incpy_u8SlaveAddress << 1) | (0);	/*Place Address and Write bit in Data Register*/
	TWCR = START_TRANSMISSION;					/*Write START_TRANSMISSION on Control Register*/
	while (! GET_BIT(TWCR, TWINT));				/*Wait for Operation to End*/

	/*Check on Status Register*/
	if(SLA_W_NACK == (TWSR & STATUS_MASK))		
	{
		return I2C_No_ACK_Recieved;
	}
	else if(ARBITRATION_LOST == (TWSR & STATUS_MASK))
	{
		return I2C_Arbitration_Lost;
	}
	return NO_ERROR;
}
/***********************************************************************************************************
 * Function	: I2C_SendData     	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_SendData(u8 incpy_u8Data)
{
	TWDR = incpy_u8Data;				/*Place Data in Data Register*/
	TWCR = START_TRANSMISSION;			/*Write START_TRANSMISSION on Control Register*/
	while (! GET_BIT(TWCR, TWINT));		/*Wait for Operation to End*/

	/*Check on Status Register*/
	if(DATA_S_NACK == (TWSR & STATUS_MASK))		
	{
		return I2C_No_ACK_Recieved;
	}
	else if(ARBITRATION_LOST == (TWSR & STATUS_MASK))
	{
		return I2C_Arbitration_Lost;
	}
	return NO_ERROR;
}


/***********************************************************************************************************
 * Function	: I2C_ReciveFrom   	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_ReciveFrom(u8 incpy_u8SlaveAddress)
{
	TWDR = (incpy_u8SlaveAddress << 1) | (1);
	TWCR = START_TRANSMISSION;					/*Write START_TRANSMISSION on Control Register*/
	while (! GET_BIT(TWCR, TWINT));				/*Wait for Operation to End*/

	/*Check on Status Register*/
	if(SLA_R_NACK == (TWSR & STATUS_MASK))		
	{
		return I2C_No_ACK_Recieved;
	}
	else if(ARBITRATION_LOST == (TWSR & STATUS_MASK))
	{
		return I2C_Arbitration_Lost;
	}
	return NO_ERROR;
	
}
/***********************************************************************************************************
 * Function	: I2C_RecviveData  	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_RecviveData(u8 incpy_Send_ACK, u8* outptr_u8Data)
{
	if (I2C_DONOT_SEND_ACK == incpy_Send_ACK)
	{
		TWCR = START_RECEPTION_NACK;		/*Write START_RECEPTION_NACK on Control Register*/
	}
	else if (I2C_DO_SEND_ACK == incpy_Send_ACK)
	{
		TWCR = START_RECEPTION_ACK;			/*Write START_RECEPTION_ACK on Control Register*/
	}
	else 
	{
		return INVALID_PARAMETERS;
	}
	while (! GET_BIT(TWCR, TWINT));		/*Wait for Operation to End*/
	*outptr_u8Data = TWDR;
	return NO_ERROR;
}
/***********************************************************************************************************
 * Function	: I2C_Stop      	: Function Purpose
 * Input1 	: incpy_f32InExample: Input Description		: Options
 * Return 	: 					: Return Description	: Options
 */
ErrorStatus I2C_Stop()
{
	TWCR = STOP_CONDITION;
	while (! GET_BIT(TWCR, TWINT));
	return NO_ERROR;
}
