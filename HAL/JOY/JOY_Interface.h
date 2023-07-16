/**********************************************************************
 * Title		: Joystick Interface Header File
 * Layer		: HAL
 * Author		: Ali Azmy, Mostafa Rashad
 * Last Update	: Apr 06, 2023
 **********************************************************************/


#ifndef JOY_INTERFACE_H
#define JOY_INTERFACE_H


/*Include Needed Files*/
#include "JOY_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*New Variable Types Definitions*/
typedef struct 
{
     s8 XPercent;     /*Joystick Position on X axis in Signed Percentage of Maximum Travel*/
     s8 YPercent;     /*Joystick Position on Y axis in Signed Percentage of Maximum Travel*/
}JOY_Status;
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
     /*Available Joysticks*/
#define JOYSTICK0       (0u)
#define JOYSTICK1       (1u)
#define JOYSTICK2       (2u)
#define JOYSTICK3       (3u)
#define JOYSTICK4       (4u)
#define JOYSTICK5       (5u)
#define JOYSTICK6       (6u)
#define JOYSTICK7       (7u)
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: JOY_Init		    : Initializes the Joystick
 * Input1 	: incpy_u8JoyNumber	    : Joystick number	: JOYSTICK0 - JOYSTICK7
 * Return 	: 				    : Error Status of function
 */
ErrorStatus JOY_Init(u8 incpy_u8JoyNumber);

/*
 * Function	: JOY_Read                    : Reads Joy Stick values
 * Input1 	: incpy_u8JoyNumber           : Joystick number               : JOYSTICK0 - JOYSTICK7
 * Output1	: outptr_JOY_StatusReturn     : Joystick Status (XPercent, YPercent)
 * Return 	: 						: Error Status of function
 */
ErrorStatus JOY_Read(u8 incpy_u8JoyNumber, JOY_Status* outptr_JOY_StatusReturn);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*JOY_INTERFACE_H*/
