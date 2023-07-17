/**********************************************************************
 * Title		: Timer 5 Program File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Dec 12, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "TMR5_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: TMR5_Init			: Initialize Timer 5
 * Input1 	: incpy_u8Mode		: Mode of Operation for the Timer	: TMR5_CTC_REPEAT - TMR5_COUNTER_ONCE
 * Input2 	: incpy_u8Prescaler	: Pre-scaler for Timer 5			: TMR5_PRESCALER1 - TMR5_EXTERNAL_RISE
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus TMR5_Init(u8 incpy_u8Mode, u8 incpy_u8Prescaler)
{
	if (TMR5_EXTERNAL_RISE < incpy_u8Prescaler || 0 == incpy_u8Prescaler)
	{
		return INVALID_PARAMETERS;
	}

	switch (incpy_u8Mode)
	{
	case TMR5_CTC_REPEAT:
	case TMR5_CTC_ONCE:
		/* TCCR5A Register Bits Description:
		 * COM5A1:0 (bits 7:6) choose 00 for normal port operation for pin OC5A
		 * COM5B1:0 (bits 5:4) choose 00 for normal port operation for pin OC5B
		 * COM5C1:0 (bits 3:2) choose 00 for normal port operation for pin OC5C
		 * WGM51:50 (bits 1:0) choose 00 for CTC mode
		 */
		CLR_BYTE(TCCR5A);
		/* TCCR5B Register Bits Description:
		 * ICNC5 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES5 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM53:52 (bits 4:3) choose 01 for CTC with top value in OCR5A
		 * CS52:50 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR5B = 0b00001000;
		break;

	case TMR5_PWM:
		/* TCCR5A Register Bits Description:
		 * COM5A1:0 (bits 7:6) choose 00 for normal port operation for pin OC5A
		 * COM5B1:0 (bits 5:4) choose 10 to clear pin OC5B on compare match when up-counting and set it on compare match when down-counting
		 * COM5C1:0 (bits 3:2) choose 00 for normal port operation for pin OC5C
		 * WGM51:50 (bits 1:0) choose 01 for Phase and Frequency Correct PWM mode with OCR5A as TOP value
		 */
		TCCR5A = 0b00100001;
		/* TCCR5B Register Bits Description:
		 * ICNC5 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES5 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM53:52 (bits 4:3) choose 10 for Phase and Frequency Correct PWM mode with OCR5A as TOP value
		 * CS52:50 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR5B = 0b00010000;
		DIO_PinInit(DIO_PORTL, DIO_PIN4, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		break;

	case TMR5_COUNTER_ONCE:
	case TMR5_COUNTER_REPEAT:
		if(TMR5_EXTERNAL_FALL > incpy_u8Prescaler)
		{
			return INVALID_PARAMETERS;
		}
		/* TCCR5A Register Bits Description:
		 * COM5A1:0 (bits 7:6) choose 00 for normal port operation for pin OC5A
		 * COM5B1:0 (bits 5:4) choose 00 for normal port operation for pin OC5B
		 * COM5C1:0 (bits 3:2) choose 00 for normal port operation for pin OC5C
		 * WGM51:50 (bits 1:0) choose 00 for CTC mode
		 */
		CLR_BYTE(TCCR5A);
		/* TCCR5B Register Bits Description:
		 * ICNC5 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES5 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM53:52 (bits 4:3) choose 01 for CTC with top value in OCR5A
		 * CS52:50 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR5B = 0b00001000;
		break;

	default:
		return INVALID_PARAMETERS;
	}

	Glob_u8TMR5_MODE = incpy_u8Mode;			/*Setting Timer 5 mode for later use*/
	Glob_u8TMR5_Prescaler = incpy_u8Prescaler;	/*Setting Timer 5 prescaler for later use*/

	return NO_ERROR;
}

/*
 * Function	: TMR5_CTC_MS			: Set a function to be executed after/every x milliseconds
 * Input1 	: incpy_u16TimeMilliSec	: x milliseconds		: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus TMR5_CTC_MS(u16 incpy_u16TimeMilliSec, void (*inptr_vdISR) (void))
{
	if (TMR5_CTC_ONCE != Glob_u8TMR5_MODE && TMR5_CTC_REPEAT != Glob_u8TMR5_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}

	Globptr_vdTMR5_CTC_ISR = inptr_vdISR;	/*Setting the pointer to function for use in the ISR*/

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT5 = 0x0000;					/*Clear Timer*/
	switch (Glob_u8TMR5_Prescaler)	/*Setting timer top value*/
	{
	case TMR5_PRESCALER1:
		OCR5A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 0); 	break;

	case TMR5_PRESCALER8:
		OCR5A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 3); 	break;

	case TMR5_PRESCALER64:
		OCR5A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 6); 	break;

	case TMR5_PRESCALER256:
		OCR5A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 8); 	break;

	case TMR5_PRESCALER1024:
		OCR5A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 10); 	break;

	case TMR5_EXTERNAL_FALL:
	case TMR5_EXTERNAL_RISE:
		OCR5A = incpy_u16TimeMilliSec * (EXTERNAL_CLK_T5); 	break;

	default:
		/*Not possible as prescaler has already been checked in the Init function...Do Nothing*/		
		break;
	}
	SET_BYTE(TIFR5); 					/*Clearing all timer flags*/
	TIMSK5 = 0x02; 						/*Enable output compare A match interrupt and disable all other timer 5 interrupts*/
	ENABLE_GLOB_INT(void);				/*Enabling interrupts again*/
	TCCR5B |= Glob_u8TMR5_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR5_CTC_S			: Set a function to be executed after/every x seconds
 * Input1 	: incpy_u16TimeMilliSec	: x seconds				: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus TMR5_CTC_S(u16 incpy_u16TimeSec, void (*inptr_vdISR) (void))
{
	if (TMR5_CTC_ONCE != Glob_u8TMR5_MODE && TMR5_CTC_REPEAT != Glob_u8TMR5_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}
	
	Globptr_vdTMR5_CTC_ISR = inptr_vdISR;	/*Setting the pointer to function for use in the ISR*/

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT5 = 0x0000;					/*Clear Timer*/
	switch (Glob_u8TMR5_Prescaler)	/*Setting timer top value*/
	{
	case TMR5_PRESCALER1:
		OCR5A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 0) * 1000; 	break;

	case TMR5_PRESCALER8:
		OCR5A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 3) * 1000; 	break;

	case TMR5_PRESCALER64:
		OCR5A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 6) * 1000; 	break;

	case TMR5_PRESCALER256:
		OCR5A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 8) * 1000; 	break;

	case TMR5_PRESCALER1024:
		OCR5A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 10) * 1000; 	break;

	case TMR5_EXTERNAL_FALL:
	case TMR5_EXTERNAL_RISE:
		OCR5A = incpy_u16TimeSec * (EXTERNAL_CLK_T5) * 1000;	break;

	default:
		/*Not possible as prescaler has already been checked in the Init function...Do Nothing*/		
		break;
	}
	SET_BYTE(TIFR5); 					/*Clearing all timer flags*/
	TIMSK5 = 0x02; 						/*Enable output compare A match interrupt and disable all other timer 5 interrupts*/
	ENABLE_GLOB_INT(void);				/*Enabling interrupts again*/
	TCCR5B |= Glob_u8TMR5_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR5_Counter			: Set a function to be executed after/every x edges on pin T5
 * Input1 	: incpy_u16Count		: x times				: 0 - 0xFFFF
 * Input2 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus TMR5_Counter(u16 incpy_u16Count, void (*inptr_vdISR) (void))
{
	if (TMR5_COUNTER_ONCE != Glob_u8TMR5_MODE && TMR5_COUNTER_REPEAT != Glob_u8TMR5_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}

	Globptr_vdTMR5_CTC_ISR = inptr_vdISR;	/*Setting the pointer to function for use in the ISR*/

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT5 = 0x0000;					/*Clear Timer*/

	OCR5A = incpy_u16Count - 1;		/*Setting timer top value. The -1 is because the timer takes an extra timer clock cycle to call the ISR*/

	SET_BYTE(TIFR5); 					/*Clearing all timer flags*/
	TIMSK5 = 0x02; 						/*Enable output compare A match interrupt and disable all other timer 5 interrupts*/
	ENABLE_GLOB_INT(void);				/*Enabling interrupts again*/
	TCCR5B |= Glob_u8TMR5_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR5_PWMStart				: Start a PWM signal on pin OC5B with a 50% duty Cycle
 * Input1 	: incpy_u8Frequency			: Frequency of the PWM in Hz			: 0 - 0xFFFF
 * Input2 	: incpy_u8RunCallBackFunc	: Whether to run a callback function	: TRUE, FALSE 
 * Input3 	: inptr_vdISR				: Pointer to Function					: Function to be executed
 * Return 	: ErrorStatus				: Error Status of function
 */
ErrorStatus TMR5_PWMStart(u16 incpy_u8Frequency, u8 incpy_u8RunCallBackFunc, void (*inptr_vdISR) (void))
{
	u32 Loc_OCR5AValue = 0;
	u8 Loc_u8GlobIntStatus = 0;

	if (TMR5_PWM != Glob_u8TMR5_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (TRUE == incpy_u8RunCallBackFunc && NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}
	if (TRUE < incpy_u8RunCallBackFunc)
	{
		return INVALID_PARAMETERS;
	}

	if (0 == incpy_u8Frequency)
	{
		TCCR5B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
		return NO_ERROR;
	}

	switch(Glob_u8TMR5_Prescaler)		/*Setting TOP Value in OCR5A using required frequency*/
	{
	case TMR5_PRESCALER1:
		Loc_OCR5AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 0) / incpy_u8Frequency;
		break;

	case TMR5_PRESCALER8:
		Loc_OCR5AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 3) / incpy_u8Frequency;
		break;

	case TMR5_PRESCALER64:
		Loc_OCR5AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 6) / incpy_u8Frequency;
		break;

	case TMR5_PRESCALER256:
		Loc_OCR5AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 8) / incpy_u8Frequency;
		break;

	case TMR5_PRESCALER1024:
		Loc_OCR5AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 10) / incpy_u8Frequency;
		break;

	case TMR5_EXTERNAL_FALL:
	case TMR5_EXTERNAL_RISE:
		Loc_OCR5AValue = (u32)((u32)EXTERNAL_CLK_T5 * 500) / incpy_u8Frequency;
		break;

	default:
		return INVALID_PRESCALER;		break;
	}
	Loc_OCR5AValue = (0xFFFF < Loc_OCR5AValue) ? 0xFFFF : Loc_OCR5AValue;

	Globptr_vdTMR5_CTC_ISR = inptr_vdISR;
	
	/*Disabling Global Interrupt while accessing a 16-bit registers*/
	Loc_u8GlobIntStatus = GET_GLOB_INT();
	DISABLE_GLOB_INT();

	OCR5A = Loc_OCR5AValue;
	OCR5B = OCR5A >> 1;

	if (TRUE == incpy_u8RunCallBackFunc)
	{
		ENABLE_GLOB_INT();
		TIMSK5 = 0x02; 				/*Enable output compare A match interrupt and disable all other timer 5 interrupts*/
	}
	else
	{
		MAKE_GLOB_INT(Loc_u8GlobIntStatus);
		TIMSK5 = 0x00; 				/*Disable all timer 5 interrupts*/
	}

	TCCR5B |= Glob_u8TMR5_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR5_Stop			: Stop Timer 5
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus TMR5_Stop(void)
{
	TCCR5B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
	CLR_BYTE(TIMSK5);	/*Disabling the timer interrupts*/
	return NO_ERROR;
}
/*__________________________________________________________________________________________________________________________________________*/


/*Interrupt Service Routines Declarations*/
/* 
 * Function	: Interupt Service Routine for the CTC of TMR5		: Calls a function given by the user
 */
void __vector_47(void)
{
	if (TMR5_CTC_ONCE == Glob_u8TMR5_MODE || TMR5_COUNTER_ONCE == Glob_u8TMR5_MODE)
	{
		CLR_BYTE(TIMSK5);	/*Disabling the timer interrupts so that is does not keep calling the ISR indefinitely*/
		TCCR5B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
	}

	if (NULL != Globptr_vdTMR5_CTC_ISR)
	{
		Globptr_vdTMR5_CTC_ISR();
	}
}
