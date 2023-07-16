/**********************************************************************
 * Title		: Math Private Header File
 * Layer		: Libraries
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Dec 8, 2022
 **********************************************************************/


#ifndef MATH_PRIVATE_H
#define MATH_PRIVATE_H


/*Include Needed Files*/
#include "MATH_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Pre-Build Configuration Macros Definitions*/
#define DO_INCLUDE		(1u)
#define DO_NOT_INCLUDE 	(2u)
/*__________________________________________________________________________________________________________________________________________*/


/*Pre-Build Configuration Checks*/
#if (DO_INCLUDE != MATH_INCLUDE_invsqrt) &&		(DO_NOT_INCLUDE != MATH_INCLUDE_invsqrt)
	#error 'MATH_INCLUDE_invsqrt' can only be 'DO_INCLUDE' or 'DO_NOT_INCLUDE'
#endif	/* MATH_INCLUDE_invsqrt */

#if (DO_INCLUDE != MATH_INCLUDE_sin) 	 &&		(DO_NOT_INCLUDE != MATH_INCLUDE_sin)
	#error 'MATH_INCLUDE_sin' can only be 'DO_INCLUDE' or 'DO_NOT_INCLUDE'
#endif	/* MATH_INCLUDE_sin */

#if (DO_INCLUDE != MATH_INCLUDE_atan) 	 &&		(DO_NOT_INCLUDE != MATH_INCLUDE_atan)
	#error 'MATH_INCLUDE_atan' can only be 'DO_INCLUDE' or 'DO_NOT_INCLUDE'
#endif	/* MATH_INCLUDE_atan */

#if (DO_INCLUDE != MATH_INCLUDE_atan2) 	 && 	(DO_NOT_INCLUDE != MATH_INCLUDE_atan2)
	#error 'MATH_INCLUDE_atan2' can only be 'DO_INCLUDE' or 'DO_NOT_INCLUDE'
#endif

#if (DO_INCLUDE != MATH_IMPROVE_invsqrt) &&		(DO_NOT_INCLUDE != MATH_IMPROVE_invsqrt)
	#error 'MATH_IMPROVE_invsqrt' can only be 'DO_INCLUDE' or 'DO_NOT_INCLUDE'
#endif	/* MATH_INCLUDE_atan2 */

#if (DO_INCLUDE != MATH_IMPROVE_sin) 	 &&		(DO_NOT_INCLUDE != MATH_IMPROVE_sin)
	#error 'MATH_IMPROVE_sin' can only be 'DO_INCLUDE' or 'DO_NOT_INCLUDE'
#endif	/* MATH_IMPROVE_sin */
/*__________________________________________________________________________________________________________________________________________*/


/*Private Definitions*/
#define MATH_FIS_MAGICNUM	(0x5F3759DF)	/* The Magic Number of the fast inverse square root */
#define MATH_4_PI2			(0.4052847F)	/* 4 /(PI^2)    */
#define MATH_PI_SQRT2		(2.2214414F)	/* PI / sqrt(2) */
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Declarations*/
/* 
 * Function	: MATH_sinHelper		: Calculates the error sin function to increase the accuracy of the sin function
 * Input1 	: incpy_f32ThetaError	: Theta of the error function	: -maximum of f32 to + maximum of f32
 * Return 	: 						: the sine of the input angle	: -1 to 1
 */
#if (DO_INCLUDE == MATH_INCLUDE_sin || DO_INCLUDE == MATH_INCLUDE_atan || DO_INCLUDE == MATH_INCLUDE_atan2) && (DO_INCLUDE == MATH_IMPROVE_sin)
	static f32 MATH_sinHelper(f32 incpy_f32Theta);
#endif
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MATH_PRIVATE_H*/
