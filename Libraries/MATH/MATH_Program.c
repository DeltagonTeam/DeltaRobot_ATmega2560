/**********************************************************************
 * Title		: Math version 2 Program File
 * Layer		: Libraries
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Dec 8, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "MATH_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: MATH_sin		: Calculates the sine of an Angle in radians
 * Input1 	: incpy_f32Theta	: Input angle in radians		: -ve maximum of f32 to +ve maximum of f32
 * Return 	: 					: the sine of the input angle	: -1 to 1
 */
#if DO_INCLUDE == MATH_INCLUDE_sin || DO_INCLUDE == MATH_INCLUDE_atan || DO_INCLUDE == MATH_INCLUDE_atan2
	f32 MATH_sin(f32 incpy_f32Theta)
	{
		f32 Loc_f32ThetaCorrectedPow3 = 0;

		/*Getting Theta Between -Pi and Pi*/
		while(-MATH_PI > incpy_f32Theta)
		{
			incpy_f32Theta += MATH_2PI;
		}
		while(MATH_PI < incpy_f32Theta)
		{
			incpy_f32Theta -= MATH_2PI;
		}

		/*Getting Theta Between -Pi/2 and Pi/2*/
		if(MATH_PI_2 < incpy_f32Theta)
		{
			incpy_f32Theta -= 2*(incpy_f32Theta - MATH_PI_2);
		}
		if(-MATH_PI_2 > incpy_f32Theta)
		{
			incpy_f32Theta += 2*(incpy_f32Theta + MATH_PI_2);
		}

		/*Calculating Sin*/
		#warning add the coff as defines
		Loc_f32ThetaCorrectedPow3 = incpy_f32Theta*incpy_f32Theta*incpy_f32Theta;
		return 0.007506F*Loc_f32ThetaCorrectedPow3*incpy_f32Theta*incpy_f32Theta - 0.16566F*Loc_f32ThetaCorrectedPow3 + 0.9997F*incpy_f32Theta;
	}
#endif	/* MATH_INCLUDE_sin */

/*
 * Function	: MATH_atan 	: Calculates the inverse tangent of a positive number with a -pi/2 to pi/2 range
 * Input1 	: incpy_f32Num	: Input Number
 * Return 	: 				: the inverse tangent of the Number
 */
#if DO_INCLUDE == MATH_INCLUDE_atan
	f32 MATH_atan(f32 incpy_f32Num)
	{
		f32 Loc_f32Theta = 0;
		f32 Loc_f32n = 1/sqrtf(1 + incpy_f32Num * incpy_f32Num);	/*Get normalization constant*/
		incpy_f32Num *= Loc_f32n;									/*Normalization of input*/
		Loc_f32Theta = (MATH_PI_2 - ((0.666667F) * Loc_f32n)) * incpy_f32Num;								/*First approximation of atan*/
		return Loc_f32Theta - Loc_f32n * MATH_sin(Loc_f32Theta) + incpy_f32Num * MATH_cos(Loc_f32Theta);	/*Second approximation of atan*/
	}
#endif	/* MATH_INCLUDE_atan */

/*
 * Function	: MATH_atan2 	: Calculates the inverse tan of a positive number with a -pi to pi range
 * Input1 	: incpy_f32Y	: Numerator of Input Number
 * Input2	: incpy_f32X	: Denominator of Input Number
 * Return 	: 				: the inverse tan of the Number
 */
#if DO_INCLUDE == MATH_INCLUDE_atan2
	f32 MATH_atan2(f32 incpy_f32Y, f32 incpy_f32X)
	{
		f32 Loc_f32Theta = 0;
		f32 Loc_f32n = 1/sqrtf(incpy_f32X * incpy_f32X + incpy_f32Y * incpy_f32Y);		/*Get normalization constant*/
		/*Normalization of inputs*/
		incpy_f32Y *= Loc_f32n;
		incpy_f32X *= Loc_f32n;
		/*First approximation of atan2*/
		if (0 <= incpy_f32X)
		{
			Loc_f32Theta = (MATH_PI_2 - ((0.666667F) * incpy_f32X)) * incpy_f32Y;
		}
		else if (0 <= incpy_f32Y)
		{
			Loc_f32Theta = MATH_PI - ((MATH_PI_2 + ((0.666667F) * incpy_f32X)) * incpy_f32Y);
		}
		else
		{
			Loc_f32Theta = -MATH_PI - ((MATH_PI_2 + ((0.666667F) * incpy_f32X)) * incpy_f32Y);
		}
		return Loc_f32Theta - incpy_f32X * MATH_sin(Loc_f32Theta) + incpy_f32Y * MATH_cos(Loc_f32Theta);	/*Second approximation of atan2*/
	}
#endif	/* MATH_INCLUDE_atan2 */
