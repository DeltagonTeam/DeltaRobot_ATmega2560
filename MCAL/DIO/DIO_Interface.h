/**********************************************************************
 * Title		: DIO Interface Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Jan 6, 2023
 **********************************************************************/


#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


/*Include Needed Files*/
#include "DIO_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*DIO Ports*/
#define DIO_PORTA	    (0u)
#define DIO_PORTB	    (1u)
#define DIO_PORTC	    (2u)
#define DIO_PORTD	    (3u)
#define DIO_PORTE	    (4u)
#define DIO_PORTF	    (5u)
#define DIO_PORTG	    (6u)
#define DIO_PORTH	    (7u)
#define DIO_PORTJ	    (8u)
#define DIO_PORTK	    (9u)
#define DIO_PORTL	    (10u)
#define DIO_NOT_A_PORT  (11u)

    /*DIO Pins*/
#define DIO_PIN0	    (0u)
#define DIO_PIN1	    (1u)
#define DIO_PIN2	    (2u)
#define DIO_PIN3	    (3u)
#define DIO_PIN4	    (4u)
#define DIO_PIN5	    (5u)
#define DIO_PIN6	    (6u)
#define DIO_PIN7	    (7u)
#define DIO_NOT_A_PIN   (8u)

    /*DIO Directions*/
#define DIO_PORT_INPUT		BYTE_LOW
#define DIO_PORT_OUTPUT		BYTE_HIGH
#define DIO_PIN_INPUT		BIT_LOW
#define DIO_PIN_OUTPUT		BIT_HIGH

    /*DIO Values*/
#define DIO_PORT_LOW		BYTE_LOW
#define DIO_PORT_HIGH		BYTE_HIGH
#define DIO_PIN_LOW			BIT_LOW
#define DIO_PIN_HIGH		BIT_HIGH

    /*DIO Pull-Up*/
#define DIO_PORT_NOPULLUP		BYTE_LOW
#define DIO_PORT_PULLUP			BYTE_HIGH
#define DIO_PIN_NOPULLUP		BIT_LOW
#define DIO_PIN_PULLUP			BIT_HIGH
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/* 
 * Function	: DIO_PortInit		: Set the Direction of all pins on one of the 4 Ports
 * Input1 	: incpy_u8Port		: Port to Set			: DIO_PORTA - DIO_PORTL
 * Input2 	: incpy_u8Dir		: Direction to set to	: 0-255, DIO_PORT_INPUT, DIO_PORT_OUTPUT
 * Input3 	: incpy_u8InitState	: Initial state of port	: 0-255, DIO_PORT_HIGH, DIO_PORT_LOW, DIO_PORT_PULLUP, DIO_PORT_NOPULLUP
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus DIO_PortInit (u8 incpy_u8Port, u8 incpy_u8Dir, u8 incpy_u8InitState);

/*
 * Function	: DIO_WritePort	    : Write an 8-bit Value on one of the 4 Ports
 * Input1 	: incpy_u8Port	    : Port to Write on	: DIO_PORTA - DIO_PORTL
 * Input2 	: incpy_u8Val	    : Value to write	: 0-255, DIO_PORT_HIGH, DIO_PORT_LOW
 * Return 	: ErrorStatus	    : Error Status of function
 */
ErrorStatus DIO_WritePort (u8 incpy_u8Port, u8 incpy_u8Val);

/*
 * Function	: DIO_ReadPort	    : Read the Value from one of the 4 Ports
 * Input1 	: incpy_u8Port	    : Port to read from				: DIO_PORTA - DIO_PORTL
 * Output1	: outptr_u8Val	    : Value inserted on the Port x	: 0-255
 * Return 	: ErrorStatus	    : Error Status of function
 */
ErrorStatus DIO_ReadPort (u8 incpy_u8Port, volatile u8* outptr_u8Val);

/*
 * Function	: DIO_PinInit		: Set the Direction of one of the 32 Pins (Pin xn)
 * Input1 	: incpy_u8Port		: Port x				: DIO_PORTA - DIO_PORTL
 * Input2 	: incpy_u8Pin		: Pin n					: DIO_PIN0-DIO_PIN7
 * Input3	: incpy_u8Dir 		: Direction to set to	: DIO_PIN_INPUT, DIO_PIN_OUTPUT
 * Input4 	: incpy_u8InitState	: Initial state of pin	: DIO_PIN_HIGH, DIO_PIN_LOW, DIO_PIN_PULLUP, DIO_PIN_NOPULLUP
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus DIO_PinInit (u8 incpy_u8Port, u8 incpy_u8Pin, u8 incpy_u8Dir, u8 incpy_u8InitState);

/*
 * Function	: DIO_WritePin	    : Write a 1-bit Value on one of the 32 Pins (Pin xn)
 * Input1 	: incpy_u8Port	    : Port x		: DIO_PORTA - DIO_PORTL
 * Input2 	: incpy_u8Pin	    : Pin n			: DIO_PIN0-DIO_PIN7
 * Input3	: incpy_u8Val 	    : Value to write: DIO_PIN_LOW, DIO_PIN_HIGH
 * Return 	: ErrorStatus	    : Error Status of function
 */
ErrorStatus DIO_WritePin (u8 incpy_u8Port, u8 incpy_u8Pin, u8 incpy_u8Val);

/*
 * Function	: DIO_ReadPin	    : Get the Value on one of the 32 Pins (Pin xn)
 * Input1 	: incpy_u8Port	    : Port x				: DIO_PORTA - DIO_PORTL
 * Input2 	: incpy_u8Pin	    : Pin n					: DIO_PIN0-DIO_PIN7
 * Output1	: outptr_u8Val	    : Value inserted on Pin	: DIO_PIN_HIGH, DIO_PIN_LOW
 * Return 	: ErrorStatus	    : Error Status of function
 */
ErrorStatus DIO_ReadPin (u8 incpy_u8Port, u8 incpy_u8Pin, u8* outptr_u8Val);


#endif /*DIO_INTERFACE_H*/
