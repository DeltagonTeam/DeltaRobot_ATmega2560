/*Include Needed Files*/
#include "ERROR_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


void ERRORu(ErrorStatus incpy_ErrorStatus)
{
    u8 Loc_SS0 = 0x0;       /*least significant seven segment display*/
    u8 Loc_SS1 = 0x0;       /*most significant seven segment display*/
    u8 Loc_SSCAT= 0x00;     /*the concatenation of both seven segment displays*/

    if (NO_ERROR == incpy_ErrorStatus)
    {
        return;
    }

    SREG &= ~( 1<< (7u));   /*disabling all maskable interrupts*/

    TCCR1B &= 0xF8;		    /*Turning Timer off by removing pre-scaler*/
    TCCR4B &= 0xF8;		    /*Turning Timer off by removing pre-scaler*/
    TCCR5B &= 0xF8;		    /*Turning Timer off by removing pre-scaler*/

    Loc_SS0 = incpy_ErrorStatus % 10;
    Loc_SS1 = incpy_ErrorStatus / 10;

    Loc_SSCAT = Loc_SS0 + (Loc_SS1 << 4);

    DDRA = 0xFF;            /*Setting the seven segmen display port direction to output*/
    PORTA = Loc_SSCAT;      /*Displaying the erroru on the seven segment displays*/

    while (1)
    {
        /*Waiting for user to Reset*/
    }
}
