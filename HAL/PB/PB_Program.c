/*Include Needed Files*/
#include "PB_Private.h"


/*Public Functions Definitions*/
ErrorStatus PB_Init(u8 incpy_u8PB, u8 incpy_u8PBmode, u8 incpy_u8PullupEnable, void (*inptr_vdISR) (void))
{
	return EINT_Enable(incpy_u8PB, EINT_FALLING, EINT_PULLUP, inptr_vdISR);
}

ErrorStatus PB_Deinit(u8 incpy_u8PB)
{
	return EINT_Disable(incpy_u8PB);
}
