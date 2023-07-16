/**********************************************************************
 * Title		: TB6600 Stepper Motor Driver Configuration Header File
 * Layer		:
 * Author		:
 * Last Update	: Dec 8, 2022
 **********************************************************************/


#ifndef TB6600_CONFIG_H
#define TB6600_CONFIG_H


/*Include Needed Files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/TMR1/TMR1_Interface.h"
#include "../../MCAL/TMR3/TMR3_Interface.h"
#include "../../MCAL/TMR4/TMR4_Interface.h"
#include "../../MCAL/TMR5/TMR5_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Choosing TMR Prescalar for Motor PWMs*/
#define TB_PRESCALER    TMR1_PRESCALER64

/*Choosing Motor Pins*/
    /*Motor 0 ports*/
#define TB0_DIR_PORT	DIO_PORTH
#define TB0_ENA_PORT	DIO_PORTH
    /*Motor 0 pins*/
#define TB0_DIR_PIN		DIO_PIN5
#define TB0_ENA_PIN		DIO_PIN3

    /*Motor 1 ports*/
#define TB1_DIR_PORT	DIO_PORTB
#define TB1_ENA_PORT	DIO_PORTJ
    /*Motor 1 pins*/
#define TB1_DIR_PIN		DIO_PIN4
#define TB1_ENA_PIN		DIO_PIN1   

    /*Motor 2 ports*/
#define TB2_DIR_PORT	DIO_PORTB
#define TB2_ENA_PORT	DIO_PORTB
    /*Motor 2 pins*/
#define TB2_DIR_PIN		DIO_PIN7
#define TB2_ENA_PIN		DIO_PIN5

    /*Motor 3 ports*/
#define TB3_DIR_PORT	DIO_NOT_A_PORT
#define TB3_ENA_PORT	DIO_NOT_A_PORT
    /*Motor 3 pins*/
#define TB3_DIR_PIN		DIO_NOT_A_PIN
#define TB3_ENA_PIN		DIO_NOT_A_PIN
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TB6600_CONFIG_H*/
