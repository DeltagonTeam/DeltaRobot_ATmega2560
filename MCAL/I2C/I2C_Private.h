/**********************************************************************
 * Title		: I2C Private Header File
 * Layer		:
 * Author		:
 * Last Update	: Dec 12, 2022
 **********************************************************************/

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

/*Include needed files*/
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../REGISTERS.h"
#include "../DIO/DIO_Interface.h"
#include "I2C_Config.h"
#include "I2C_Interface.h"

/*________________________________________________________________________________________________________________________________________________________*/

/*Pre-Build Configuration Macros Definitions*/

/*________________________________________________________________________________________________________________________________________________________*/

/*Pre-Build Configuration Checks*/

/*________________________________________________________________________________________________________________________________________________________*/

/*Private Definitions*/
	/*I2C Register Bits*/
#define TWINT 	(7u)

	/*I2C Control Modes*/
#define START_CONDITION			(0b10100100)
#define RESTART_CONDITION		(0b10110100)
#define START_TRANSMISSION		(0b10000100)
#define START_RECEPTION_ACK		(0b11000100)
#define START_RECEPTION_NACK	(0b10000100)
#define STOP_CONDITION			(0b10010100)

	/*I2C Status Checks*/
#define STATUS_MASK				(0xFC)
#define START_SENT				(0x08)
#define REPEATED_START_SENT		(0x10)
#define SLA_W_ACK				(0x18)
#define SLA_W_NACK				(0x20)
#define DATA_S_ACK				(0x28)
#define DATA_S_NACK				(0x30)
#define ARBITRATION_LOST		(0x38)
#define SLA_R_ACK				(0x40)
#define SLA_R_NACK				(0x48)
#define DATA_R_ACK				(0x50)
#define DATA_R_NACK				(0x58)

/*________________________________________________________________________________________________________________________________________________________*/

/*Private Macros Definitions*/

/*________________________________________________________________________________________________________________________________________________________*/

/*Global Variables Declarations*/

/*________________________________________________________________________________________________________________________________________________________*/

/*Private Functions Declarations*/

#endif /* I2C_PRIVATE_H_*/
