/**********************************************************************
 * Title		: Math Program File
 * Layer		: Libraries
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Dec 8, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "MATH_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Definitions*/
/*
 * Function	: MATH_sinHelper		: Calculates the error sin function to increase the accuracy of the sin function
 * Input1 	: incpy_f32ThetaError	: Theta of the error function	: -maximum of f32 to + maximum of f32
 * Return 	: ErrorStatus			: the sine of the input angle	: -1 to 1
 */
#if (DO_INCLUDE == MATH_INCLUDE_sin || DO_INCLUDE == MATH_INCLUDE_atan || DO_INCLUDE == MATH_INCLUDE_atan2) && (DO_INCLUDE == MATH_IMPROVE_sin)
	static f32 MATH_sinHelper(f32 incpy_f32ThetaError)
	{
		s8 Loc_s8SignCorrector = 1;
		/*Correct the range of the input to be between -pi and pi radians*/
		while(-MATH_PI > incpy_f32ThetaError)
		{
			incpy_f32ThetaError += MATH_2PI;
		}
		while(MATH_PI < incpy_f32ThetaError)
		{
			incpy_f32ThetaError -= MATH_2PI;
		}
		/*Turn Theta into a positive value while still saving the sign*/
		if(0 > incpy_f32ThetaError)
		{
			incpy_f32ThetaError *= (-1);
			Loc_s8SignCorrector = -1;
		}
		return Loc_s8SignCorrector * MATH_4_PI2 * incpy_f32ThetaError * (MATH_PI - incpy_f32ThetaError);	/*First approximation of sin*/
	}
#endif	/* MATH_IMPROVE_sin */
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: MATH_sin			: Calculates the sine of an Angle in radians
 * Input1 	: incpy_f32Theta	: Input angle in radians		: -maximum of f32 to + maximum of f32
 * Return 	: ErrorStatus		: the sine of the input angle	: -1 to 1
 */
#if DO_INCLUDE == MATH_INCLUDE_sin || DO_INCLUDE == MATH_INCLUDE_atan || DO_INCLUDE == MATH_INCLUDE_atan2
	f32 MATH_sin(f32 incpy_f32Theta)
	{
		f32 Loc_f32SinApprox = 0;
		s8 Loc_s8SignCorrector = 1;
		#if DO_INCLUDE == MATH_IMPROVE_sin
			f32 Loc_f32ThetaError = 0;
		#endif	/* MATH_IMPROVE_sin */
		/*Correct the range of the input to be between -pi and pi radians where the approximation works*/
		while(-MATH_PI > incpy_f32Theta)
		{
			incpy_f32Theta += MATH_2PI;
		}
		while(MATH_PI < incpy_f32Theta)
		{
			incpy_f32Theta -= MATH_2PI;
		}
		/*Turn Theta into a positive value while still saving the sign*/
		if(0 > incpy_f32Theta)
		{
			incpy_f32Theta *= (-1);
			Loc_s8SignCorrector = -1;
		}
		Loc_f32SinApprox = MATH_4_PI2 * incpy_f32Theta * (MATH_PI - incpy_f32Theta);	/*First approximation of sin*/
	#if DO_INCLUDE == MATH_IMPROVE_sin
		Loc_f32ThetaError = 2.546479F * (incpy_f32Theta - MATH_PI_2) * (incpy_f32Theta - MATH_PI_2);
		return (Loc_s8SignCorrector) * (Loc_f32SinApprox * (0.776F + 0.224F * Loc_f32SinApprox) - 0.001 * MATH_sinHelper(Loc_f32ThetaError));	/*Second approximation of sin with error function removed*/
	#else
		return (Loc_s8SignCorrector) * Loc_f32SinApprox*(0.776F+0.224F*Loc_f32SinApprox);	/*Second approximation of sin*/
	#endif	/* MATH_IMPROVE_sin */
	}
#endif	/* MATH_INCLUDE_sin */

/*
 * Function	: MATH_invsqrt	: Calculates the inverse square root of a positive number based on the Fast Inverse Square Root algorithm
 * Input1 	: incpy_f32Num	: Input number								: 0 to + maximum of f32 except (negative values have to be checked by the user)
 * Return 	: ErrorStatus	: the inverse of the square root of the number
 */
#if DO_INCLUDE == MATH_INCLUDE_invsqrt || DO_INCLUDE == MATH_INCLUDE_atan || DO_INCLUDE == MATH_INCLUDE_atan2
	f32 MATH_invsqrt(f32 incpy_f32Num)
	{
		f32 Loc_f32FloatNum = incpy_f32Num;
		u32 Loc_f32IntNum = 0;
		memcpy(&Loc_f32IntNum, &Loc_f32FloatNum, sizeof(Loc_f32FloatNum));	/*Turn the floating variable into an integer of the same bits*/
		Loc_f32IntNum = MATH_FIS_MAGICNUM - (Loc_f32IntNum >> 1);			/*Perform fast inverse square root*/
		memcpy(&Loc_f32FloatNum, &Loc_f32IntNum, sizeof(Loc_f32FloatNum));	/*Turn the integer variable into a float of the same bits*/
		Loc_f32FloatNum = Loc_f32FloatNum * (1.5F - (incpy_f32Num * 0.5F * Loc_f32FloatNum * Loc_f32FloatNum));	/* First Newton Raphson Iteration for better accuracy */
		#if DO_INCLUDE == MATH_IMPROVE_invsqrt
			Loc_f32FloatNum = Loc_f32FloatNum * (1.5F - (incpy_f32Num * 0.5F * Loc_f32FloatNum * Loc_f32FloatNum));	/* second Newton Raphson Iteration for better accuracy */
		#endif	/* MATH_IMPROVE_invsqrt */
		return Loc_f32FloatNum;
	}
#endif	/* MATH_INCLUDE_invsqrt */

/*
 * Function	: MATH_atan 	: Calculates the inverse tangent of a positive number with a -pi/2 to pi/2 range
 * Input1 	: incpy_f32Num	: Input Number
 * Return 	: ErrorStatus	: the inverse tangent of the Number
 */
#if DO_INCLUDE == MATH_INCLUDE_atan
	f32 MATH_atan(f32 incpy_f32Num)
	{
		f32 Loc_f32Theta = 0;
		f32 Loc_f32n = MATH_invsqrt(1 + incpy_f32Num * incpy_f32Num);	/*Get normalization constant*/
		incpy_f32Num *= Loc_f32n;		/*Normalization of input*/
		Loc_f32Theta = (MATH_PI_2 - ((0.666667F) * Loc_f32n)) * incpy_f32Num;	/*First approximation of atan*/
		return Loc_f32Theta - Loc_f32n * MATH_sin(Loc_f32Theta) + incpy_f32Num * MATH_cos(Loc_f32Theta);	/*Second approximation of atan*/
	}
#endif	/* MATH_INCLUDE_atan */

/*
 * Function	: MATH_atan2 	: Calculates the inverse tan of a positive number with a -pi to pi range
 * Input1 	: incpy_f32Y	: Numerator of Input Number
 * Input2	: incpy_f32X	: Denominator of Input Number
 * Return 	: ErrorStatus	: the inverse tan of the Number
 */
#if DO_INCLUDE == MATH_INCLUDE_atan2
	f32 MATH_atan2(f32 incpy_f32Y, f32 incpy_f32X)
	{
		f32 Loc_f32Theta = 0;
		f32 Loc_f32n = MATH_invsqrt(incpy_f32X * incpy_f32X + incpy_f32Y * incpy_f32Y);		/*Get normalization constant*/
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
