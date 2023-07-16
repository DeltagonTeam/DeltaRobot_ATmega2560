/**********************************************************************
 * Title		: ADC Private Header File
 * Layer		: MCAL
 * Author		: Ali Azmy, Ashraf Ehab
 * Last Update	: Jan 7, 2023
 **********************************************************************/


#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


/*Include Needed Files*/
#include "ADC_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Pre-Build Configuration Macros Definitions*/
	/*Priorities*/
#define ADC_HIGHACCURACY		(1u)
#define ADC_HIGHSPEED			(2u)
	/*Reference Voltages*/
#define ADC_VREF_EXTERNAL		(0u)	/* External Voltage Reference (reference voltage put through  AREF pin)*/
#define ADC_VREF_VCC			(1u)	/* VCC with external capacitor at AREF pin*/
#define ADC_VREF_INTERNAL1_1V	(2u)	/* Internal 1.1 V Voltage Reference with external capacitor at AREF pin */
#define ADC_VREF_INTERNAL2_56V	(3u)	/* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
/*__________________________________________________________________________________________________________________________________________*/


/*Pre-Build Configuration Checks*/
	/*Pre-Scalar*/
#if ADC_HIGHACCURACY == ADC_SET_PRIORITY
	/*Pre-Scaler for High Accuracy*/
	#if		(16000u) <  MCU_CLK_FREQUENCY
		#error Maximum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 16000KHz
	#elif	(6400u)  <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(7u)	/*F_CPU/128*/
	#elif	(3200u)  <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(6u)	/*F_CPU/64*/
	#elif	(1600u)  <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(5u)	/*F_CPU/32*/
	#elif	(800u)   <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(4u)	/*F_CPU/16*/
	#elif	(400u)   <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(3u)	/*F_CPU/8*/
	#elif	(200u)   <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(2u)	/*F_CPU/4*/
	#elif	(128u)   <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(1u)	/*F_CPU/2*/
	#else 	/*0u < MCU_CLK_FREQUENCY*/
		#error Minimum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 128KHz
	#endif	/*MCU_CLK_FREQUENCY*/

#elif ADC_HIGHSPEED == ADC_SET_PRIORITY
	/*Pre-Scaler for High Speed*/
	#if		(16000u) <  MCU_CLK_FREQUENCY
		#error Maximum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 16000KHz
	#elif	(12800u) < MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(7u)	/*F_CPU/128*/
	#elif	(6400u)  < MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(6u)	/*F_CPU/64*/
	#elif	(3200u)  < MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(5u)	/*F_CPU/32*/
	#elif	(1600u)  < MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(4u)	/*F_CPU/16*/
	#elif	(800u)   < MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(3u)	/*F_CPU/8*/
	#elif	(400u)   < MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(2u)	/*F_CPU/4*/
	#elif	(128u)  <= MCU_CLK_FREQUENCY
		#define ADC_PRESCALER		(1u)	/*F_CPU/2*/
	#else 	/*0u < MCU_CLK_FREQUENCY*/
		#error Minimum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 128KHz
	#endif	/*MCU_CLK_FREQUENCY*/

#else
	/*Check for Wrong Inputs*/
	#error 'ADC_SET_PRIORITY' can only be 'ADC_HIGHACCURACY' or 'ADC_HIGHSPEED'
#endif

	/*Reference Voltage*/
#if((ADC_VREF_INTERNAL2_56V < ADC_REF_VOLTAGE))
	#error 'ADC_REF_VOLTAGE' has been given an invalid definition
#endif
/*__________________________________________________________________________________________________________________________________________*/


/*Private Definitions*/
	/*Bits*/
#define ADEN	(7u)		/*Bit 7 in ADCSRA*/
#define ADSC	(6u)		/*Bit 6 in ADCSRA*/
#define ADIF	(4u)		/*Bit 4 in ADCSRA*/
#define MUX5	(3u)		/*Bit 3 in ADCSRB*/
#define REFS0	(6u)		/*Bit 6 in ADMUX*/
/*__________________________________________________________________________________________________________________________________________*/


#endif /*ADC_PRIVATE_H*/
