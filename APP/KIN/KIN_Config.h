/**********************************************************************
 * Title		: Kinematics Configuration Header File
 * Layer		: APP
 * Author		: Ashraf Ehab, Ali Azmy, Mostafa Rashad
 * Last Update	: Apr 06, 2023
 **********************************************************************/


#ifndef KIN_CONFIG_H
#define KIN_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/MATH/MATH_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Definitions*/
    /*Robot Dimensions*/
#define DIM_SB		(360.0F)
#define DIM_SP		(240.0F)

#define DIM_L		(200.0F)
#define DIM_l		(400.0F)

    /*Robot Limits*/
#define PLATFORM_ORIGIN_MAX_XY  (130.0F)        /*the max radius of the cylinder that the origin of the platform is allowed to move in (mm)*/
#define PLATFORM_ORIGIN_MAX_Z   (-310.0F)       /*the max z level of the cylinder that the origin of the platform is allowed to move in (mm)*/
#define PLATFORM_ORIGIN_MIN_Z   (-440.0F)       /*the min z level of the cylinder that the origin of the platform is allowed to move in (mm)*/
/*__________________________________________________________________________________________________________________________________________*/


#endif /*KIN_CONFIG_H*/
