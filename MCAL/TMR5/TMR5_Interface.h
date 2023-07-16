/**********************************************************************
 * Title		: Timer 5 Interface Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Mar 2, 2023
 **********************************************************************/


#ifndef TMR5_INTERFACE_H
#define TMR5_INTERFACE_H


/*Include Needed Files*/
#include "TMR5_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*Timer Modes*/
#define TMR5_CTC_REPEAT		    (0u)        /*Timer in CTC mode - will clear the timer on compare match and restart*/
#define TMR5_CTC_ONCE		    (1u)        /*Timer in CTC mode - will clear the timer on compare match but run only once*/
#define TMR5_PWM		        (2u)        /*Timer in phase correct PWM mode*/
#define TMR5_COUNTER_REPEAT	    (3u)        /*Timer in counter mode - will clear the counter on compare match and restart*/
#define TMR5_COUNTER_ONCE	    (4u)        /*Timer in counter mode - will clear the counter on compare match but run only once*/

    /*Timer Pre-scalers*/
#define TMR5_PRESCALER1			(1u)	/*F_CPU/1*/			/*Resolution = 1/F_CPU(Hz)			Max = 0xFFFF*1/F_CPU(Hz)		in seconds*/
#define TMR5_PRESCALER8			(2u)	/*F_CPU/8*/			/*Resolution = 8/F_CPU(Hz)			Max = 0xFFFF*8/F_CPU(Hz)		in seconds*/
#define TMR5_PRESCALER64		(3u)	/*F_CPU/64*/		/*Resolution = 64/F_CPU(Hz)			Max = 0xFFFF*64/F_CPU(Hz)		in seconds*/
#define TMR5_PRESCALER256		(4u)	/*F_CPU/256*/		/*Resolution = 256/F_CPU(Hz)		Max = 0xFFFF*256/F_CPU(Hz)		in seconds*/
#define TMR5_PRESCALER1024		(5u)	/*F_CPU/1024*/		/*Resolution = 1024/F_CPU(Hz)		Max = 0xFFFF*1024/F_CPU	(Hz)	in seconds*/
#define TMR5_EXTERNAL_FALL		(6u)	/*External Clock on Falling Edge on Pin T5*/	/*Resolution = 1/F_T5(Hz)		Max = 0xFFFF*1/F_T5(Hz)		in seconds*/
#define TMR5_EXTERNAL_RISE		(7u)	/*External Clock on Rising Edge on Pin T5*/		/*Resolution = 1/F_T5(Hz)		Max = 0xFFFF*1/F_T5(Hz)		in seconds*/

/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: TMR5_Init			: Initialize Timer 5
 * Input1 	: incpy_u8Mode		: Mode of Operation for the Timer	: TMR5_CTC_REPEAT - TMR5_COUNTER_ONCE
 * Input2 	: incpy_u8Prescaler	: Pre-scaler for Timer 5			: TMR5_PRESCALER1 - TMR5_EXTERNAL_RISE
 * Return 	:					: Error Status of function
 */
ErrorStatus TMR5_Init(u8 incpy_u8Mode, u8 incpy_u8Prescaler);

/*
 * Function	: TMR5_CTC_MS			: Set a function to be executed after/every x milliseconds
 * Input1 	: incpy_u16TimeMilliSec	: x milliseconds		: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR5_CTC_MS(u16 incpy_u16TimeMilliSec, void (*inptr_vdISR) (void));

/*
 * Function	: TMR5_CTC_S			: Set a function to be executed after/every x seconds
 * Input1 	: incpy_u16TimeMilliSec	: x seconds				: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR5_CTC_S(u16 incpy_u16TimeSec, void (*inptr_vdISR) (void));

/*
 * Function	: TMR5_Counter			: Set a function to be executed after/every x edges on pin T5
 * Input1 	: incpy_u16Count		: x times				: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR5_Counter(u16 incpy_u16Count, void (*inptr_vdISR) (void));

/*
 * Function	: TMR5_PWMStart				: Start a PWM signal on pin OC5B with a 50% duty Cycle
 * Input1 	: incpy_u8Frequency			: Frequency of the PWM in Hz			: 0 - 0xFFFF
 * Input2 	: incpy_u8RunCallBackFunc	: Whether to run a callback function	: TRUE, FALSE 
 * Input3 	: inptr_vdISR				: Pointer to Function					: Function to be executed
 * Return 	:							: Error Status of function
 */
ErrorStatus TMR5_PWMStart(u16 incpy_u8Frequency, u8 incpy_u8RunCallBackFunc, void (*inptr_vdISR) (void));

/*
 * Function	: TMR5_Stop	    : De-initialize Timer 5
 * Return 	:				: Error Status of function
 */
ErrorStatus TMR5_Stop(void);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TMR5_INTERFACE_H*/
