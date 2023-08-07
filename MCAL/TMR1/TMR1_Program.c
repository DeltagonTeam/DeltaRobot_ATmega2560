/**********************************************************************
 * Title		: Timer 1 Program File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Dec 12, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "TMR1_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: TMR1_Init			: Initialize Timer 1
 * Input1 	: incpy_u8Mode		: Mode of Operation for the Timer	: TMR1_CTC_REPEAT - TMR1_COUNTER_ONCE
 * Input2 	: incpy_u8Prescaler	: Pre-scaler for Timer 1			: TMR1_PRESCALER1 - TMR1_EXTERNAL_RISE
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus TMR1_Init(u8 incpy_u8Mode, u8 incpy_u8Prescaler)
{
	if (TMR1_EXTERNAL_RISE < incpy_u8Prescaler || 0 == incpy_u8Prescaler)
	{
		return INVALID_PARAMETERS;
	}

	switch (incpy_u8Mode)
	{
	case TMR1_CTC_REPEAT:
	case TMR1_CTC_ONCE:
		/* TCCR1A Register Bits Description:
		 * COM1A1:0 (bits 7:6) choose 00 for normal port operation for pin OC1A
		 * COM1B1:0 (bits 5:4) choose 00 for normal port operation for pin OC1B
		 * COM1C1:0 (bits 3:2) choose 00 for normal port operation for pin OC1C
		 * WGM11:10 (bits 1:0) choose 00 for CTC mode
		 */
		CLR_BYTE(TCCR1A);
		/* TCCR1B Register Bits Description:
		 * ICNC1 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES1 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM13:12 (bits 4:3) choose 01 for CTC with top value in OCR1A
		 * CS12:10 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR1B = 0b00001000;
		break;

	case TMR1_PWM:
		/* TCCR1A Register Bits Description:
		 * COM1A1:0 (bits 7:6) choose 00 for normal port operation for pin OC1A
		 * COM1B1:0 (bits 5:4) choose 10 to clear pin OC1B on compare match when up-counting and set it on compare match when down-counting
		 * COM1C1:0 (bits 3:2) choose 00 for normal port operation for pin OC1C
		 * WGM11:10 (bits 1:0) choose 01 for Phase and Frequency Correct PWM mode with OCR1A as TOP value
		 */
		TCCR1A = 0b00100001;
		/* TCCR1B Register Bits Description:
		 * ICNC1 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES1 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM13:12 (bits 4:3) choose 10 for Phase and Frequency Correct PWM mode with OCR1A as TOP value
		 * CS12:10 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR1B = 0b00010000;
		DIO_PinInit(DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT, DIO_PIN_LOW);
		break;

	case TMR1_COUNTER_ONCE:
	case TMR1_COUNTER_REPEAT:
		if(TMR1_EXTERNAL_FALL > incpy_u8Prescaler)
		{
			return INVALID_PARAMETERS;
		}
		/* TCCR1A Register Bits Description:
		 * COM1A1:0 (bits 7:6) choose 00 for normal port operation for pin OC1A
		 * COM1B1:0 (bits 5:4) choose 00 for normal port operation for pin OC1B
		 * COM1C1:0 (bits 3:2) choose 00 for normal port operation for pin OC1C
		 * WGM11:10 (bits 1:0) choose 00 for CTC mode
		 */
		CLR_BYTE(TCCR1A);
		/* TCCR1B Register Bits Description:
		 * ICNC1 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES1 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM13:12 (bits 4:3) choose 01 for CTC with top value in OCR1A
		 * CS12:10 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR1B = 0b00001000;
		break;

	default:
		return INVALID_PARAMETERS;
	}

	Glob_u8TMR1_MODE = incpy_u8Mode;			/*Setting Timer 1 mode for later use*/
	Glob_u8TMR1_Prescaler = incpy_u8Prescaler;	/*Setting Timer 1 prescaler for later use*/

	return NO_ERROR;
}

/*
 * Function	: TMR1_CTC_MS			: Set a function to be executed after/every x milliseconds
 * Input1 	: incpy_u16TimeMilliSec	: x milliseconds						: 0 - 0xFFFF
 * Input2 	: inptr_vdCallback		: Pointer to the callback function      : Pointer to function
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus TMR1_CTC_MS(u16 incpy_u16TimeMilliSec, void (*inptr_vdCallback) (void))
{
	if (TMR1_CTC_ONCE != Glob_u8TMR1_MODE && TMR1_CTC_REPEAT != Glob_u8TMR1_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (NULL == inptr_vdCallback)
	{
		return NULL_POINTER_PASSED;
	}

	Globptr_vdTMR1Callback = inptr_vdCallback;	/*Setting the pointer to function for use in the ISR*/

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT1 = 0x0000;					/*Clear Timer*/
	switch (Glob_u8TMR1_Prescaler)	/*Setting timer top value*/
	{
	case TMR1_PRESCALER1:
		OCR1A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 0); 	break;

	case TMR1_PRESCALER8:
		OCR1A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 3); 	break;

	case TMR1_PRESCALER64:
		OCR1A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 6); 	break;

	case TMR1_PRESCALER256:
		OCR1A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 8); 	break;

	case TMR1_PRESCALER1024:
		OCR1A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 10); 	break;

	case TMR1_EXTERNAL_FALL:
	case TMR1_EXTERNAL_RISE:
		OCR1A = incpy_u16TimeMilliSec * (EXTERNAL_CLK_T1); 	break;

	default:
		/*Not possible as prescaler has already been checked in the Init function...Do Nothing*/		
		break;
	}
	SET_BYTE(TIFR1); 					/*Clearing all timer flags*/
	TIMSK1 = 0x02; 						/*Enable output compare A match interrupt and disable all other timer 1 interrupts*/
	ENABLE_GLOB_INT(void);				/*Enabling interrupts again*/
	TCCR1B |= Glob_u8TMR1_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR1_CTC_S			: Set a function to be executed after/every x seconds
 * Input1 	: incpy_u16TimeMilliSec	: x seconds								: 0 - 0xFFFF
 * Input2 	: inptr_vdCallback		: Pointer to the callback function      : Pointer to function
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus TMR1_CTC_S(u16 incpy_u16TimeSec, void (*inptr_vdCallback) (void))
{
	if (TMR1_CTC_ONCE != Glob_u8TMR1_MODE && TMR1_CTC_REPEAT != Glob_u8TMR1_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (NULL == inptr_vdCallback)
	{
		return NULL_POINTER_PASSED;
	}
	
	Globptr_vdTMR1Callback = inptr_vdCallback;	/*Setting the pointer to function for use in the ISR*/

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT1 = 0x0000;					/*Clear Timer*/
	switch (Glob_u8TMR1_Prescaler)	/*Setting timer top value*/
	{
	case TMR1_PRESCALER1:
		OCR1A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 0) * 1000; 	break;

	case TMR1_PRESCALER8:
		OCR1A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 3) * 1000; 	break;

	case TMR1_PRESCALER64:
		OCR1A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 6) * 1000; 	break;

	case TMR1_PRESCALER256:
		OCR1A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 8) * 1000; 	break;

	case TMR1_PRESCALER1024:
		OCR1A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 10) * 1000; 	break;

	case TMR1_EXTERNAL_FALL:
	case TMR1_EXTERNAL_RISE:
		OCR1A = incpy_u16TimeSec * (EXTERNAL_CLK_T1) * 1000;	break;

	default:
		/*Not possible as prescaler has already been checked in the Init function...Do Nothing*/		
		break;
	}
	SET_BYTE(TIFR1); 					/*Clearing all timer flags*/
	TIMSK1 = 0x02; 						/*Enable output compare A match interrupt and disable all other timer 1 interrupts*/
	ENABLE_GLOB_INT(void);				/*Enabling interrupts again*/
	TCCR1B |= Glob_u8TMR1_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR1_Counter			: Set a function to be executed after/every x edges on pin T1
 * Input1 	: incpy_u16Count		: x times								: 0 - 0xFFFF
 * Input2 	: inptr_vdCallback		: Pointer to the callback function      : Pointer to function
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus TMR1_Counter(u16 incpy_u16Count, void (*inptr_vdCallback) (void))
{
	if (TMR1_COUNTER_ONCE != Glob_u8TMR1_MODE && TMR1_COUNTER_REPEAT != Glob_u8TMR1_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (NULL == inptr_vdCallback)
	{
		return NULL_POINTER_PASSED;
	}

	Globptr_vdTMR1Callback = inptr_vdCallback;	/*Setting the pointer to function for use in the ISR*/

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT1 = 0x0000;					/*Clear Timer*/

	OCR1A = incpy_u16Count - 1;		/*Setting timer top value. The -1 is because the timer takes an extra timer clock cycle to call the ISR*/

	SET_BYTE(TIFR1); 					/*Clearing all timer flags*/
	TIMSK1 = 0x02; 						/*Enable output compare A match interrupt and disable all other timer 1 interrupts*/
	ENABLE_GLOB_INT(void);				/*Enabling interrupts again*/
	TCCR1B |= Glob_u8TMR1_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR1_PWMStart				: Start a PWM signal on pin OC1B with a 50% duty Cycle
 * Input1 	: incpy_u8Frequency			: Frequency of the PWM in Hz			: 0 - 0xFFFF
 * Input2 	: incpy_u8DutyCycle			: Duty cycle of PWM in percentage		: 0 - 100
 * Input3 	: incpy_u8RunCallBackFunc	: Whether to run a callback function	: TRUE, FALSE 
 * Input4 	: inptr_vdCallback			: Pointer to the callback function      : Pointer to function
 * Return 	: ErrorStatus				: Error Status of function
 */
ErrorStatus TMR1_PWMStart(u16 incpy_u8Frequency, u8 incpy_u8DutyCycle, u8 incpy_u8RunCallBackFunc, void (*inptr_vdCallback) (void))
{
	u32 Loc_OCR1AValue = 0;
	u8 Loc_u8GlobIntStatus = 0;

	if (TMR1_PWM != Glob_u8TMR1_MODE)
	{
		return INVALID_FUNCTION;
	}
	if (TRUE == incpy_u8RunCallBackFunc && NULL == inptr_vdCallback)
	{
		return NULL_POINTER_PASSED;
	}
	if (TRUE < incpy_u8RunCallBackFunc)
	{
		return INVALID_PARAMETERS;
	}

	if (0 == incpy_u8Frequency)
	{
		TCCR1B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
		return NO_ERROR;
	}

	switch(Glob_u8TMR1_Prescaler)		/*Setting TOP Value in OCR1A using required frequency*/
	{
	case TMR1_PRESCALER1:
		Loc_OCR1AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 0) / incpy_u8Frequency;
		break;

	case TMR1_PRESCALER8:
		Loc_OCR1AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 3) / incpy_u8Frequency;
		break;

	case TMR1_PRESCALER64:
		Loc_OCR1AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 6) / incpy_u8Frequency;
		break;

	case TMR1_PRESCALER256:
		Loc_OCR1AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 8) / incpy_u8Frequency;
		break;

	case TMR1_PRESCALER1024:
		Loc_OCR1AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 10) / incpy_u8Frequency;
		break;

	case TMR1_EXTERNAL_FALL:
	case TMR1_EXTERNAL_RISE:
		Loc_OCR1AValue = (u32)((u32)EXTERNAL_CLK_T1 * 500) / incpy_u8Frequency;
		break;

	default:
		return INVALID_PRESCALER;		break;
	}
	Loc_OCR1AValue = (0xFFFF < Loc_OCR1AValue) ? 0xFFFF : Loc_OCR1AValue;

	Globptr_vdTMR1Callback = inptr_vdCallback;
	
	/*Disabling Global Interrupt while accessing a 16-bit registers*/
	Loc_u8GlobIntStatus = GET_GLOB_INT();
	DISABLE_GLOB_INT();

	OCR1A = Loc_OCR1AValue;
	OCR1B = (0 != incpy_u8DutyCycle)? (OCR1A / (100/incpy_u8DutyCycle)) : 0;

	if (TRUE == incpy_u8RunCallBackFunc)
	{
		ENABLE_GLOB_INT();
		TIMSK1 = 0x02; 				/*Enable output compare A match interrupt and disable all other timer 1 interrupts*/
	}
	else
	{
		MAKE_GLOB_INT(Loc_u8GlobIntStatus);
		TIMSK1 = 0x00; 				/*Disable all timer 1 interrupts*/
	}

	TCCR1B |= Glob_u8TMR1_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR1_Stop			: Stop Timer 1
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus TMR1_Stop(void)
{
	TCCR1B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
	CLR_BYTE(TIMSK1);	/*Disabling the timer interrupts*/
	return NO_ERROR;
}
/*__________________________________________________________________________________________________________________________________________*/


/*Interrupt Service Routines Declarations*/
/* 
 * Function	: Interupt Service Routine for the CTC of TMR1		: Calls a function given by the user
 */
void __vector_17(void)
{
	if (TMR1_CTC_ONCE == Glob_u8TMR1_MODE || TMR1_COUNTER_ONCE == Glob_u8TMR1_MODE)
	{
		CLR_BYTE(TIMSK1);	/*Disabling the timer interrupts so that is does not keep calling the ISR indefinitely*/
		TCCR1B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
	}

	if (NULL != Globptr_vdTMR1Callback)
	{
		Globptr_vdTMR1Callback();
	}
}
