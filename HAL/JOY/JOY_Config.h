/**********************************************************************
 * Title		: Joystick Configuration Header File
 * Layer		: HAL
 * Author		: Ali Azmy, Mostafa Rashad
 * Last Update	: Apr 06, 2023
 **********************************************************************/


#ifndef JOY_CONFIG_H
#define JOY_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Choosing Joystick Channels*/
#define JOY0_X      ADC_CHANNEL4
#define JOY0_Y      ADC_CHANNEL3

#define JOY1_X      ADC_CHANNEL6
#define JOY1_Y      ADC_CHANNEL5

#define JOY2_X      ADC_NOT_A_CHANNEL
#define JOY2_Y      ADC_NOT_A_CHANNEL

#define JOY3_X      ADC_NOT_A_CHANNEL
#define JOY3_Y      ADC_NOT_A_CHANNEL

#define JOY4_X      ADC_NOT_A_CHANNEL
#define JOY4_Y      ADC_NOT_A_CHANNEL

#define JOY5_X      ADC_NOT_A_CHANNEL
#define JOY5_Y      ADC_NOT_A_CHANNEL

#define JOY6_X      ADC_NOT_A_CHANNEL
#define JOY6_Y      ADC_NOT_A_CHANNEL

#define JOY7_X      ADC_NOT_A_CHANNEL
#define JOY7_Y      ADC_NOT_A_CHANNEL
/*__________________________________________________________________________________________________________________________________________*/


#endif /*JOY_CONFIG_H*/
