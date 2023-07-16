/**********************************************************************
 * Title		: FEEDBACK Configuration Header File
 * Layer		:
 * Author		:
 * Last Update	: Dec 8, 2022
 **********************************************************************/


#ifndef FEEDBACK_CONFIG_H
#define FEEDBACK_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/MATH/MATH_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../HAL/POT/POT_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Choosing Feedback Potentiometers*/
#define FEEDBACK_CHANNEL0   POT0
#define FEEDBACK_CHANNEL1   POT1
#define FEEDBACK_CHANNEL2   POT2
/*__________________________________________________________________________________________________________________________________________*/


/*Choosing the Calibration Angles*/
#define INIT_ANGLE0 	0.3738495F      /*the angle that potentiometer 0 is calibrated at in radians*/
#define INIT_ANGLE1 	0.3738495F      /*the angle that potentiometer 1 is calibrated at in radians*/
#define INIT_ANGLE2 	0.3738495F      /*the angle that potentiometer 2 is calibrated at in radians*/
/*__________________________________________________________________________________________________________________________________________*/


#endif /*FEEDBACK_CONFIG_H*/
