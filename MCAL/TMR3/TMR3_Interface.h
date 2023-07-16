/**********************************************************************
 * Title		: Timer 3 Interface Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Mar 2, 2023
 **********************************************************************/


#ifndef TMR3_INTERFACE_H
#define TMR3_INTERFACE_H


/*Include Needed Files*/
#include "TMR3_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*Timer Modes*/
#define TMR3_CTC		(0u)
#define TMR3_PWM		(1u)
#define TMR3_COUNTER	(2u)

    /*Timer Pre-scalers*/
#define TMR3_PRESCALER1			(1u)	/*F_CPU/1*/			/*Resolution = 1/F_CPU(Hz)			Max = 0xFFFF*1/F_CPU(Hz)		in seconds*/
#define TMR3_PRESCALER8			(2u)	/*F_CPU/8*/			/*Resolution = 8/F_CPU(Hz)			Max = 0xFFFF*8/F_CPU(Hz)		in seconds*/
#define TMR3_PRESCALER64		(3u)	/*F_CPU/64*/		/*Resolution = 64/F_CPU(Hz)			Max = 0xFFFF*64/F_CPU(Hz)		in seconds*/
#define TMR3_PRESCALER256		(4u)	/*F_CPU/256*/		/*Resolution = 256/F_CPU(Hz)		Max = 0xFFFF*256/F_CPU(Hz)		in seconds*/
#define TMR3_PRESCALER1024		(5u)	/*F_CPU/1024*/		/*Resolution = 1024/F_CPU(Hz)		Max = 0xFFFF*1024/F_CPU	(Hz)	in seconds*/
#define TMR3_EXTERNAL_FALL		(6u)	/*External Clock on Falling Edge on Pin T3*/	/*Resolution = 1/F_T3(Hz)		Max = 0xFFFF*1/F_T3(Hz)		in seconds*/
#define TMR3_EXTERNAL_RISE		(7u)	/*External Clock on Rising Edge on Pin T3*/		/*Resolution = 1/F_T3(Hz)		Max = 0xFFFF*1/F_T3(Hz)		in seconds*/

    /*CTC Modes*/
#define TMR3_CTCMODE_REPEAT		(0u)
#define TMR3_CTCMODE_ONCE		(1u)
#define TMR3_CTCMODE_NOTCTC     (2u)

    /*Counter Modes*/
#define TMR3_COUNTERMODE_REPEAT		TMR3_CTCMODE_REPEAT
#define TMR3_COUNTERMODE_ONCE		TMR3_CTCMODE_ONCE
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: TMR3_Init			: Initialize Timer 3
 * Input1 	: incpy_u8Mode		: Mode of Operation for the Timer	: TMR3_CTC, TMR3_PWM, TMR3_COUNTER
 * Input2 	: incpy_u8Prescaler	: Pre-scaler for Timer 3			: TMR3_PRESCALER1 - TMR3_EXTERNAL_RISE
 * Return 	:					: Error Status of function
 */
ErrorStatus TMR3_Init(u8 incpy_u8Mode, u8 incpy_u8Prescaler);

/*
 * Function	: TMR3_CTC_MS			: Set a function to be executed after/every x milliseconds
 * Input1 	: incpy_u8CTCMode		: after/every			: TMR3_CTCMODE_REPEAT, TMR3_CTCMODE_ONCE
 * Input2 	: incpy_u16TimeMilliSec	: x milliseconds		: 0 - 0xFFFF
 * Input3 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR3_CTC_MS(u8 incpy_u8CTCMode, u16 incpy_u16TimeMilliSec, void (*inptr_vdISR) (void));

/*
 * Function	: TMR3_CTC_S			: Set a function to be executed after/every x seconds
 * Input1 	: incpy_u8CTCMode		: after/every			: TMR3_CTCMODE_REPEAT, TMR3_CTCMODE_ONCE
 * Input2 	: incpy_u16TimeMilliSec	: x seconds				: 0 - 0xFFFF
 * Input3 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR3_CTC_S(u8 incpy_u8CTCMode, u16 incpy_u16TimeSec, void (*inptr_vdISR) (void));

/*
 * Function	: TMR3_Counter			: Set a function to be executed after/every x edges on pin T3
 * Input1 	: incpy_u8CounterMode	: after/every			: TMR3_COUNTERMODE_REPEAT, TMR3_COUNTERMODE_ONCE
 * Input2 	: incpy_u16Count		: x times				: 0 - 0xFFFF
 * Input3 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR3_Counter(u8 incpy_u8CounterMode, u16 incpy_u16Count ,void (*inptr_vdISR) (void));

/*
 * Function	: TMR3_PWMStart		: Start a PWM signal on pin OC3B with a 50% duty Cycle
 * Input1 	: incpy_u8Frequency	: Frequency of the PWM in Hz		: 0 - 0xFFFF
 * Input2 	: inptr_vdISR		: Pointer to Function	: Function to be executed
 * Return 	:					: Error Status of function
 */
ErrorStatus TMR3_PWMStart(u16 incpy_u8Frequency, void (*inptr_vdISR) (void));

/*
 * Function	: TMR3_Stop	    : De-initialize Timer 3
 * Return 	:				: Error Status of function
 */
ErrorStatus TMR3_Stop(void);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TMR3_INTERFACE_H*/
