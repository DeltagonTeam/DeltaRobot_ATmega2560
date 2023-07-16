/**********************************************************************
 * Title		: Standard Data Types File
 * Layer		: Libraries
 * Author		: Ashraf Ehab
 * Last Update	: Oct 23, 2022
 **********************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/*Type Definitions*/
typedef unsigned char 			u8;
typedef signed char 			s8;

typedef unsigned short int 		u16;
typedef signed short int 		s16;
typedef unsigned long int 		u32;
typedef signed long int 		s32;
typedef unsigned long long int 	u64;
typedef signed long long int 	s64;

typedef float 					f32;
typedef double 					f64;
typedef long double 			f128;

typedef enum
{
	NO_ERROR,
	INVALID_PARAMETERS,
	INVALID_FUNCTION,
	NULL_POINTER_PASSED,
	POSITION_OUT_OF_RANGE,
	INVALID_CONFIGS,
	FEATURE_NOT_ENABLED,
	INVALID_MODE,
	INVALID_PRESCALER,
	I2C_StartNotSent,
	I2C_RepeatedStartNotSent,
	I2C_No_ACK_Recieved,
	I2C_Arbitration_Lost
}ErrorStatus;


#endif	/* STD_TYPES_H_ */
