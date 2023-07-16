#ifndef ERROR_INTERFACE_H
#define ERROR_INTERFACE_H


/*Include Needed Files*/
#include "ERROR_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Macros*/
#define ERRORU_IF_ERROR(X)		{if (NO_ERROR != X) ERRORu(X);}
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
void ERRORu(ErrorStatus incpy_ErrorStatus);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*ERROR_INTERFACE_H*/
