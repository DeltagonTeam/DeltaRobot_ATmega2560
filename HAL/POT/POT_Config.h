/**********************************************************************
 * Title		: Potentiometer Configuration Header File
 * Layer		: HAL
 * Author		: Ashraf Ehab, Mohamed ElHaddad
 * Last Update	: Oct 31, 2022
 **********************************************************************/


#ifndef POT_CONFIG_H
#define POT_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/MATH/MATH_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Choosing the Potentiometer ADC Channels*/
#define POT0        ADC_CHANNEL0
#define POT1        ADC_CHANNEL1
#define POT2        ADC_CHANNEL2
#define POT3        ADC_NOT_A_CHANNEL
#define POT4        ADC_NOT_A_CHANNEL
#define POT5        ADC_NOT_A_CHANNEL
#define POT6        ADC_NOT_A_CHANNEL
#define POT7        ADC_NOT_A_CHANNEL
#define POT8        ADC_NOT_A_CHANNEL
#define POT9        ADC_NOT_A_CHANNEL
#define POT10       ADC_NOT_A_CHANNEL
#define POT11       ADC_NOT_A_CHANNEL
#define POT12       ADC_NOT_A_CHANNEL
#define POT13       ADC_NOT_A_CHANNEL
#define POT14       ADC_NOT_A_CHANNEL
#define POT15       ADC_NOT_A_CHANNEL
/*__________________________________________________________________________________________________________________________________________*/


/*Range of Potentiometer*/
#define POT_RANGE   (2.820532F)     /*the range of the potentiometer based on the voltage referance in radians*/
/*__________________________________________________________________________________________________________________________________________*/


#endif /*POT_CONFIG_H*/
