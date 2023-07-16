/**********************************************************************
 * Title		: DIO Program File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Jan 6, 2023
 **********************************************************************/


/*Include Needed Files*/
#include "DIO_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: DIO_PortInit		: Set the Direction of all pins on one of the 4 Ports
 * Input1 	: incpy_u8Port		: Port to Set			: DIO_PORTA-DIO_PORTL
 * Input2 	: incpy_u8Dir		: Direction to set to	: 0-255, DIO_PORT_INPUT, DIO_PORT_OUTPUT
 * Input3 	: incpy_u8InitState	: Initial state of port	: 0-255, DIO_PORT_HIGH, DIO_PORT_LOW, DIO_PORT_PULLUP, DIO_PORT_NOPULLUP
 * Return 	:					: Error Status of function
 */
ErrorStatus DIO_PortInit (u8 incpy_u8Port, u8 incpy_u8Dir, u8 incpy_u8InitState)
{
	switch (incpy_u8Port)
	{
	case DIO_PORTA:		DDRA = incpy_u8Dir;		PORTA = incpy_u8InitState;		break;
	case DIO_PORTB: 	DDRB = incpy_u8Dir;		PORTB = incpy_u8InitState;		break;
	case DIO_PORTC:		DDRC = incpy_u8Dir;		PORTC = incpy_u8InitState;		break;
	case DIO_PORTD: 	DDRD = incpy_u8Dir; 	PORTD = incpy_u8InitState;		break;
	case DIO_PORTE: 	DDRE = incpy_u8Dir; 	PORTE = incpy_u8InitState;		break;
	case DIO_PORTF: 	DDRF = incpy_u8Dir; 	PORTF = incpy_u8InitState;		break;
	case DIO_PORTG: 	DDRG = incpy_u8Dir; 	PORTG = incpy_u8InitState;		break;
	case DIO_PORTH: 	DDRH = incpy_u8Dir; 	PORTH = incpy_u8InitState;		break;
	case DIO_PORTJ: 	DDRJ = incpy_u8Dir; 	PORTJ = incpy_u8InitState;		break;
	case DIO_PORTK: 	DDRK = incpy_u8Dir; 	PORTK = incpy_u8InitState;		break;
	case DIO_PORTL: 	DDRL = incpy_u8Dir; 	PORTL = incpy_u8InitState;		break;
	default:			return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}

/*
 * Function	: DIO_WritePort	: Write an 8-bit Value on one of the 4 Ports
 * Input1 	: incpy_u8Port	: Port to Write on	: DIO_PORTA-DIO_PORTL
 * Input2 	: incpy_u8Val	: Value to write	: 0-255, DIO_PORT_HIGH, DIO_PORT_LOW
 * Return 	:				: Error Status of function
 */
ErrorStatus DIO_WritePort (u8 incpy_u8Port, u8 incpy_u8Val)
{
	switch (incpy_u8Port)
	{
	case DIO_PORTA:		PORTA = incpy_u8Val;	break;
	case DIO_PORTB: 	PORTB = incpy_u8Val;	break;
	case DIO_PORTC:		PORTC = incpy_u8Val;	break;
	case DIO_PORTD: 	PORTD = incpy_u8Val; 	break;
	case DIO_PORTE: 	PORTE = incpy_u8Val; 	break;
	case DIO_PORTF: 	PORTF = incpy_u8Val; 	break;
	case DIO_PORTG: 	PORTG = incpy_u8Val; 	break;
	case DIO_PORTH: 	PORTH = incpy_u8Val; 	break;
	case DIO_PORTJ: 	PORTJ = incpy_u8Val; 	break;
	case DIO_PORTK: 	PORTK = incpy_u8Val; 	break;
	case DIO_PORTL: 	PORTL = incpy_u8Val; 	break;
	default:			return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}

/*
 * Function	: DIO_ReadPort	: Read the Value from one of the 4 Ports
 * Input1 	: incpy_u8Port	: Port to read from				: DIO_PORTA-DIO_PORTL
 * Output1	: outptr_u8Val	: Value inserted on the Port x	: 0-255
 * Return 	:				: Error Status of function
 */
ErrorStatus DIO_ReadPort (u8 incpy_u8Port, volatile u8* outptr_u8Val)
{
	if ( NULL == outptr_u8Val)
	{
		return NULL_POINTER_PASSED;
	}
	switch (incpy_u8Port)
	{
	case DIO_PORTA:		*outptr_u8Val = PINA;	break;
	case DIO_PORTB: 	*outptr_u8Val = PINB;	break;
	case DIO_PORTC:		*outptr_u8Val = PINC;	break;
	case DIO_PORTD: 	*outptr_u8Val = PIND;	break;
	case DIO_PORTE: 	*outptr_u8Val = PINE;	break;
	case DIO_PORTF: 	*outptr_u8Val = PINF;	break;
	case DIO_PORTG: 	*outptr_u8Val = PING;	break;
	case DIO_PORTH: 	*outptr_u8Val = PINH;	break;
	case DIO_PORTJ: 	*outptr_u8Val = PINJ;	break;
	case DIO_PORTK: 	*outptr_u8Val = PINK;	break;
	case DIO_PORTL: 	*outptr_u8Val = PINL;	break;
	default:			return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}

/*
 * Function	: DIO_PinInit		: Set the Direction of one of the 32 Pins (Pin xn)
 * Input1 	: incpy_u8Port		: Port x				: DIO_PORTA-DIO_PORTL
 * Input2 	: incpy_u8Pin		: Pin n					: DIO_PIN0-DIO_PIN7
 * Input3	: incpy_u8Dir 		: Direction to set to	: DIO_PIN_INPUT, DIO_PIN_OUTPUT
 * Input4 	: incpy_u8InitState	: Initial state of pin	: DIO_PIN_HIGH, DIO_PIN_LOW, DIO_PIN_PULLUP, DIO_PIN_NOPULLUP
 * Return 	:					: Error Status of function
 */
ErrorStatus DIO_PinInit (u8 incpy_u8Port, u8 incpy_u8Pin, u8 incpy_u8Dir, u8 incpy_u8InitState)
{
	if ((DIO_NOT_A_PIN <= incpy_u8Pin) || (DIO_PIN_OUTPUT < incpy_u8Dir) || (DIO_PIN_HIGH < incpy_u8InitState) || ((DIO_PORTG == incpy_u8Port) && (DIO_PIN5 < incpy_u8Pin)))
	{
		return INVALID_PARAMETERS;
	}
	switch (incpy_u8Port)
	{
	case DIO_PORTA:		MAKE_BIT(DDRA, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTA, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTB:		MAKE_BIT(DDRB, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTB, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTC:		MAKE_BIT(DDRC, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTC, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTD:		MAKE_BIT(DDRD, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTD, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTE:		MAKE_BIT(DDRE, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTE, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTF:		MAKE_BIT(DDRF, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTF, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTG:		MAKE_BIT(DDRG, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTG, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTH:		MAKE_BIT(DDRH, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTH, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTJ:		MAKE_BIT(DDRJ, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTJ, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTK:		MAKE_BIT(DDRK, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTK, incpy_u8Pin, incpy_u8InitState);		break;
	case DIO_PORTL:		MAKE_BIT(DDRL, incpy_u8Pin, incpy_u8Dir);	MAKE_BIT(PORTL, incpy_u8Pin, incpy_u8InitState);		break;
	default:			return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}

/*
 * Function	: DIO_WritePin	: Write a 1-bit Value on one of the 32 Pins (Pin xn)
 * Input1 	: incpy_u8Port	: Port x		: DIO_PORTA-DIO_PORTL
 * Input2 	: incpy_u8Pin	: Pin n			: DIO_PIN0-DIO_PIN7
 * Input3	: incpy_u8Val 	: Value to write: DIO_PIN_LOW, DIO_PIN_HIGH
 * Return 	:				: Error Status of function
 */
ErrorStatus DIO_WritePin (u8 incpy_u8Port, u8 incpy_u8Pin, u8 incpy_u8Val)
{
	if ((DIO_NOT_A_PIN <= incpy_u8Pin) || (DIO_PIN_HIGH < incpy_u8Val) || ((DIO_PORTG == incpy_u8Port) && (DIO_PIN5 < incpy_u8Pin)))
	{
		return INVALID_PARAMETERS;
	}
	switch (incpy_u8Port)
	{
	case DIO_PORTA:		MAKE_BIT(PORTA, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTB:		MAKE_BIT(PORTB, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTC:		MAKE_BIT(PORTC, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTD:		MAKE_BIT(PORTD, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTE:		MAKE_BIT(PORTE, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTF:		MAKE_BIT(PORTF, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTG:		MAKE_BIT(PORTG, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTH:		MAKE_BIT(PORTH, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTJ:		MAKE_BIT(PORTJ, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTK:		MAKE_BIT(PORTK, incpy_u8Pin, incpy_u8Val);		break;
	case DIO_PORTL:		MAKE_BIT(PORTL, incpy_u8Pin, incpy_u8Val);		break;
	default:			return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}

/*
 * Function	: DIO_ReadPin	: Get the Value on one of the 32 Pins (Pin xn)
 * Input1 	: incpy_u8Port	: Port x				: DIO_PORTA-DIO_PORTL
 * Input2 	: incpy_u8Pin	: Pin n					: DIO_PIN0-DIO_PIN7
 * Output1	: outptr_u8Val	: Value inserted on Pin	: DIO_PIN_HIGH, DIO_PIN_LOW
 * Return 	:				: Error Status of function
 */
ErrorStatus DIO_ReadPin (u8 incpy_u8Port, u8 incpy_u8Pin, u8* outptr_u8Val)
{
	if (NULL == outptr_u8Val)
	{
		return NULL_POINTER_PASSED;
	}
	if (DIO_NOT_A_PIN <= incpy_u8Pin || ((DIO_PORTG == incpy_u8Port) && (DIO_PIN5 < incpy_u8Pin)))
	{
		return INVALID_PARAMETERS;
	}
	switch (incpy_u8Port)
	{
	case DIO_PORTA:		*outptr_u8Val =  GET_BIT(PINA, incpy_u8Pin);	break;
	case DIO_PORTB: 	*outptr_u8Val =  GET_BIT(PINB, incpy_u8Pin);	break;
	case DIO_PORTC:		*outptr_u8Val =  GET_BIT(PINC, incpy_u8Pin);	break;
	case DIO_PORTD: 	*outptr_u8Val =  GET_BIT(PIND, incpy_u8Pin);	break;
	case DIO_PORTE: 	*outptr_u8Val =  GET_BIT(PINE, incpy_u8Pin);	break;
	case DIO_PORTF: 	*outptr_u8Val =  GET_BIT(PINF, incpy_u8Pin);	break;
	case DIO_PORTG: 	*outptr_u8Val =  GET_BIT(PING, incpy_u8Pin);	break;
	case DIO_PORTH: 	*outptr_u8Val =  GET_BIT(PINH, incpy_u8Pin);	break;
	case DIO_PORTJ: 	*outptr_u8Val =  GET_BIT(PINJ, incpy_u8Pin);	break;
	case DIO_PORTK: 	*outptr_u8Val =  GET_BIT(PINK, incpy_u8Pin);	break;
	case DIO_PORTL: 	*outptr_u8Val =  GET_BIT(PINL, incpy_u8Pin);	break;
	default:			return INVALID_PARAMETERS;
	}
	return NO_ERROR;
}
