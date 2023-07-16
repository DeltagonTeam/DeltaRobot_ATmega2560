#ifndef PB_INTERFACE_H
#define PB_INTERFACE_H


/*Include Needed Files*/
#include "PB_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*Push Button Modes*/
#define PB_LOW		    EINT_LOW	
#define PB_TOGGLE		EINT_TOGGLE	
#define PB_FALLING	    EINT_FALLING
#define PB_RISING		EINT_RISING	

    /*Internal Pull up Resistor Enable and Disable*/
#define PB_PULLUP		EINT_PULLUP	
#define PB_NOPULLUP		EINT_NOPULLUP
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
ErrorStatus PB_Init(u8 incpy_u8PB, u8 incpy_u8PBmode, u8 incpy_u8PullupEnable, void (*inptr_vdISR) (void));

ErrorStatus PB_Deinit(u8 incpy_u8PB);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*PB_INTERFACE_H*/
