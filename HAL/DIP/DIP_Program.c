/*Include Needed Files*/
#include "DIP_Private.h"


/*Public Functions Definitions*/
/*
 * Function	: DIP_Init				    : Initializes the n-way SPST DIP Switch
 * Input1 	: incpy_u8DipPort			: Port that the switch is connected to	: DIP_PORTA - DIP_PORTL
 * Input2 	: incpy_u8NumPins	        : The number of pins of the switch (n)	: 1 - 8
 * Input3 	: incpy_u8PullupEnable		: Enable or Disable Pull up resistors	: DIP_PULLUP, DIP_NOPULLUP
 * Input4 	: incpy_u8OutPutInvert	    : Whether to invert the reading			: DIP_OUTPUT_INVERT, DIP_OUTPUT_NOT_INVERT
 * Return 	:							: Error Status of function
 */
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

/*
 * Function	: DIP_Read				    : Reads the n-way SPST DIP Switch
 * Output1	: outptr_u8Reading			: Value of read from the switch 0 - 2^(n)-1, !(0 - 2^(n)-1)
 * Return 	:							: Error Status of function
 */
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
