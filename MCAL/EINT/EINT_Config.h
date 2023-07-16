/**********************************************************************
 * Title		: External Interrupt Configuration Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab
 * Last Update	: Jan 30, 2023
 **********************************************************************/


#ifndef EINT_CONFIG_H
#define EINT_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../REGISTERS.h"
#include "../Glob_Int.h"
#include "../DIO/DIO_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Include Needed Functions*/
    /*Options for each:- DO_INCLUDE , DO_NOT_INCLUDE*/
#define EINT_INCLUDE_INT0		DO_NOT_INCLUDE
#define EINT_INCLUDE_INT1		DO_NOT_INCLUDE
#define EINT_INCLUDE_INT2		DO_INCLUDE
#define EINT_INCLUDE_INT3		DO_INCLUDE
#define EINT_INCLUDE_INT4		DO_INCLUDE
#define EINT_INCLUDE_INT5		DO_INCLUDE
#define EINT_INCLUDE_INT6		DO_NOT_INCLUDE
#define EINT_INCLUDE_INT7		DO_NOT_INCLUDE
/*__________________________________________________________________________________________________________________________________________*/


#endif /*EINT_CONFIG_H*/
