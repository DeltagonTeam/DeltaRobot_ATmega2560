/**********************************************************************
 * Title		: External Interrupt Program File
 * Layer		: MCAL
 * Author		: Ashraf Ehab
 * Last Update	: Jan 30, 2023
 **********************************************************************/


/*Include Needed Files*/
#include "EINT_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
/* 
 * Function	: EINT_Enable			: Enables one of the 8 normal external interrupts
 * Input1 	: incpy_u8INTnumber		: Choose which Interrupt to enable		: EINT0-EINT7
 * Input2 	: incpy_u8INTmode		: Choosing the mode of operation		: EINT_Low, EINT_AnyChange, EINT_FallEdge, EINT_RiseEdge
 * Input3 	: incpy_u8PullupEnable	: Enable or Disable Pull up resistor	: EINT_PULLUP, EINT_NOPULLUP
 * Input4 	: inptr_vdISR			: Pointer to the required ISR function
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus EINT_Enable(u8 incpy_u8INTnumber, u8 incpy_u8INTmode, u8 incpy_u8PullupEnable, void (*inptr_vdISR) (void))
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	Loc_ErrorStatusReturn = EINT_EnableCheck(incpy_u8INTnumber);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	if (NULL == inptr_vdISR)
	{
		return NULL_POINTER_PASSED;
	}
	CLR_BIT(EIMSK,incpy_u8INTnumber);	/*Disable Interrupt while editing configurations*/

	/*First 4 are on PortD and configured using register EICRA*/
	if (EINT3 >= incpy_u8INTnumber)
	{
		Loc_ErrorStatusReturn = DIO_PinInit (DIO_PORTD, incpy_u8INTnumber, DIO_PIN_INPUT, incpy_u8PullupEnable);	/*Set Pin Direction as input*/
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);
		
		incpy_u8INTnumber <<= 1;		/*Multiply Interrupt number by 2 to align with the control register bits*/
		/*Set Interrupt Mode*/
		switch (incpy_u8INTmode)
		{
		case EINT_LOW:
			CLR_BIT(EICRA, incpy_u8INTnumber);		/*ISCn0 = 0*/
			CLR_BIT(EICRA, (incpy_u8INTnumber+1));	/*ISCn1 = 0*/
			break;

		case EINT_TOGGLE:
			SET_BIT(EICRA, incpy_u8INTnumber);		/*ISCn0 = 1*/
			CLR_BIT(EICRA, (incpy_u8INTnumber+1));	/*ISCn1 = 0*/
			break;

		case EINT_FALLING:
			CLR_BIT(EICRA, incpy_u8INTnumber);		/*ISCn0 = 0*/
			SET_BIT(EICRA, (incpy_u8INTnumber+1));	/*ISCn1 = 1*/
			break;

		case EINT_RISING:
			SET_BIT(EICRA, incpy_u8INTnumber);		/*ISCn0 = 1*/
			SET_BIT(EICRA, (incpy_u8INTnumber+1));	/*ISCn1 = 1*/
			break;

		default:
			return INVALID_PARAMETERS;
		}
		incpy_u8INTnumber >>= 1;		/*Return Interrupt number to original value*/
	}
	/*Second 4 are on PortE and configured using register EICRB*/
	else if (EINT7 >= incpy_u8INTnumber)
	{
		Loc_ErrorStatusReturn = DIO_PinInit (DIO_PORTE, incpy_u8INTnumber, DIO_PIN_INPUT, incpy_u8PullupEnable);	/*Set Pin Direction as input*/
		RETURN_IF_ERROR(Loc_ErrorStatusReturn);

		/*Subtract 4 from Interrupt number then Multiply by 2 to align with the control register bits*/
		incpy_u8INTnumber -= 4;
		incpy_u8INTnumber <<= 1;
		/*Set Interrupt Mode*/
		switch (incpy_u8INTmode)
		{
		case EINT_LOW:
			CLR_BIT(EICRB, incpy_u8INTnumber);		/*ISCn0 = 0*/
			CLR_BIT(EICRB, (incpy_u8INTnumber+1));	/*ISCn1 = 0*/
			break;

		case EINT_TOGGLE:
			SET_BIT(EICRB, incpy_u8INTnumber);		/*ISCn0 = 1*/
			CLR_BIT(EICRB, (incpy_u8INTnumber+1));	/*ISCn1 = 0*/
			break;

		case EINT_FALLING:
			CLR_BIT(EICRB, incpy_u8INTnumber);		/*ISCn0 = 0*/
			SET_BIT(EICRB, (incpy_u8INTnumber+1));	/*ISCn1 = 1*/
			break;

		case EINT_RISING:
			SET_BIT(EICRB, incpy_u8INTnumber);		/*ISCn0 = 1*/
			SET_BIT(EICRB, (incpy_u8INTnumber+1));	/*ISCn1 = 1*/
			break;

		default:
			return INVALID_PARAMETERS;
		}
		/*Return Interrupt number to original value*/
		incpy_u8INTnumber >>= 1;
		incpy_u8INTnumber += 4;
	}
	else
	{
		return INVALID_PARAMETERS;
	}

	/*Place the User's ISR Location in the respective Global variable to be called from the original ISR function*/
	switch (incpy_u8INTnumber)
	{
	#if DO_INCLUDE == EINT_INCLUDE_INT0
		case EINT0:	Globptr_vdEINT0 = inptr_vdISR;	break;
	#endif
	#if DO_INCLUDE == EINT_INCLUDE_INT1
		case EINT1:	Globptr_vdEINT1 = inptr_vdISR;	break;
	#endif
	#if DO_INCLUDE == EINT_INCLUDE_INT2
		case EINT2:	Globptr_vdEINT2 = inptr_vdISR;	break;
	#endif
	#if DO_INCLUDE == EINT_INCLUDE_INT3
		case EINT3:	Globptr_vdEINT3 = inptr_vdISR;	break;
	#endif
	#if DO_INCLUDE == EINT_INCLUDE_INT4
		case EINT4:	Globptr_vdEINT4 = inptr_vdISR;	break;
	#endif
	#if DO_INCLUDE == EINT_INCLUDE_INT5
		case EINT5:	Globptr_vdEINT5 = inptr_vdISR;	break;
	#endif
	#if DO_INCLUDE == EINT_INCLUDE_INT6
		case EINT6:	Globptr_vdEINT6 = inptr_vdISR;	break;
	#endif
	#if DO_INCLUDE == EINT_INCLUDE_INT7
		case EINT7:	Globptr_vdEINT7 = inptr_vdISR;	break;
	#endif
	default:	/*Do Nothing*/						break;
	}

	SET_BIT(EIFR,incpy_u8INTnumber);	/*Clearing Interrupt flag by writing a logical one to it*/
	SET_BIT(EIMSK, incpy_u8INTnumber);	/*Enable Required External Interrupt*/
	ENABLE_GLOB_INT(void);

	return NO_ERROR;
}

/* 
 * Function	: EINT_Disable			: Disables one of the 8 normal external interrupts
 * Input1 	: incpy_u8INTnumber		: Choose which Interrupt to disable		: EINT0-EINT7
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus EINT_Disable(u8 incpy_u8INTnumber)
{
	CLR_BIT(EIMSK, incpy_u8INTnumber);	/*Disable Required External Interrupt*/
	return NO_ERROR;
}
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Definitions*/
/* 
 * Function	: EINT_EnableCheck		: Checks if the given external interrupt is enabled
 * Input1 	: incpy_u8INTnumber		: Choose which Interrupt to check		: EINT0-EINT7
 * Return 	: ErrorStatus			: Error Status of function
 */
ErrorStatus EINT_EnableCheck(u8 incpy_u8INTnumber)
{
	switch (incpy_u8INTnumber)
	{
	case EINT0:
		#if DO_INCLUDE != EINT_INCLUDE_INT0
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	case EINT1:
		#if DO_INCLUDE != EINT_INCLUDE_INT1
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	case EINT2:
		#if DO_INCLUDE != EINT_INCLUDE_INT2
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	case EINT3:
		#if DO_INCLUDE != EINT_INCLUDE_INT3
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	case EINT4:
		#if DO_INCLUDE != EINT_INCLUDE_INT4
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	case EINT5:
		#if DO_INCLUDE != EINT_INCLUDE_INT5
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	case EINT6:
		#if DO_INCLUDE != EINT_INCLUDE_INT6
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	case EINT7:
		#if DO_INCLUDE != EINT_INCLUDE_INT7
			return FEATURE_NOT_ENABLED;
		#endif
		break;
	
	default:
		break;
	}
	return NO_ERROR;
}
/*__________________________________________________________________________________________________________________________________________*/


/*Interrupt Service Routines Definitions*/
/* 
 * Function	: Interupt Service Routine for External Interrupt 0	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT0
	void __vector_1(void)
	{
		if (NULL != Globptr_vdEINT0)
		{
			Globptr_vdEINT0();
		}
	}
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 1	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT1
	void __vector_2(void)
	{
		if (NULL != Globptr_vdEINT1)
		{
			Globptr_vdEINT1();
		}
	}
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 2	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT2
	void __vector_3(void)
	{
		if (NULL != Globptr_vdEINT2)
		{
			Globptr_vdEINT2();
		}
	}
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 3	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT3
	void __vector_4(void)
	{
		if (NULL != Globptr_vdEINT3)
		{
			Globptr_vdEINT3();
		}
	}
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 4	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT4
	void __vector_5(void)
	{
		if (NULL != Globptr_vdEINT4)
		{
			Globptr_vdEINT4();
		}
	}
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 5	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT5
	void __vector_6(void)
	{
		if (NULL != Globptr_vdEINT5)
		{
			Globptr_vdEINT5();
		}
	}
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 6	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT6
	void __vector_7(void)
	{
		if (NULL != Globptr_vdEINT6)
		{
			Globptr_vdEINT6();
		}
	}
#endif

/* 
 * Function	: Interupt Service Routine for External Interrupt 7	: Calls a function given by the user
 */
#if DO_INCLUDE == EINT_INCLUDE_INT7
	void __vector_8(void)
	{
		if (NULL != Globptr_vdEINT7)
		{
			Globptr_vdEINT7();
		}
	}
#endif
