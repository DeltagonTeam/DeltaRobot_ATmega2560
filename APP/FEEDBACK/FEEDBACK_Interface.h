/**********************************************************************
 * Title		: FEEDBACK Interface Header File
 * Layer		:
 * Author		:
 * Last Update	: Dec 12, 2022
 **********************************************************************/


#ifndef FEEDBACK_INTERFACE_H
#define FEEDBACK_INTERFACE_H


/*Include Needed Files*/
#include "FEEDBACK_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/*
 * Function	: FEEDBACK_Init		: a public function that initializes the potentiometers
 * Return 	:					: Error Status of function
 */
ErrorStatus FEEDBACK_Init(void);

/*
 * Function	: FEEDBACK_ReadCurrentThetas	: a public function that calculates the anglular positions of the driver links
 * Output1	: outptr_f32Thetas	            : an array with the anglular positions of the driver links
 * Return 	:					            : Error Status of function
 */
ErrorStatus FEEDBACK_ReadCurrentThetas(f32* outptr_f32Thetas);

/*
 * Function	: FEEDBACK_GetCorrection    	: a public function that calculates the offset of the anglular positions of the driver links
 * Return 	:					            : Error Status of function
 */
ErrorStatus FEEDBACK_GetCorrection(void);
/*__________________________________________________________________________________________________________________________________________*/

#endif /*FEEDBACK_INTERFACE_H*/
