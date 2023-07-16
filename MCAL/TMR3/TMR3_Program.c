/**********************************************************************
 * Title		: Timer 3 Program File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Dec 12, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "TMR3_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: TMR3_Init			: Initialize Timer 3
 * Input1 	: incpy_u8Mode		: Mode of Operation for the Timer	: TMR3_CTC, TMR3_PWM, TMR3_COUNTER
 * Input2 	: incpy_u8Prescaler	: Pre-scaler for Timer 3			: TMR3_PRESCALER1 - TMR3_EXTERNAL_RISE
 * Return 	:					: Error Status of function
 */
ErrorStatus TMR3_Init(u8 incpy_u8Mode, u8 incpy_u8Prescaler)
{
	if (TMR3_EXTERNAL_RISE < incpy_u8Prescaler || 0 == incpy_u8Prescaler)
	{
		return INVALID_PARAMETERS;
	}
	switch (incpy_u8Mode)
	{
	case TMR3_CTC:
		/* TCCR3A Register Bits Description:
		 * COM3A1:0 (bits 7:6) choose 00 for normal port operation for pin OC3A
		 * COM3B1:0 (bits 5:4) choose 00 for normal port operation for pin OC3B
		 * COM3C1:0 (bits 3:2) choose 00 for normal port operation for pin OC3C
		 * WGM31:30 (bits 1:0) choose 00 for CTC mode
		 */
		CLR_BYTE(TCCR3A);
		/* TCCR3B Register Bits Description:
		 * ICNC3 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES3 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM33:32 (bits 4:3) choose 01 for CTC with top value in OCR3A
		 * CS32:30 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR3B = 0b00001000;
		break;

	case TMR3_PWM:
		/* TCCR3A Register Bits Description:
		 * COM3A1:0 (bits 7:6) choose 00 for normal port operation for pin OC3A
		 * COM3B1:0 (bits 5:4) choose 10 to clear pin OC3B on compare match when up-counting and set it on compare match when down-counting
		 * COM3C1:0 (bits 3:2) choose 00 for normal port operation for pin OC3C
		 * WGM31:30 (bits 1:0) choose 01 for Phase and Frequency Correct PWM mode with OCR3A as TOP value
		 */
		TCCR3A = 0b00100001;
		/* TCCR3B Register Bits Description:
		 * ICNC3 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES3 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM33:32 (bits 4:3) choose 10 for Phase and Frequency Correct PWM mode with OCR3A as TOP value
		 * CS32:30 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR3B = 0b00010000;
		DIO_PinInit(DIO_PORTE,DIO_PIN4,DIO_PIN_OUTPUT,DIO_PIN_LOW);
		Glob_u8TMR3_CTC_MODE = TMR3_CTCMODE_NOTCTC;
		break;

	case TMR3_COUNTER:
		if(TMR3_EXTERNAL_FALL > incpy_u8Prescaler)
		{
			return INVALID_PARAMETERS;
		}
		/* TCCR3A Register Bits Description:
		 * COM3A1:0 (bits 7:6) choose 00 for normal port operation for pin OC3A
		 * COM3B1:0 (bits 5:4) choose 00 for normal port operation for pin OC3B
		 * COM3C1:0 (bits 3:2) choose 00 for normal port operation for pin OC3C
		 * WGM31:30 (bits 1:0) choose 00 for CTC mode
		 */
		CLR_BYTE(TCCR3A);
		/* TCCR3B Register Bits Description:
		 * ICNC3 	(bit 7) for noise canceler of input capture, which is not used.
		 * ICES3 	(bit 6) for edge selection in input capture, which is not used.
		 * R		(bit 5) reserved
		 * WGM33:32 (bits 4:3) choose 01 for CTC with top value in OCR3A
		 * CS32:30 	(bits 2:0) for pre-scaler which will be selected later.
		 */
		TCCR3B = 0b00001000;
		Glob_u8TMR3_CTC_MODE = TMR3_CTCMODE_NOTCTC;
		break;

	default:
		return INVALID_PARAMETERS;
	}
	Glob_u8TMR3_Prescaler = incpy_u8Prescaler;

	return NO_ERROR;
}

/*
 * Function	: TMR3_CTC_MS			: Set a function to be executed after/every x milliseconds
 * Input1 	: incpy_u8CTCMode		: after/every			: TMR3_CTCMODE_REPEAT, TMR3_CTCMODE_ONCE
 * Input2 	: incpy_u16TimeMilliSec	: x milliseconds		: 0 - 0xFFFF
 * Input3 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR3_CTC_MS(u8 incpy_u8CTCMode, u16 incpy_u16TimeMilliSec ,void (*inptr_vdISR) (void))
{
	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}
	if (TMR3_CTCMODE_ONCE < incpy_u8CTCMode)
	{
		return INVALID_PARAMETERS;
	}
	Glob_u8TMR3_CTC_MODE = incpy_u8CTCMode;
	Globptr_vdTMR3_CTC_ISR = inptr_vdISR;

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT3 = 0x0000;				/*Clear Timer*/
	switch (Glob_u8TMR3_Prescaler)	/*Setting timer top value*/
	{
	case TMR3_PRESCALER1:
		OCR3A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 0); 	break;

	case TMR3_PRESCALER8:
		OCR3A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 3); 	break;

	case TMR3_PRESCALER64:
		OCR3A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 6); 	break;

	case TMR3_PRESCALER256:
		OCR3A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 8); 	break;

	case TMR3_PRESCALER1024:
		OCR3A = incpy_u16TimeMilliSec * (MCU_CLK_FREQUENCY >> 10); 	break;

	case TMR3_EXTERNAL_FALL:
	case TMR3_EXTERNAL_RISE:
		OCR3A = incpy_u16TimeMilliSec * (EXTERNAL_CLK_T3); 	break;

	default:
		/*Not possible...Do Nothing*/		break;
	}
	SET_BYTE(TIFR3); 			/*Clearing all timer flags*/
	TIMSK3 = 0x02; 				/*Enable output compare A match interrupt and disable all other timer 3 interrupts*/
	ENABLE_GLOB_INT(void);			/*Enabling interrupts again*/
	TCCR3B |= Glob_u8TMR3_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR3_CTC_S			: Set a function to be executed after/every x seconds
 * Input1 	: incpy_u8CTCMode		: after/every			: TMR3_CTCMODE_REPEAT, TMR3_CTCMODE_ONCE
 * Input2 	: incpy_u16TimeMilliSec	: x seconds				: 0 - 0xFFFF
 * Input3 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR3_CTC_S(u8 incpy_u8CTCMode, u16 incpy_u16TimeSec ,void (*inptr_vdISR) (void))
{
	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}
	if (TMR3_CTCMODE_ONCE < incpy_u8CTCMode)
	{
		return INVALID_PARAMETERS;
	}
	Glob_u8TMR3_CTC_MODE = incpy_u8CTCMode;
	Globptr_vdTMR3_CTC_ISR = inptr_vdISR;

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT3 = 0x0000;				/*Clear Timer*/
	switch (Glob_u8TMR3_Prescaler)	/*Setting timer top value*/
	{
	case TMR3_PRESCALER1:
		OCR3A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 0) * 1000; 	break;

	case TMR3_PRESCALER8:
		OCR3A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 3) * 1000; 	break;

	case TMR3_PRESCALER64:
		OCR3A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 6) * 1000; 	break;

	case TMR3_PRESCALER256:
		OCR3A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 8) * 1000; 	break;

	case TMR3_PRESCALER1024:
		OCR3A = incpy_u16TimeSec * (MCU_CLK_FREQUENCY >> 10) * 1000; 	break;

	case TMR3_EXTERNAL_FALL:
	case TMR3_EXTERNAL_RISE:
		OCR3A = incpy_u16TimeSec * (EXTERNAL_CLK_T3) * 1000; 	break;

	default:
		/*Not possible...Do Nothing*/		break;
	}
	SET_BYTE(TIFR3); 			/*Clearing all timer flags*/
	TIMSK3 = 0x02; 				/*Enable output compare A match interrupt and disable all other timer 3 interrupts*/
	ENABLE_GLOB_INT(void);			/*Enabling interrupts again*/
	TCCR3B |= Glob_u8TMR3_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR3_Counter			: Set a function to be executed after/every x edges on pin T3
 * Input1 	: incpy_u8CounterMode	: after/every			: TMR3_COUNTERMODE_REPEAT, TMR3_COUNTERMODE_ONCE
 * Input2 	: incpy_u16Count		: x times				: 0 - 0xFFFF
 * Input3 	: inptr_vdISR			: Pointer to Function	: Function to be executed
 * Return 	:						: Error Status of function
 */
ErrorStatus TMR3_Counter(u8 incpy_u8CounterMode, u16 incpy_u16Count ,void (*inptr_vdISR) (void))
{
	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}
	if (TMR3_COUNTERMODE_ONCE < incpy_u8CounterMode)
	{
		return INVALID_PARAMETERS;
	}
	Glob_u8TMR3_CTC_MODE = incpy_u8CounterMode;
	Globptr_vdTMR3_CTC_ISR = inptr_vdISR;

	DISABLE_GLOB_INT(void);			/*Disabling interrupts as accessing a 16-bit register is an atomic operation*/
	TCNT3 = 0x0000;				/*Clear Timer*/

	OCR3A = incpy_u16Count - 1;		/*Setting timer top value. The -1 is because the timer takes an extra timer clock cycle to call the ISR*/

	SET_BYTE(TIFR3); 			/*Clearing all timer flags*/
	TIMSK3 = 0x02; 				/*Enable output compare A match interrupt and disable all other timer 3 interrupts*/
	ENABLE_GLOB_INT(void);			/*Enabling interrupts again*/
	TCCR3B |= Glob_u8TMR3_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR3_PWMStart		: Start a PWM signal on pin OC3B with a 50% duty Cycle
 * Input1 	: incpy_u8Frequency	: Frequency of the PWM in Hz		: 0 - 0xFFFF
 * Input2 	: inptr_vdISR		: Pointer to Function	: Function to be executed
 * Return 	:					: Error Status of function
 */
ErrorStatus TMR3_PWMStart(u16 incpy_u8Frequency, void (*inptr_vdISR) (void))
{
	u32 Loc_OCR3AValue = 0;

	if (0 == incpy_u8Frequency)
	{
		TCCR3B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
		return NO_ERROR;
	}
	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}

	switch(Glob_u8TMR3_Prescaler)		/*Setting TOP Value in OCR3A using required frequency*/
	{
	case TMR3_PRESCALER1:
		Loc_OCR3AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 0) / incpy_u8Frequency;
		break;

	case TMR3_PRESCALER8:
		Loc_OCR3AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 3) / incpy_u8Frequency;
		break;

	case TMR3_PRESCALER64:
		Loc_OCR3AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 6) / incpy_u8Frequency;
		break;

	case TMR3_PRESCALER256:
		Loc_OCR3AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 8) / incpy_u8Frequency;
		break;

	case TMR3_PRESCALER1024:
		Loc_OCR3AValue = (u32)(((u32)MCU_CLK_FREQUENCY * 500) >> 10) / incpy_u8Frequency;
		break;

	case TMR3_EXTERNAL_FALL:
	case TMR3_EXTERNAL_RISE:
		Loc_OCR3AValue = (u32)((u32)EXTERNAL_CLK_T3 * 500) / incpy_u8Frequency;
		break;

	default:
		return INVALID_PRESCALER;		break;
	}
	Loc_OCR3AValue = (0xFFFF < Loc_OCR3AValue) ? 0xFFFF : Loc_OCR3AValue;

	Globptr_vdTMR3_CTC_ISR = inptr_vdISR;

	/*Disabling Global Interrupt while accessing a 16-bit registers*/
	DISABLE_GLOB_INT(void);

	OCR3A = Loc_OCR3AValue;

	OCR3B = OCR3A >> 1;

	ENABLE_GLOB_INT();

	TIMSK3 = 0x02; 				/*Enable output compare A match interrupt and disable all other timer 3 interrupts*/
	
	TCCR3B |= Glob_u8TMR3_Prescaler; 	/*Turning the timer on by setting pre-scaler*/
	return NO_ERROR;
}

/*
 * Function	: TMR3_Deinit	: De-initialize Timer 3
 * Return 	:				: Error Status of function
 */
ErrorStatus TMR3_Deinit(void)
{
	CLR_BYTE(TIMSK3);	/*Disabling the timer interrupts*/
	TCCR3B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
	return NO_ERROR;
}
/*__________________________________________________________________________________________________________________________________________*/


/*Interrupt Service Routines Declarations*/
/* 
 * Function	: Interupt Service Routine for the CTC of TMR3		: Calls a function given by the user
 */
void __vector_32(void)
{
	if (TMR3_CTCMODE_ONCE == Glob_u8TMR3_CTC_MODE)
	{
		CLR_BYTE(TIMSK3);	/*Disabling the timer interrupts so that is does not keep calling the ISR indefinitely*/
		TCCR3B &= 0xF8;		/*Turning Timer off by removing pre-scaler*/
	}

	if (NULL != Globptr_vdTMR3_CTC_ISR)
	{
		Globptr_vdTMR3_CTC_ISR();
	}
}
