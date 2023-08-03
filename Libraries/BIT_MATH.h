/**********************************************************************
 * Title		: BIT-WISE MATH Functions File
 * Layer		: Libraries
 * Author		: Khaled Mohsen
 * Last Update	: Oct 23, 2022
 **********************************************************************/


#ifndef BIT_MATH_H
#define BIT_MATH_H


/*Function-like Macros for Logical Operations on Variables or Registers*/
    /*Bits*/
#define SET_BIT(Var,BitNo) 						(Var) = (Var)|(1<<(BitNo))
#define CLR_BIT(Var,BitNo) 						(Var) = (Var) & ~(1<<(BitNo))
#define TOGGLE_BIT(Var,BitNo) 					(Var) = (Var) ^ (1<<(BitNo))
#define GET_BIT(Var,BitNo) 						(((Var) >> (BitNo)) & 1)
#define MAKE_BIT(Var,BitNo,Val)					(Var) = (((Var) & (~(1<<(BitNo)))) | ((Val)<<(BitNo)))

    /*Concatenating*/
#define CONC_BIT(A7,A6,A5,A4,A3,A2,A1,A0) 		CONC_HELP(A7,A6,A5,A4,A3,A2,A1,A0) //text replacement first
#define CONC_HELP(A7,A6,A5,A4,A3,A2,A1,A0)  	0b##A7##A6##A5##A4##A3##A2##A1##A0 //concatenate then

    /*Bytes*/
#define SET_BYTE(Var) 							Var = 0xFF
#define CLR_BYTE(Var) 							Var = 0x00

    /*Nibbles*/
#define SET_NIBBLE_LOW(Var) 					Var = Var | 0x0F
#define SET_NIBBLE_HIGH(Var) 					Var = Var | 0xF0
#define CLEAR_NIBBLE_LOW(Var) 					Var = (Var & (0xF0))
#define CLEAR_NIBBLE_HIGH(Var) 					Var = (Var & (0x0F))
/*__________________________________________________________________________________________________________________________________________*/


#endif /*BIT_MATH_H*/
