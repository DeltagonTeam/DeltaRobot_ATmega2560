/**********************************************************************
 * Title		: Timer 4 Interface Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Mar 2, 2023
 **********************************************************************/


#ifndef TMR4_INTERFACE_H
#define TMR4_INTERFACE_H


/*Include Needed Files*/
#include "TMR4_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*Timer Modes*/
#define TMR4_CTC_REPEAT		    (0u)        /*Timer in CTC mode - will clear the timer on compare match and restart*/
#define TMR4_CTC_ONCE		    (1u)        /*Timer in CTC mode - will clear the timer on compare match but run only once*/
#define TMR4_PWM		        (2u)        /*Timer in phase correct PWM mode*/
#define TMR4_COUNTER_REPEAT	    (3u)        /*Timer in counter mode - will clear the counter on compare match and restart*/
#define TMR4_COUNTER_ONCE	    (4u)        /*Timer in counter mode - will clear the counter on compare match but run only once*/

    /*Timer Pre-scalers*/
#define TMR4_PRESCALER1			(1u)	/*F_CPU/1*/			/*Resolution = 1/F_CPU(Hz)			Max = 0xFFFF*1/F_CPU(Hz)		in seconds*/
#define TMR4_PRESCALER8			(2u)	/*F_CPU/8*/			/*Resolution = 8/F_CPU(Hz)			Max = 0xFFFF*8/F_CPU(Hz)		in seconds*/
#define TMR4_PRESCALER64		(3u)	/*F_CPU/64*/		/*Resolution = 64/F_CPU(Hz)			Max = 0xFFFF*64/F_CPU(Hz)		in seconds*/
#define TMR4_PRESCALER256		(4u)	/*F_CPU/256*/		/*Resolution = 256/F_CPU(Hz)		Max = 0xFFFF*256/F_CPU(Hz)		in seconds*/
#define TMR4_PRESCALER1024		(5u)	/*F_CPU/1024*/		/*Resolution = 1024/F_CPU(Hz)		Max = 0xFFFF*1024/F_CPU	(Hz)	in seconds*/
#define TMR4_EXTERNAL_FALL		(6u)	/*External Clock on Falling Edge on Pin T4*/	/*Resolution = 1/F_T4(Hz)		Max = 0xFFFF*1/F_T4(Hz)		in seconds*/
#define TMR4_EXTERNAL_RISE		(7u)	/*External Clock on Rising Edge on Pin T4*/		/*Resolution = 1/F_T4(Hz)		Max = 0xFFFF*1/F_T4(Hz)		in seconds*/

/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: TMR4_Init			: Initialize Timer 4
 * Input1 	: incpy_u8Mode		: Mode of Operation for the Timer	: TMR4_CTC_REPEAT - TMR4_COUNTER_ONCE
 * Input2 	: incpy_u8Prescaler	: Pre-scaler for Timer 4			: TMR4_PRESCALER1 - TMR4_EXTERNAL_RISE
 * Return 	:					: Error Status of function
 */
ErrorStatus TMR4_Init(u8 incpy_u8Mode, u8 incpy_u8Prescaler);

/*
 * Function	: TMR4_CTC_MS			: Set a function to be executed after/every x milliseconds
 * Input1 	: incpy_u16TimeMilliSec	: x milliseconds		: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR4_CTC_MS(u16 incpy_u16TimeMilliSec, void (*inptr_vdISR) (void));

/*
 * Function	: TMR4_CTC_S			: Set a function to be executed after/every x seconds
 * Input1 	: incpy_u16TimeMilliSec	: x seconds				: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR4_CTC_S(u16 incpy_u16TimeSec, void (*inptr_vdISR) (void));

/*
 * Function	: TMR4_Counter			: Set a function to be executed after/every x edges on pin T4
 * Input1 	: incpy_u16Count		: x times				: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR4_Counter(u16 incpy_u16Count, void (*inptr_vdISR) (void));

/*
 * Function	: TMR4_PWMStart				: Start a PWM signal on pin OC4B with a 50% duty Cycle
 * Input1 	: incpy_u8Frequency			: Frequency of the PWM in Hz			: 0 - 0xFFFF
 * Input2 	: incpy_u8RunCallBackFunc	: Whether to run a callback function	: TRUE, FALSE 
 * Input3 	: inptr_vdISR				: Pointer to Function					: Function to be executed
 * Return 	:							: Error Status of function
 */
ErrorStatus TMR4_PWMStart(u16 incpy_u8Frequency, u8 incpy_u8RunCallBackFunc, void (*inptr_vdISR) (void));

/*
 * Function	: TMR4_Stop	    : De-initialize Timer 4
 * Return 	:				: Error Status of function
 */
ErrorStatus TMR4_Stop(void);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TMR4_INTERFACE_H*/
