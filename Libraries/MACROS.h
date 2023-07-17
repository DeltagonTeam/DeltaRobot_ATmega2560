/**********************************************************************
 * Title		: Universal MACROS File for Commonly Needed Macros
 * Layer		: Libraries
 * Author		: Ashraf Ehab
 * Last Update	: Oct 23, 2022
 **********************************************************************/


#ifndef MACROS_H
#define MACROS_H


/*Defining Macros*/
#define TRUE			(1u)
#define FALSE			(0u)

#ifndef NULL
#define NULL			((void*)0u)
#endif

#define IDLE			(0u)
#define BUSY			(1u)

#define DISABLE			(1u)
#define ENABLE			(2u)

#define BIT_HIGH		(1u)
#define BIT_LOW			(0u)
#define BYTE_HIGH		(0xFF)
#define BYTE_LOW		(0x00)
/*__________________________________________________________________________________________________________________________________________*/


/*Defining Function-like Macros*/
#define RETURN_IF_ERROR(X)		{if (NO_ERROR != X) return X;}
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MACROS_H*/
