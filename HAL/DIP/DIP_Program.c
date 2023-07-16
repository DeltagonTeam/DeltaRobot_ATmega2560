/*Include Needed Files*/
#include "DIP_Private.h"


/*Public Functions Definitions*/
ErrorStatus DIP_Init(u8 incpy_u8DipPort, u8 incpy_u8NumPins, u8 incpy_u8PullupEnable, u8 incpy_u8OutPutInvert)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	if (0 == incpy_u8NumPins)
	{
		return INVALID_PARAMETERS;
	}
	
	for (u8 Loc_u8PinCounter = 0; incpy_u8NumPins > Loc_u8PinCounter; Loc_u8PinCounter++)
	{
		Loc_ErrorStatusReturn = DIO_PinInit(incpy_u8DipPort, Loc_u8PinCounter, DIO_PIN_INPUT, incpy_u8PullupEnable);
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
	}

	Glob_u8ReadingMask = ~(0xFF << incpy_u8NumPins);
	Glob_u8OutPutInvert = incpy_u8OutPutInvert;
	Glob_u8DipPort = incpy_u8DipPort;

	return NO_ERROR;
}

ErrorStatus DIP_Read(volatile u8* outptr_u8Reading)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	Loc_ErrorStatusReturn = DIO_ReadPort(Glob_u8DipPort, outptr_u8Reading);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	if (DIP_OUTPUT_INVERT == Glob_u8OutPutInvert)
	{
		*outptr_u8Reading = ~(*outptr_u8Reading);
	}

	*outptr_u8Reading &= Glob_u8ReadingMask;

	return NO_ERROR;
}
