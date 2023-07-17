/**********************************************************************
 * Title		: Kinematics Interface Header File
 * Layer		: APP
 * Author		: Ashraf Ehab, Ali Azmy, Mostafa Rashad
 * Last Update	: Apr 06, 2023
 **********************************************************************/


#ifndef KIN_INTERFACE_H
#define KIN_INTERFACE_H


/*Include Needed Files*/
#include "KIN_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declaration*/
/*
 * Function	: KIN_Init          : a public function that calculates constants for the Kinematics
 * Return 	: ErrorStatus	    : Error Status of function
 */
ErrorStatus KIN_Init(void);

/*
 * Function	: KIN_GetCoords		: a public function that calculates the coordinates of origin of the platform
 * Input1	: inptr_f32Thetas	: an array with the anglular positions of the driver links [Th1,Th2,Th3]
 * Output1 	: outptr_f32Coords	: an array with the coordinates of origin of the platform [x,y,z]
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus KIN_GetCoords(const f32* inptr_f32Thetas, f32* outptr_f32Coords);

/*
 * Function	: KIN_GetThetas		: a public function that calculates the anglur positions of the driver links
 * Input1 	: inptr_f32Coords	: an array with the coordinates of origin of the platform [x,y,z]
 * Output1	: outptr_f32Thetas	: an array with the anglular positions of the driver links [Th1,Th2,Th3]
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus KIN_GetThetas(const f32* inptr_f32Coords, f32* outptr_f32Thetas);

/*
 * Function	: KIN_GetThetaDots			: a public function that calculates the anglur velosities of the driver links
 * Input1   : inptr_f32Coords 			: an array with the coordinates of origin of the platform [x,y,z]
 * Input2   : inptr_f32Velocities       : an array with the velocity components of the origin of the platform [xd,yd,zd]
 * Input3   : inptr_f32Thetas           : an array with the anglular positions of the driver links [Th1,Th2,Th3]
 * Output1	: outptr_f32ThetaDots 	    : an array with the anglular velocities of the driver links [Thd1,Thd2,Thd3]
 * Return 	: ErrorStatus				: Error Status of function
 */
ErrorStatus KIN_GetThetaDots(const f32* inptr_f32Coords, const f32* inptr_f32Velocities, const f32* inptr_f32Thetas, f32* outptr_f32ThetaDots);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*KIN_INTERFACE_H*/
