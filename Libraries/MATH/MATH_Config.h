/**********************************************************************
 * Title		: Math version 2 Configuration Header File
 * Layer		: Libraries
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Dec 8, 2022
 **********************************************************************/


#ifndef MATH_CONFIG_H
#define MATH_CONFIG_H


/*Include Needed Files*/
#include <math.h>
#include "../MACROS.h"
#include "../STD_TYPES.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Include Needed Functions*/
    /*Options for each:- DO_INCLUDE , DO_NOT_INCLUDE*/
#define MATH_INCLUDE_sin			DO_INCLUDE
#define MATH_INCLUDE_atan	        DO_INCLUDE			/*also includes invsqrt(void), sqrt(void), sin(void), cos(void)*/
#define MATH_INCLUDE_atan2 		DO_NOT_INCLUDE		    /*also includes invsqrt(void), sqrt(void), sin(void), cos(void)*/
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MATH_CONFIG_H*/
