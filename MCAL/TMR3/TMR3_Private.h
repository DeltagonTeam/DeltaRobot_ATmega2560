/**********************************************************************
 * Title		: Timer 3 Private Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Mar 2, 2023
 **********************************************************************/


#ifndef TMR3_PRIVATE_H
#define TMR3_PRIVATE_H


/*Include Needed Files*/
#include "TMR3_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Pre-Build Configuration Checks*/
#if		(16000u) <  MCU_CLK_FREQUENCY
	#error Maximum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 16000KHz
#elif 	(0u) > MCU_CLK_FREQUENCY
	#error Minimum 'MCU_CLK_FREQUENCY' for 'ATMEGA2560' is 128KHz
#endif	/*MCU_CLK_FREQUENCY*/

#if		(16000u) <  EXTERNAL_CLK_T3
	#error Maximum 'EXTERNAL_CLK_T3' for 'ATMEGA2560' is 16000KHz
#elif 	(0u) > EXTERNAL_CLK_T3
	#error Minimum 'EXTERNAL_CLK_T3' for 'ATMEGA2560' is 128KHz
#endif	/*MCU_CLK_FREQUENCY*/
/*__________________________________________________________________________________________________________________________________________*/


/*Private Macros Definitions*/
#define __INTR_ATTRS	used,externally_visible
/*__________________________________________________________________________________________________________________________________________*/


/*Global Variables Definitions*/
static void (* Globptr_vdTMR3_CTC_ISR) (void) = NULL;
static u8 Glob_u8TMR3_Prescaler = 0;
static u8 Glob_u8TMR3_MODE = 0;
/*__________________________________________________________________________________________________________________________________________*/


/*Interrupt Service Routines Declarations*/
/* 
 * Function	: Interupt Service Routine for the CTC of TMR3		: Calls a function given by the user
 */
void __vector_32(void)__attribute__( (signal, __INTR_ATTRS) );
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TMR3_PRIVATE_H*/
