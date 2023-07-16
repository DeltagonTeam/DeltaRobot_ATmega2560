/**********************************************************************
 * Title		: Kinematics Private Header File
 * Layer		: APP
 * Author		: Ashraf Ehab, Ali Azmy, Mostafa Rashad
 * Last Update	: Apr 06, 2023
 **********************************************************************/


#ifndef KIN_PRIVATE_H
#define KIN_PRIVATE_H


/*Include Needed Files*/
#include "KIN_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Declaration*/
/*
 * Function	: KIN_CalcTheta		: a private function that calculates the anglur position of any driver link
 * Input1 	: incpy_f32E		: precalculated expression that is different for each driver link
 * Input2 	: incpy_f32F		: precalculated expression that is different for each driver link
 * Input3 	: incpy_f32G		: precalculated expression that is different for each driver link
 * Output1	: outptr_f32Theta	: Value inserted on the Port x	: 0-255
 * Return 	:					: Error Status of function
 */
static ErrorStatus KIN_CalcTheta(f32 incpy_f32E, f32 incpy_f32F, f32 incpy_f32G, f32* outptr_f32Theta);

/*
 * Function	    : KIN_Trilaterate   : a private function that calculates an intersection point of three spheres
 * Input1       : inptr_f32A1       : an array with the coordinates of the center of sphere 1
 * Input2       : inptr_f32A2       : an array with the coordinates of the center of sphere 2
 * Input3       : inptr_f32A3       : an array with the coordinates of the center of sphere 3
 * Input4       : inptr_f32Radii    : an array with the radii of the three spheres
 * Output1	    : outptr_f32Coords  : an array with the coordinates of the choosen point of intersection
 * Return       :                   : Error Status of function
 */
static ErrorStatus KIN_Trilaterate(f32 *inptr_f32A1, f32 *inptr_f32A2, f32 *inptr_f32A3, f32 *inptr_f32Radii, f32 *outptr_f32Coords);
/*__________________________________________________________________________________________________________________________________________*/


/*Private Global Constant Variables*/
static f32 Glob_f32wB = 0;
/*static f32 Glob_f32uB = 0; (not used) */
static f32 Glob_f32wP = 0;
static f32 Glob_f32uP = 0;

static f32 Glob_f32a = 0;
static f32 Glob_f32b = 0;
static f32 Glob_f32c = 0;

static f32 Glob_f32d = 0;
static f32 Glob_f32e = 0;
static f32 Glob_f32f = 0;
/*__________________________________________________________________________________________________________________________________________*/


#endif /*KIN_PRIVATE_H*/
