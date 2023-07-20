/**********************************************************************
 * Title		: TB6600 Stepper Motor Driver Interface Header File
 * Layer		:
 * Author		:
 * Last Update	: Dec 12, 2022
 **********************************************************************/


#ifndef TB6600_INTERFACE_H
#define TB6600_INTERFACE_H


/*Include Needed Files*/
#include "TB6600_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*Available Motors*/
#define TB_MOTOR0       (0u)
#define TB_MOTOR1       (1u)
#define TB_MOTOR2       (2u)
#define TB_MOTOR3       (3u)
/*__________________________________________________________________________________________________________________________________________*/


/*Motor Pulse Pins*/
    /*Motor 0 Pulse Pin*/
#define TB0_PUL_PIN		DIO_PIN6
#define TB0_PUL_PORT	DIO_PORTB

    /*Motor 1 Pulse Pin*/
#define TB1_PUL_PIN		DIO_PIN4
#define TB1_PUL_PORT	DIO_PORTH

    /*Motor 2 Pulse Pin*/
#define TB2_PUL_PIN		DIO_PIN4
#define TB2_PUL_PORT	DIO_PORTL

    /*Motor 3 Pulse Pin*/
#define TB3_PUL_PIN		DIO_PIN4
#define TB3_PUL_PORT	DIO_PORTE



/*Motor Directions*/
#define TB_DIR_CW		DIO_PIN_LOW
#define TB_DIR_CCW		DIO_PIN_HIGH


/*Public Functions Declarations*/
/* 
 * Function	: TB6600_Init			: Initializes the TB6600
 * Input1 	: incpy_u8MotorNumber	: Motor number		: TB_MOTOR0 - TB_MOTOR3
 * Return 	: ErrorStatus	    	: Error Status of function
 */
ErrorStatus TB6600_Init(u8 incpy_u8MotorNumber);

/* 
 * Function	: TB6600_Engage			: Starts the controlling the motor according to the given parameters
 * Input1 	: incpy_u8MotorNumber	: Motor number						: TB_MOTOR0 - TB_MOTOR3
 * Input2 	: incpy_u8Dir			: Motor direction					: TB_DIR_CW, TB_DIR_CCW
 * Input3 	: incpy_u8Speed			: Motor speed in pulses per second  : 0 to hold the motor in its position
 * Input4 	: inptr_vdCallback		: Pointer to the callback function  : Pointer to function
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus TB6600_Engage(u8 incpy_u8MotorNumber, u8 incpy_u8Dir, u8 incpy_u8Speed, void (*inptr_vdCallback) (void));

/* 
 * Function	: TB6600_Disengage		: Allows the motor to move freely
 * Input1 	: incpy_u8MotorNumber	: Motor number		: TB_MOTOR0 - TB_MOTOR3
 * Return 	: ErrorStatus	    	: Error Status of function
 */
ErrorStatus TB6600_Disengage(u8 incpy_u8MotorNumber);

#endif /*TB6600_INTERFACE_H*/
