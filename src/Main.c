/**********************************************************************
 * Title		: Main file
 * Layer		: APP
 * Author		:
 * Last Update	:
 **********************************************************************/


/*Include Needed Files*/
#include "../APP/MODES/MODES_Interface.h"
#include "../APP/ERROR/ERROR_Interface.h"


/*Main*/
int main(void)
{
	/*SetUp*/
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	Loc_ErrorStatusReturn = JOY_Init(JOYSTICK0);
	ERRORU_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = JOY_Init(JOYSTICK1);
	ERRORU_IF_ERROR(Loc_ErrorStatusReturn);

	Loc_ErrorStatusReturn = TB6600_Init(TB_MOTOR0);
	ERRORU_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = TB6600_Init(TB_MOTOR1);
	ERRORU_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = TB6600_Init(TB_MOTOR2);
	ERRORU_IF_ERROR(Loc_ErrorStatusReturn);

	Loc_ErrorStatusReturn = KIN_Init();
	ERRORU_IF_ERROR(Loc_ErrorStatusReturn);

	Loc_ErrorStatusReturn = MODES_InitModeUpdater();
	ERRORU_IF_ERROR(Loc_ErrorStatusReturn);

	/*Loop*/
	while(1)
	{
		switch (Glob_u8Mode)
		{
		case IDLE_MODE:
			Loc_ErrorStatusReturn = MODES_IdleMode();
			ERRORU_IF_ERROR(Loc_ErrorStatusReturn);
			break;

		case CALIBRATE_MODE:
			Loc_ErrorStatusReturn = MODES_CalibrateMode();
			ERRORU_IF_ERROR(Loc_ErrorStatusReturn);
			break;

		case MANUAL_MODE:
			Loc_ErrorStatusReturn = MODES_ManualMode();
			ERRORU_IF_ERROR(Loc_ErrorStatusReturn);
			break;

		case GCODE_MODE:
			Loc_ErrorStatusReturn = MODES_GCodeMode();
			ERRORU_IF_ERROR(Loc_ErrorStatusReturn);
			break;

		default:
			ERRORu(INVALID_MODE);
			break;
		}
	}

	return 0;
}