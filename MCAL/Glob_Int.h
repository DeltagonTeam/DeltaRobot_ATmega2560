/**********************************************************************
 * Title	:	Global Interrupt Control File
 * Layer	:	MCAL
 * Author	:	Ashraf Ehab
 * Last Update:	March 5, 2023
 **********************************************************************/

#ifndef MCAL_GLOB_INT_H
#define MCAL_GLOB_INT_H

#include "../Libraries/BIT_MATH.h"
#include "REGISTERS.h"

#define INT_FLAG		(7u)

#define ENABLE_GLOB_INT(void)		SET_BIT(SREG,INT_FLAG)
#define DISABLE_GLOB_INT(void)		CLR_BIT(SREG,INT_FLAG)
#define GET_GLOB_INT(void)			GET_BIT(SREG,INT_FLAG)
#define MAKE_GLOB_INT(Val)		    MAKE_BIT(SREG,INT_FLAG,Val)

#endif /*MCAL_GLOB_INT_H*/
