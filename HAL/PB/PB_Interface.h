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
/*
 * Function	: PB_Init				    : Initializes the given push button
 * Input1 	: incpy_u8PB	        	: Push button number					: PB0 - PB3
 * Input2 	: incpy_u8PBmode	        : The mode of the push button			: PB_Low, PB_AnyChange, PB_FallEdge, PB_RiseEdge
 * Input3 	: incpy_u8PullupEnable		: Enable or Disable Pull up resistor	: PB_PULLUP, PB_NOPULLUP
 * Input4 	: inptr_vdISR				: Pointer to the required ISR function	:
 * Return 	:							: Error Status of function
 */
ErrorStatus PB_Init(u8 incpy_u8PB, u8 incpy_u8PBmode, u8 incpy_u8PullupEnable, void (*inptr_vdISR) (void));

/*
 * Function	: PB_Disable				: Disables the given push button
 * Input1 	: incpy_u8PB	        	: Push button number					: PB0 - PB3
 * Return 	:							: Error Status of function
 */
ErrorStatus PB_Disable(u8 incpy_u8PB);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*PB_INTERFACE_H*/
