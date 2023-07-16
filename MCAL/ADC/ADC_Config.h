/**********************************************************************
 * Title		: ADC Configuration Header File
 * Layer		: MCAL
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Jan 7, 2023
 **********************************************************************/


#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../REGISTERS.h"
#include "../MCU_Config.h"
#include "../Glob_Int.h"
#include "../DIO/DIO_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Choose ADC Preferences*/
#define ADC_SET_PRIORITY	ADC_HIGHACCURACY	/*chooses what to optimize the ADC Pre-scalar for; options:- ADC_HIGHACCURACY,  ADC_HIGHSPEED*/
#define ADC_REF_VOLTAGE		ADC_VREF_EXTERNAL   /*choose adc reference voltage*/
    /*ADC_REF_VOLTAGE Reference voltage Options*/
    /*
     * ADC_VREF_EXTERNAL		:	External Voltage Reference (reference voltage put through  AREF pin)
     * ADC_VREF_VCC				:	AVCC with external capacitor at AREF pin
     * ADC_VREF_INTERNAL1_1V	:	Internal 1.1V Voltage Reference with external capacitor at AREF pin
     * ADC_VREF_INTERNAL2_56V	:	Internal 2.56V Voltage Reference with external capacitor at AREF pin
     */
/*__________________________________________________________________________________________________________________________________________*/


#endif /*ADC_CONFIG_H*/
