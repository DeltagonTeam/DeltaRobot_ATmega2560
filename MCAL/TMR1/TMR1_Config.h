/**********************************************************************
 * Title		: Timer 1 Configuration Header File
 * Layer		: MCAL
 * Author		: Ashraf Ehab, Ali Azmy
 * Last Update	: Mar 2, 2023
 **********************************************************************/


#ifndef TMR1_CONFIG_H
#define TMR1_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../REGISTERS.h"
#include "../MCU_Config.h"
#include "../Glob_Int.h"
#include "../DIO/DIO_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Micro-Controller Setup*/
#define EXTERNAL_CLK_T1		(1000u)			/* define External Clock on Pin T1 in KHz if used */
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TMR1_CONFIG_H*/
