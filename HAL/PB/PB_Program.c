/*Include Needed Files*/
#include "PB_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/*
 * Function	: PB_Init				    : Initializes the given push button
 * Input1 	: incpy_u8PB	        	: Push button number					: PB0 - PB3
 * Input2 	: incpy_u8PBmode	        : The mode of the push button			: PB_Low, PB_AnyChange, PB_FallEdge, PB_RiseEdge
 * Input3 	: incpy_u8PullupEnable		: Enable or Disable Pull up resistor	: PB_PULLUP, PB_NOPULLUP
 * Input4 	: inptr_vdISR				: Pointer to the required ISR function	:
 * Return 	: ErrorStatus				: Error Status of function
 */
ErrorStatus PB_Init(u8 incpy_u8PB, u8 incpy_u8PBmode, u8 incpy_u8PullupEnable, void (*inptr_vdISR) (void))
{
	return EINT_Enable(incpy_u8PB, EINT_FALLING, EINT_PULLUP, inptr_vdISR);
}

/*
 * Function	: PB_Disable				: Disables the given push button
 * Input1 	: incpy_u8PB	        	: Push button number					: PB0 - PB3
 * Return 	: ErrorStatus				: Error Status of function
 */
ErrorStatus PB_Disable(u8 incpy_u8PB)
{
	return EINT_Disable(incpy_u8PB);
}
