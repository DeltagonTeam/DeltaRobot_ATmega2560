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
#define GCODE_MODE 		(3u)
/*__________________________________________________________________________________________________________________________________________*/


/*Global Variables Externs*/
extern volatile u8 Glob_u8Mode;
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Declarations*/
ErrorStatus MODES_InitModeUpdater(void);

ErrorStatus MODES_IdleMode(void);

ErrorStatus MODES_CalibrateMode(void);

ErrorStatus MODES_ManualMode(void);

ErrorStatus MODES_GCodeMode(void);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*TB6600_INTERFACE_H*/
