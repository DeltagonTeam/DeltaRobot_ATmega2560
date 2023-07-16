#ifndef DIP_INTERFACE_H
#define DIP_INTERFACE_H


/*Include Needed Files*/
#include "DIP_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
    /*DIP Invertion*/
#define DIP_OUTPUT_INVERT       BIT_HIGH
#define DIP_OUTPUT_NOT_INVERT   BIT_LOW

    /*DIP Pull-Up*/
#define DIP_PULLUP          DIO_PIN_PULLUP
#define DIP_NOPULLUP        DIO_PIN_NOPULLUP

    /*DIP Ports*/
#define DIP_PORTA	    DIO_PORTA	  
#define DIP_PORTB	    DIO_PORTB	  
#define DIP_PORTC	    DIO_PORTC	  
#define DIP_PORTD	    DIO_PORTD	  
#define DIP_PORTE	    DIO_PORTE	  
#define DIP_PORTF	    DIO_PORTF	  
#define DIP_PORTG	    DIO_PORTG	  
#define DIP_PORTH	    DIO_PORTH	  
#define DIP_PORTJ	    DIO_PORTJ	  
#define DIP_PORTK	    DIO_PORTK	  
#define DIP_PORTL	    DIO_PORTL	  
#define DIP_NOT_A_PORT  DIO_NOT_A_PORT
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
/*
 * Function	: DIP_Init				    : Initializes the n-way SPST DIP Switch
 * Input1 	: incpy_u8DipPort			: Port that the switch is connected to	: DIP_PORTA - DIP_PORTL
 * Input2 	: incpy_u8NumPins	        : The number of pins of the switch (n)	: 1 - 8
 * Input3 	: incpy_u8PullupEnable		: Enable or Disable Pull up resistors	: DIP_PULLUP, DIP_NOPULLUP
 * Input4 	: incpy_u8OutPutInvert	    : Whether to invert the reading			: DIP_OUTPUT_INVERT, DIP_OUTPUT_NOT_INVERT
 * Return 	:							: Error Status of function
 */
ErrorStatus DIP_Init(u8 incpy_u8DipPort, u8 incpy_u8NumPins, u8 incpy_u8PullupEnable, u8 incpy_u8OutPutInvert);

/*
 * Function	: DIP_Read				    : Reads the n-way SPST DIP Switch
 * Output1	: outptr_u8Reading			: Value of read from the switch 0 - 2^(n)-1, !(0 - 2^(n)-1)
 * Return 	:							: Error Status of function
 */
ErrorStatus DIP_Read(volatile u8* outptr_u8Reading);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*DIP_INTERFACE_H*/
