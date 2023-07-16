/**********************************************************************
 * Title		: Math Configuration Header File
 * Layer		: Libraries
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Dec 8, 2022
 **********************************************************************/


#ifndef MATH_CONFIG_H
#define MATH_CONFIG_H


/*Include Needed Files*/
#include <string.h>
#include "../MACROS.h"
#include "../STD_TYPES.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Include Needed Functions*/
    /*Options for each:- DO_INCLUDE , DO_NOT_INCLUDE*/
#define MATH_INCLUDE_invsqrt		DO_INCLUDE
#define MATH_INCLUDE_sin			DO_INCLUDE
#define MATH_INCLUDE_atan			DO_INCLUDE			/*also includes invsqrt(void), sqrt(void), sin(void), cos(void)*/
#define MATH_INCLUDE_atan2 			DO_NOT_INCLUDE		/*also includes invsqrt(void), sqrt(void), sin(void), cos(void)*/
/*__________________________________________________________________________________________________________________________________________*/


/*Enable Extra Accuracy Features at the expense of consuming more memory*/
    /*Options for each:- DO_INCLUDE , DO_NOT_INCLUDE*/
#define MATH_IMPROVE_invsqrt		DO_INCLUDE		/* Improves the accuracy of inverse square root function -- also affects sqrt(void), atan(void), atan2(void)*/
#define MATH_IMPROVE_sin			DO_INCLUDE		/* Improves the accuracy of sin function -- also affects cos(void), tan(void), atan(void), atan2(void)*/
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MATH_CONFIG_H*/
