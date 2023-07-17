/**********************************************************************
 * Title	:	Global Interrupt Control File
 * Layer	:	MCAL
 * Author	:	Ashraf Ehab
 * Last Update:	March 5, 2023
 **********************************************************************/


#ifndef GLOB_INT_H
#define GLOB_INT_H


/*Include Needed Files*/
#include "../Libraries/BIT_MATH.h"
#include "REGISTERS.h"
/*__________________________________________________________________________________________________________________________________________*/


/* Defining Needed Bits*/
#define GLOB_INT_ENABLE	    (7u)
/*__________________________________________________________________________________________________________________________________________*/


/*Defining Function-like Macros*/
#define ENABLE_GLOB_INT(void)		SET_BIT(SREG,GLOB_INT_ENABLE)
#define DISABLE_GLOB_INT(void)		CLR_BIT(SREG,GLOB_INT_ENABLE)
#define GET_GLOB_INT(void)			GET_BIT(SREG,GLOB_INT_ENABLE)
#define MAKE_GLOB_INT(Val)		    MAKE_BIT(SREG,GLOB_INT_ENABLE,Val)
/*__________________________________________________________________________________________________________________________________________*/


#endif /*GLOB_INT_H*/
