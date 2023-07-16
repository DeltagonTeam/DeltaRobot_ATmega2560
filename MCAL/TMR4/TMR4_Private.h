/**********************************************************************
 * Title		: Timer 4 Private Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Mar 2, 2023
 **********************************************************************/


#ifndef TMR4_PRIVATE_H
#define TMR4_PRIVATE_H


/*Include Needed Files*/
#include "TMR4_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Pre-Build Configuration Checks*/
#if		(16000u) <  MCU_CLK_FREQUENCY
	#error Maximum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 16000KHz
#elif 	(0u) > MCU_CLK_FREQUENCY
	#error Minimum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 128KHz
#endif	/*MCU_CLK_FREQUENCY*/

#if		(16000u) <  EXTERNAL_CLK_T4
	#error Maximum 'EXTERNAL_CLK_T4' for 'ATMEGA2560' is 16000KHz
#elif 	(0u) > EXTERNAL_CLK_T4
	#error Minimum 'EXTERNAL_CLK_T4' for 'ATMEGA2560' is 128KHz
#endif	/*MCU_CLK_FREQUENCY*/
/*__________________________________________________________________________________________________________________________________________*/


/*Private Macros Definitions*/
#define __INTR_ATTRS	used,externally_visible
/*__________________________________________________________________________________________________________________________________________*/


/*Global Variables Definitions*/
static void (* Globptr_vdTMR4_CTC_ISR) (void) = NULL;
static u8 Glob_u8TMR4_Prescaler = 0;
static u8 Glob_u8TMR4_MODE = 0;
/*__________________________________________________________________________________________________________________________________________*/


/*Interrupt Service Routines Declarations*/
/* 
 * Function	: Interupt Service Routine for the CTC of TMR4		: Calls a function given by the user
 */
void __vector_42(void)__attribute__( (signal, __INTR_ATTRS) );
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TMR4_PRIVATE_H*/
