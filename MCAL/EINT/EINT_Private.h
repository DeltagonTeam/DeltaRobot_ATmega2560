/**********************************************************************
 * Title		: External Interrupt Private Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab
 * Last Update	: Jan 30, 2023
 **********************************************************************/


#ifndef EINT_PRIVATE_H
#define EINT_PRIVATE_H


/*Include needed files*/
#include "EINT_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Pre-Build Configuration Macros Definitions*/
#define DO_INCLUDE		(1u)
#define DO_NOT_INCLUDE 	(2u)
/*__________________________________________________________________________________________________________________________________________*/


/*Private Macros Definitions*/
#define __INTR_ATTRS	used,externally_visible
/*__________________________________________________________________________________________________________________________________________*/


/*Global Variables Definitions*/
#if DO_INCLUDE == EINT_INCLUDE_INT0
	static void (* Globptr_vdEINT0) (void) = NULL;
#endif

#if DO_INCLUDE == EINT_INCLUDE_INT1
	static void (* Globptr_vdEINT1) (void) = NULL;
#endif

#if DO_INCLUDE == EINT_INCLUDE_INT2
	static void (* Globptr_vdEINT2) (void) = NULL;
#endif

#if DO_INCLUDE == EINT_INCLUDE_INT3
	static void (* Globptr_vdEINT3) (void) = NULL;
#endif

#if DO_INCLUDE == EINT_INCLUDE_INT4
	static void (* Globptr_vdEINT4) (void) = NULL;
#endif

#if DO_INCLUDE == EINT_INCLUDE_INT5
	static void (* Globptr_vdEINT5) (void) = NULL;
#endif

#if DO_INCLUDE == EINT_INCLUDE_INT6
	static void (* Globptr_vdEINT6) (void) = NULL;
#endif

#if DO_INCLUDE == EINT_INCLUDE_INT7
	static void (* Globptr_vdEINT7) (void) = NULL;
#endif
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Declarations*/
/* 
 * Function	: EINT_EnableCheck		: Checks if the given external interrupt is enabled
 * Input1 	: incpy_u8INTnumber		: Choose which Interrupt to check		: EINT0-EINT7
 * Return 	:						: Error Status of function
 */
ErrorStatus EINT_EnableCheck(u8 incpy_u8INTnumber);
/*__________________________________________________________________________________________________________________________________________*/


/*Interrupt Service Routines Declarations*/
/* 
 * Function	: Interupt Service Routine for External Interrupt 0	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT0
	void __vector_1(void)__attribute__( (signal, __INTR_ATTRS) );
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 1	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT1
	void __vector_2(void)__attribute__( (signal, __INTR_ATTRS) );
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 2	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT2
	void __vector_3(void)__attribute__( (signal, __INTR_ATTRS) );
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 3	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT3
	void __vector_4(void)__attribute__( (signal, __INTR_ATTRS) );
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 4	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT4
	void __vector_5(void)__attribute__( (signal, __INTR_ATTRS) );
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 5	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT5
	void __vector_6(void)__attribute__( (signal, __INTR_ATTRS) );
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 6	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT6
	void __vector_7(void)__attribute__( (signal, __INTR_ATTRS) );
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 7	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT7
	void __vector_8(void)__attribute__( (signal, __INTR_ATTRS) );
#endif
/*__________________________________________________________________________________________________________________________________________*/


#endif /*EINT_PRIVATE_H*/
