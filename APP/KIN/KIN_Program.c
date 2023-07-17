/**********************************************************************
 * Title		: Kinematics Program File
 * Layer		: APP
 * Author		: Ashraf Ehab, Ali Azmy, Mostafa Rashad
 * Last Update	: Apr 06, 2023
 **********************************************************************/


/*Include Needed Files*/
#include "KIN_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Definitions*/
/*
 * Function	: KIN_CalcTheta		: a private function that calculates the anglur position of any driver link
 * Input1 	: incpy_f32E		: precalculated expression that is different for each driver link
 * Input2 	: incpy_f32F		: precalculated expression that is different for each driver link
 * Input3 	: incpy_f32G		: precalculated expression that is different for each driver link
 * Output1	: outptr_f32Theta	: Value inserted on the Port x	: 0-255
 * Return 	:					: Error Status of function
 */
static ErrorStatus KIN_CalcTheta(f32 incpy_f32E, f32 incpy_f32F, f32 incpy_f32G, f32* outptr_f32Theta)
{
	/*Defining Variables*/
	f32 Loc_f32Under_Sqrt = 0;
	f32 Loc_f32Tangent_a = 0;
	f32 Loc_f32Tangent_b = 0;

    /*Checking whether a Real Solution Exists*/
    Loc_f32Under_Sqrt = incpy_f32E*incpy_f32E + incpy_f32F*incpy_f32F - incpy_f32G*incpy_f32G;
    if (0 > Loc_f32Under_Sqrt)
	{
		return POSITION_OUT_OF_RANGE;
	}
    
    /*Choosing the Solution to be Returned*/
    Loc_f32Tangent_a = (-incpy_f32F + MATH_sqrt(Loc_f32Under_Sqrt)) / (incpy_f32G - incpy_f32E);
    Loc_f32Tangent_b = (-incpy_f32F - MATH_sqrt(Loc_f32Under_Sqrt)) / (incpy_f32G - incpy_f32E);

    if (MATH_abs(Loc_f32Tangent_a) < MATH_abs(Loc_f32Tangent_b))
	{
        *outptr_f32Theta = 2*MATH_atan(Loc_f32Tangent_a);
	}
    else
	{
        *outptr_f32Theta = 2*MATH_atan(Loc_f32Tangent_b);
	}     

    /*Returning*/
    return NO_ERROR;
}

/*
 * Function	    : KIN_Trilaterate   : a private function that calculates an intersection point of three spheres
 * Input1       : inptr_f32A1       : an array with the coordinates of the center of sphere 1
 * Input2       : inptr_f32A2       : an array with the coordinates of the center of sphere 2
 * Input3       : inptr_f32A3       : an array with the coordinates of the center of sphere 3
 * Input4       : inptr_f32Radii    : an array with the radii of the three spheres
 * Output1	    : outptr_f32Coords  : an array with the coordinates of the choosen point of intersection
 * Return       :                   : Error Status of function
 */
static ErrorStatus KIN_Trilaterate(const f32* inptr_f32A1, const f32* inptr_f32A2, const f32* inptr_f32A3, const f32* inptr_f32Radii, f32* outptr_f32Coords)
{
    /*Unpacking Inputs*/
    f32 Loc_f32X1 = inptr_f32A1[0];
    f32 Loc_f32Y1 = inptr_f32A1[1];
    f32 Loc_f32Z1 = inptr_f32A1[2];

    f32 Loc_f32X2 = inptr_f32A2[0];
    f32 Loc_f32Y2 = inptr_f32A2[1];
    f32 Loc_f32Z2 = inptr_f32A2[2];

    f32 Loc_f32X3 = inptr_f32A3[0];
    f32 Loc_f32Y3 = inptr_f32A3[1];
    f32 Loc_f32Z3 = inptr_f32A3[2];

    f32 Loc_f32r1 = inptr_f32Radii[0];
    f32 Loc_f32r2 = inptr_f32Radii[1];
    f32 Loc_f32r3 = inptr_f32Radii[2];

    /*Manipulating Equations*/
    f32 Loc_f32a11 = 2 * (Loc_f32X3 - Loc_f32X1);
    f32 Loc_f32a12 = 2 * (Loc_f32Y3 - Loc_f32Y1);
    f32 Loc_f32a13 = 2 * (Loc_f32Z3 - Loc_f32Z1);

    f32 Loc_f32a21 = 2 * (Loc_f32X3 - Loc_f32X2);
    f32 Loc_f32a22 = 2 * (Loc_f32Y3 - Loc_f32Y2);
    f32 Loc_f32a23 = 2 * (Loc_f32Z3 - Loc_f32Z2);

    f32 Loc_f32b1 = Loc_f32r1 * Loc_f32r1 - Loc_f32r3 * Loc_f32r3 - Loc_f32X1 * Loc_f32X1 - Loc_f32Y1 * Loc_f32Y1 - Loc_f32Z1 * Loc_f32Z1 + Loc_f32X3 * Loc_f32X3 + Loc_f32Y3 * Loc_f32Y3 + Loc_f32Z3 * Loc_f32Z3;
    f32 Loc_f32b2 = Loc_f32r2 * Loc_f32r2 - Loc_f32r3 * Loc_f32r3 - Loc_f32X2 * Loc_f32X2 - Loc_f32Y2 * Loc_f32Y2 - Loc_f32Z2 * Loc_f32Z2 + Loc_f32X3 * Loc_f32X3 + Loc_f32Y3 * Loc_f32Y3 + Loc_f32Z3 * Loc_f32Z3;

    f32 Loc_f32a1 = Loc_f32a22 / Loc_f32a21 - Loc_f32a12 / Loc_f32a11;
    f32 Loc_f32a2 = Loc_f32a13 / Loc_f32a11 - Loc_f32a23 / Loc_f32a21;
    f32 Loc_f32a3 = Loc_f32b2 / Loc_f32a21 - Loc_f32b1 / Loc_f32a11;
    f32 Loc_f32a4 = Loc_f32a2 / Loc_f32a1;
    f32 Loc_f32a5 = Loc_f32a3 / Loc_f32a1;
    f32 Loc_f32a6 = (Loc_f32a22 * Loc_f32a4 + Loc_f32a23) / Loc_f32a21;
    f32 Loc_f32a7 = (Loc_f32b2 - Loc_f32a22 * Loc_f32a5) / Loc_f32a21;

    f32 Loc_f32a0 = Loc_f32a6 * Loc_f32a6 + Loc_f32a4 * Loc_f32a4 + 1;
    f32 Loc_f32b0 = 2 * (Loc_f32a6 * (Loc_f32X1 - Loc_f32a7) + Loc_f32a4 * (Loc_f32a5 - Loc_f32Y1) - Loc_f32Z1);
    f32 Loc_f32c0 = Loc_f32a7 * (Loc_f32a7 - 2 * Loc_f32X1) + Loc_f32a5 * (Loc_f32a5 - 2 * Loc_f32Y1) + Loc_f32X1 * Loc_f32X1 + Loc_f32Y1 * Loc_f32Y1 + Loc_f32Z1 * Loc_f32Z1 - Loc_f32r1 * Loc_f32r1;

    f32 Loc_f32UnderRoot = Loc_f32b0 * Loc_f32b0 - 4 * Loc_f32a0 * Loc_f32c0;

    if (0 == Loc_f32UnderRoot)
    {
        return POSITION_OUT_OF_RANGE;
    }

    /*Calculating the Coordinates*/
    f32 Loc_f32z = 0.5 * (-Loc_f32b0 - MATH_sqrt(Loc_f32b0 * Loc_f32b0 - 4 * Loc_f32a0 * Loc_f32c0)) / Loc_f32a0;
    f32 Loc_f32y = Loc_f32a4 * Loc_f32z + Loc_f32a5;
    f32 Loc_f32x = -Loc_f32a6 * Loc_f32z + Loc_f32a7;

    outptr_f32Coords[0] = Loc_f32x;
    outptr_f32Coords[1] = Loc_f32y;
    outptr_f32Coords[2] = Loc_f32z;

    return NO_ERROR;
}
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/*
 * Function	: KIN_Init      : a public function that calculates constants for the Kinematics
 * Return 	:				: Error Status of function
 */
ErrorStatus KIN_Init(void)
{
    if (0 >= DIM_L || 0 >= DIM_l || 0 >= DIM_SB || 0 >= DIM_SP)
    {
        return INVALID_CONFIGS;
    }
   
    Glob_f32wB = DIM_SB*MATH_SQRT3 / 6.0F;
    /*Glob_f32uB = DIM_SB*MATH_SQRT3 / 3.0F; (not used)*/
    Glob_f32wP = DIM_SP*MATH_SQRT3 / 6.0F;
    Glob_f32uP = DIM_SP*MATH_SQRT3 / 3.0F;

    Glob_f32a = Glob_f32wB - Glob_f32uP;
    Glob_f32b = (DIM_SP - (MATH_SQRT3 * Glob_f32wB)) * 0.5F;
    Glob_f32c = Glob_f32wP - (Glob_f32wB * 0.5F);

    Glob_f32d = (Glob_f32a * Glob_f32a) + (DIM_L * DIM_L) - (DIM_l * DIM_l);
    Glob_f32e = (Glob_f32b * Glob_f32b) + (Glob_f32c * Glob_f32c) + (DIM_L * DIM_L) - (DIM_l * DIM_l);
    Glob_f32f = Glob_f32c + (MATH_SQRT3 * Glob_f32b);

    return NO_ERROR;
}

/*
 * Function	: KIN_GetCoords		: a public function that calculates the coordinates of origin of the platform
 * Input1	: inptr_f32Thetas	: an array with the anglular positions of the driver links [Th1,Th2,Th3]
 * Output1 	: outptr_f32Coords	: an array with the coordinates of origin of the platform [x,y,z]
 * Return 	:					: Error Status of function
 */
ErrorStatus KIN_GetCoords(const f32* inptr_f32Thetas, f32* outptr_f32Coords)
{
    /*Unpacking Inputs*/
    f32 Loc_f32Th1 = inptr_f32Thetas[0];
    f32 Loc_f32Th2 = inptr_f32Thetas[1];
    f32 Loc_f32Th3 = inptr_f32Thetas[2];

    /*Calculating the Center of Sphere 1 (Point A1)*/
    f32 Loc_f32X1 = 0;
    f32 Loc_f32Y1 = -Glob_f32wB - DIM_L * MATH_cos(Loc_f32Th1) + Glob_f32uP;
    f32 Loc_f32Z1 = -DIM_L * MATH_sin(Loc_f32Th1);

    /*Calculating the Center of Sphere 2 (Point A2)*/
    f32 Loc_f32X2 = 0.5 * (MATH_SQRT3 * (Glob_f32wB + DIM_L * MATH_cos(Loc_f32Th2)) - DIM_SP);
    f32 Loc_f32Y2 = 0.5 * (Glob_f32wB + DIM_L * MATH_cos(Loc_f32Th2)) - Glob_f32wP;
    f32 Loc_f32Z2 = -DIM_L * MATH_sin(Loc_f32Th2);

    /*Calculating the Center of Sphere 3 (Point A3)*/
    f32 Loc_f32X3 = -0.5 * (MATH_SQRT3 * (Glob_f32wB + DIM_L * MATH_cos(Loc_f32Th3)) - DIM_SP);
    f32 Loc_f32Y3 = 0.5 * (Glob_f32wB + DIM_L * MATH_cos(Loc_f32Th3)) - Glob_f32wP;
    f32 Loc_f32Z3 = -DIM_L * MATH_sin(Loc_f32Th3);

    /*Getting the End Effector Coordinates*/
    f32 Loc_f32A1[3] = {Loc_f32X1, Loc_f32Y1, Loc_f32Z1};
    f32 Loc_f32A2[3] = {Loc_f32X2, Loc_f32Y2, Loc_f32Z2};
    f32 Loc_f32A3[3] = {Loc_f32X3, Loc_f32Y3, Loc_f32Z3};

    f32 Loc_f32Radii[3] = {DIM_l, DIM_l, DIM_l};
    return KIN_Trilaterate(Loc_f32A1, Loc_f32A2, Loc_f32A3, Loc_f32Radii, outptr_f32Coords);
}

/*
 * Function	: KIN_GetThetas		: a public function that calculates the anglur positions of the driver links
 * Input1 	: inptr_f32Coords	: an array with the coordinates of origin of the platform [x,y,z]
 * Output1	: outptr_f32Thetas	: an array with the anglular positions of the driver links [Th1,Th2,Th3]
 * Return 	:					: Error Status of function
 */
ErrorStatus KIN_GetThetas(const f32* inptr_f32Coords, f32* outptr_f32Thetas)
{
    /*Unpacking Inputs*/
	f32 Loc_f32x = inptr_f32Coords[0];
	f32 Loc_f32y = inptr_f32Coords[1];
    f32 Loc_f32z = inptr_f32Coords[2];

	/*Defining Variables*/
	f32 Loc_f32E = 0;
	f32 Loc_f32F = 0;
	f32 Loc_f32G = 0;
	f32 Loc_f32PosMagSqrd = (Loc_f32x*Loc_f32x) + (Loc_f32y*Loc_f32y) + (Loc_f32z*Loc_f32z);

    /*Calculating Expression used for the Three Motor Angles*/
    Loc_f32F  = 2.0F*Loc_f32z*DIM_L;

    /*Getting theta 1*/
    Loc_f32E = 2.0F*DIM_L*(Loc_f32y + Glob_f32a);
    Loc_f32G = Loc_f32PosMagSqrd + 2.0F*Loc_f32y*Glob_f32a + Glob_f32d;
    ErrorStatus error1 = KIN_CalcTheta(Loc_f32E, Loc_f32F, Loc_f32G, &outptr_f32Thetas[0]);

    /*Getting theta 2*/
    Loc_f32E = -DIM_L*(MATH_SQRT3*Loc_f32x + Loc_f32y + Glob_f32f);
    Loc_f32G = Loc_f32PosMagSqrd + 2.0F*(Loc_f32x*Glob_f32b + Loc_f32y*Glob_f32c) + Glob_f32e;
    ErrorStatus error2 = KIN_CalcTheta(Loc_f32E, Loc_f32F, Loc_f32G, &outptr_f32Thetas[1]);

    /*Getting theta 3*/
    Loc_f32E = DIM_L*(MATH_SQRT3*Loc_f32x-Loc_f32y - Glob_f32f);
    Loc_f32G = Loc_f32PosMagSqrd + 2.0F*(-Loc_f32x*Glob_f32b + Loc_f32y*Glob_f32c) + Glob_f32e;
    ErrorStatus error3 = KIN_CalcTheta(Loc_f32E, Loc_f32F, Loc_f32G, &outptr_f32Thetas[2]);

    /*Checking whether there is an Error with Any of the Angles*/
    if (error1 || error2 || error3)
	{
		return POSITION_OUT_OF_RANGE;
	}
    
    /*Returning*/
    return NO_ERROR;
}

/*
 * Function	: KIN_GetThetaDots			: a public function that calculates the anglur velosities of the driver links
 * Input1   : inptr_f32Coords 			: an array with the coordinates of origin of the platform [x,y,z]
 * Input2   : inptr_f32Velocities       : an array with the velocity components of the origin of the platform [xd,yd,zd]
 * Input3   : inptr_f32Thetas           : an array with the anglular positions of the driver links [Th1,Th2,Th3]
 * Output1	: outptr_f32ThetaDots 	    : an array with the anglular velocities of the driver links [Thd1,Thd2,Thd3]
 * Return 	:							: Error Status of function
 */
ErrorStatus KIN_GetThetaDots(const f32* inptr_f32Coords, const f32* inptr_f32Velocities, const f32* inptr_f32Thetas, f32* outptr_f32ThetaDots)
{
    /*Unpacking Inputs*/
   	f32 Loc_f32x = inptr_f32Coords[0];
	f32 Loc_f32y = inptr_f32Coords[1];
    f32 Loc_f32z = inptr_f32Coords[2];

   	f32 Loc_f32xd = inptr_f32Velocities[0];
	f32 Loc_f32yd = inptr_f32Velocities[1];
    f32 Loc_f32zd = inptr_f32Velocities[2];
  
  	f32 Loc_f32Th1 = inptr_f32Thetas[0];
	f32 Loc_f32Th2 = inptr_f32Thetas[1];
    f32 Loc_f32Th3 = inptr_f32Thetas[2];

    /*Calculating the Angular Velocities of the Motors*/
    outptr_f32ThetaDots[0] = (DIM_L*(Loc_f32yd*MATH_cos(Loc_f32Th1) + Loc_f32zd*MATH_sin(Loc_f32Th1)) + Loc_f32x*Loc_f32xd + (Loc_f32y+Glob_f32a)*Loc_f32yd + Loc_f32z*Loc_f32zd) / (DIM_L*((Loc_f32y+Glob_f32a)*MATH_sin(Loc_f32Th1) - Loc_f32z*MATH_cos(Loc_f32Th1)));
    outptr_f32ThetaDots[1] = (DIM_L*((MATH_SQRT3*Loc_f32xd+Loc_f32yd)*MATH_cos(Loc_f32Th2) - 2.0F*Loc_f32zd*MATH_sin(Loc_f32Th2)) - 2.0F*((Loc_f32x+Glob_f32b)*Loc_f32xd + (Loc_f32y+Glob_f32c)*Loc_f32yd + Loc_f32z*Loc_f32zd)) / (DIM_L*((MATH_SQRT3*(Loc_f32x+Glob_f32b)+Loc_f32y+Glob_f32c)*MATH_sin(Loc_f32Th2) + 2.0F*Loc_f32z*MATH_cos(Loc_f32Th2)));
    outptr_f32ThetaDots[2] = (DIM_L*((MATH_SQRT3*Loc_f32xd-Loc_f32yd)*MATH_cos(Loc_f32Th3) + 2.0F*Loc_f32zd*MATH_sin(Loc_f32Th3)) + 2.0F*((Loc_f32x-Glob_f32b)*Loc_f32xd + (Loc_f32y+Glob_f32c)*Loc_f32yd + Loc_f32z*Loc_f32zd)) / (DIM_L*((MATH_SQRT3*(Loc_f32x-Glob_f32b)-Loc_f32y-Glob_f32c)*MATH_sin(Loc_f32Th3) - 2.0F*Loc_f32z*MATH_cos(Loc_f32Th3)));
    
    /*Returning*/
    return NO_ERROR;
}

