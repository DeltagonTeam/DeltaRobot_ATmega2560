#ifndef PB_CONFIG_H
#define PB_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../MCAL/EINT/EINT_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Choosing Push Button External Interrupts*/
#define PB0	    EINT2
#define PB1	    EINT4
#define PB2	    EINT5
#define PB3	    NOT_AN_EINT
/*__________________________________________________________________________________________________________________________________________*/


#endif /*PB_CONFIG_H*/
