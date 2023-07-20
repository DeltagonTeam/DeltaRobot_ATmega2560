/**********************************************************************
 * Title		: Math version 2 Interface Header File
 * Layer		: Libraries
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Dec 8, 2022
 **********************************************************************/


#ifndef MATH_INTERFACE_H
#define MATH_INTERFACE_H


/*Include Needed Files*/
#include "MATH_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
#define MATH_PI       (3.141593F)     /* Pi */
#define MATH_PI_2		(1.570796F)     /* Pi/2 */
#define MATH_2PI      (6.283185F)     /* 2*Pi */
#define MATH_SQRT2	(1.414214F)     /* sqrt(2) */
#define MATH_SQRT3	(1.732051F)     /* sqrt(3) */
#define MATH_1_SQRT2	(0.7071068F)    /* Pi/sqrt(2) */
#define MATH_PI_SQRT2	(2.221441F)     /* Pi/sqrt(2) */
#define MATH_4_PI2	(0.4052847F)	/* 4/(Pi^2) */
/*__________________________________________________________________________________________________________________________________________*/


/*Public Macros*/
/*
 * Function	: MATH_cos	: Calculates the cosine of an Angle in radians
 * Input1 	: X			    : Input angle in radians		: - ve maximum of f32 to +ve maximum of f32
 * Return 	: 			    : the cosine of the input angle	: -1 to 1
 */
#define MATH_cos(X)		(MATH_sin(MATH_PI_2 - (X)))

/*
 * Function	: MATH_tan	: Calculates the tangent of an Angle in radians
 * Input1 	: X			    : Input angle in radians			: - ve maximum of f32 to +ve maximum of f32 except 0 (has to be checked by the user)
 * Return 	: 			    : the tangent of the input angle	: -1 to 1
 */
#define MATH_tan(X)		(MATH_sin(X) / MATH_cos(X))
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: MATH_sin		: Calculates the sine of an Angle in radians
 * Input1 	: incpy_f32Theta	: Input angle in radians		: - ve maximum of f32 to +ve maximum of f32
 * Return 	: 					: the sine of the input angle	: -1 to 1
 */
f32 MATH_sin(f32 incpy_f32Theta);

/*
 * Function	: MATH_atan 	: Calculates the inverse tangent of a positive number with a -pi/2 to pi/2 range
 * Input1 	: incpy_f32Num	: Input Number
 * Return 	: 				: the inverse tangent of the Number
 */
f32 MATH_atan(f32 incpy_f32Num);

/*
 * Function	: MATH_atan2 	: Calculates the inverse tangent of a positive number with a -pi to pi range
 * Input1 	: incpy_f32Y	: Numerator of Input Number
 * Input2	: incpy_f32X	: Denominator of Input Number
 * Return 	: 				: the inverse tangent of the Number
 */
f32 MATH_atan2(f32 incpy_f32X, f32 incpy_f32Y);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MATH_INTERFACE_H*/
