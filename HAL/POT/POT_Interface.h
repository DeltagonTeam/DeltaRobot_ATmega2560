/**********************************************************************
 * Title		: Potentiometer Interface Header File
 * Layer		: HAL
 * Author		: Ashraf Ehab, Mohamed ElHaddad
 * Last Update	: Oct 31, 2022
 **********************************************************************/


#ifndef POT_INTERFACE_H
#define POT_INTERFACE_H


/*Include Needed Files*/
#include "POT_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: POT_Init		: Initializes the Potentiometer
 * Input1 	: incpy_u8Pot	: the Potentiometer to be read initialized
 * Return 	: 				: Error Status of function
 */
ErrorStatus POT_Init(u8 incpy_u8Pot);

/*
 * Function	: POT_Read				: Reads the Potentiometer
 * Input1 	: incpy_u8Pot			: the Potentiometer to be read
 * Output1	: outptr_f32PotAngleRad	: Potentiometer angle in Radians
 * Return 	: 						: Error Status of function
 */
ErrorStatus POT_Read(u8 incpy_u8Pot, f32* outptr_f32PotAngleRad);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*POT_INTERFACE_H*/
