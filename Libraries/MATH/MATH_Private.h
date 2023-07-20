/**********************************************************************
 * Title		: Math version 2 Private Header File
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
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MATH_PRIVATE_H*/
