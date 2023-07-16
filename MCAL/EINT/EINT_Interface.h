/**********************************************************************
 * Title		: External Interrupt Interface Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab
 * Last Update	: Jan 30, 2023
 **********************************************************************/


#ifndef EINT_INTERFACE_H
#define EINT_INTERFACE_H


/*Include Needed Files*/
#include "EINT_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*External Interrupt Modes*/
#define EINT_LOW		(0u)
#define EINT_TOGGLE		(1u)
#define EINT_FALLING	(2u)
#define EINT_RISING		(3u)

    /*Internal Pull up Resistor Enable and Disable*/
#define EINT_PULLUP			DIO_PIN_PULLUP
#define EINT_NOPULLUP		DIO_PIN_NOPULLUP

    /*External Interrupts*/
#define EINT0				(0u)		/*PortD - PIN0*/
#define EINT1				(1u)		/*PortD - PIN1*/
#define EINT2				(2u)		/*PortD - PIN2*/
#define EINT3				(3u)		/*PortD - PIN3*/
#define EINT4				(4u)		/*PortE - PIN4*/
#define EINT5				(5u)		/*PortE - PIN5*/
#define EINT6				(6u)		/*PortE - PIN6*/
#define EINT7				(7u)		/*PortE - PIN7*/
#define NOT_AN_EINT         (8u)        /*Default value that returns an "INVALID PARAMETERS" error*/
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: EINT_Enable			: Enables one of the 8 normal external interrupts
 * Input1 	: incpy_u8INTnumber		: Choose which Interrupt to enable		: EINT0-EINT7
 * Input2 	: incpy_u8INTmode		: Choosing the mode of operation		: EINT_Low, EINT_AnyChange, EINT_FallEdge, EINT_RiseEdge
 * Input3 	: incpy_u8PullupEnable	: Enable or Disable Pull up resistor	: EINT_PULLUP, EINT_NOPULLUP
 * Input4 	: inptr_vdISR			: Pointer to the required ISR function	:
 * Return 	:						: Error Status of function
 */
ErrorStatus EINT_Enable(u8 incpy_u8INTnumber, u8 incpy_u8INTmode, u8 incpy_u8PullupEnable, void (*inptr_vdISR) (void));

/* 
 * Function	: EINT_Disable			: Disables one of the 8 normal external interrupts
 * Input1 	: incpy_u8INTnumber		: Choose which Interrupt to disable		: EINT0-EINT7
 * Return 	:						: Error Status of function
 */
ErrorStatus EINT_Disable(u8 incpy_u8INTnumber);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*EINT_INTERFACE_H*/
