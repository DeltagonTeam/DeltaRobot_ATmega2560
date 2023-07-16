#ifndef MODES_INTERFACE_H
#define MODES_INTERFACE_H


/*Include Needed Files*/
#include "MODES_Config.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Definitions*/
	/*Modes*/
#define IDLE_MODE		(0u)
#define CALIBRATE_MODE 	(1u)
#define MANUAL_MODE 	(2u)
/*__________________________________________________________________________________________________________________________________________*/


/*Global Variables Externs*/
extern volatile u8 Glob_u8Mode;
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
ErrorStatus MODE_InitModeUpdater(void);

ErrorStatus MODE_IdleMode(void);

ErrorStatus MODE_CalibrateMode(void);

ErrorStatus MODE_ManualMode(void);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TB6600_INTERFACE_H*/
