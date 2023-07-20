/*Include Needed Files*/
#include "MODES_Private.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Public Functions Definitions*/
ErrorStatus MODES_InitModeUpdater(void)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	Loc_ErrorStatusReturn = DIP_Init(DIP_PORTL, 4, DIP_PULLUP, DIP_OUTPUT_INVERT);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	Glob_u8Mode = IDLE_MODE;

	return PB_Init(PB_UPDATE, PB_FALLING, PB_PULLUP, &MODES_UpdateMode);
}

ErrorStatus MODES_IdleMode(void)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	Loc_ErrorStatusReturn = TB6600_Engage(TB_MOTOR0, TB_DIR_CW, 0, &MODES_UpdateCurrentStep0);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = TB6600_Engage(TB_MOTOR1, TB_DIR_CW, 0, &MODES_UpdateCurrentStep1);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = TB6600_Engage(TB_MOTOR2, TB_DIR_CW, 0, &MODES_UpdateCurrentStep2);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	while (IDLE_MODE == Glob_u8Mode)
	{
		/* wait until mode changes */
	}
	

	return NO_ERROR;
}

ErrorStatus MODES_CalibrateMode(void)
{
    ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

    Loc_ErrorStatusReturn = TB6600_Disengage(TB_MOTOR0);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    Loc_ErrorStatusReturn = TB6600_Disengage(TB_MOTOR1);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    Loc_ErrorStatusReturn = TB6600_Disengage(TB_MOTOR2);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);

    Loc_ErrorStatusReturn = PB_Init(PB_CALIBRATE, PB_FALLING, PB_PULLUP, &MODES_Calibrate);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);

    while (CALIBRATE_MODE == Glob_u8Mode)
    {
        /*Do nothing while user is calibrating*/
    }

    return PB_Disable(PB_CALIBRATE);
}

ErrorStatus MODES_ManualMode(void)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	f32 Loc_f32Velocities[3] = {0,0,0};

	JOY_Status Loc_JoyStatusXY = {0,0};
	JOY_Status Loc_JoyStatusZR = {0,0};

	/*Reading Velocities from Joysticks*/
	Loc_ErrorStatusReturn = JOY_Read(JOYSTICK0, &Loc_JoyStatusXY);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = JOY_Read(JOYSTICK1, &Loc_JoyStatusZR);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	Loc_JoyStatusXY.XPercent += Glob_s8OffsetX;
	Loc_JoyStatusXY.YPercent += Glob_s8OffsetY;
	Loc_JoyStatusZR.YPercent += Glob_s8OffsetZ;
	
	Loc_f32Velocities[0] = (f32)Loc_JoyStatusXY.XPercent*MAX_VELOCITY/100;
	Loc_f32Velocities[1] = (f32)Loc_JoyStatusXY.YPercent*MAX_VELOCITY/100;
	Loc_f32Velocities[2] = (f32)Loc_JoyStatusZR.YPercent*MAX_VELOCITY/100;

    return MODES_MovePlatform(Loc_f32Velocities);
}

ErrorStatus MODES_GCodeMode(void)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	u8 Loc_u8GCodeIndex = 0;
	f32 Loc_f32Velocities[3] = {0,0,0};
	f32 Loc_f32Distance[3] = {0,0,0};
	f32 Loc_f32Coords[3] = {0,0,0};
	f32 Loc_f32Thetas[3] = {0,0,0};

	/*Reading Thetas from Angles*/
    Loc_f32Thetas[0] = 0.003141593F * Glob_s16CurrentStep0;
	Loc_f32Thetas[1] = 0.003141593F * Glob_s16CurrentStep1;
	Loc_f32Thetas[2] = 0.003141593F * Glob_s16CurrentStep2;

	/*Calculating Coordinates*/
	Loc_ErrorStatusReturn = KIN_GetCoords(Loc_f32Thetas, Loc_f32Coords);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	for (u8 Loc_u8i = 0; 3 > Loc_u8i; Loc_u8i++)
	{
		Loc_f32Distance[Loc_u8i] = Glob_f32GCode[Loc_u8i][Loc_u8GCodeIndex] - Loc_f32Coords[Loc_u8i];
	}
	
	Loc_f32Velocities[0] = Loc_f32Distance[0]/PLATFORM_ORIGIN_MAX_XY*MAX_VELOCITY;
	Loc_f32Velocities[1] = Loc_f32Distance[1]/PLATFORM_ORIGIN_MAX_XY*MAX_VELOCITY;
	Loc_f32Velocities[2] = Loc_f32Distance[2]/PLATFORM_ORIGIN_MAX_XY*MAX_VELOCITY;

    return MODES_MovePlatform(Loc_f32Velocities);
}
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Definitions*/
ErrorStatus MODES_MovePlatform(f32* inptr_f32Velocities)
{
	ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

	f32 Loc_f32Coords[3] = {0,0,0};
	f32 Loc_f32Thetas[3] = {0,0,0};
	f32 Loc_f32ThetaDots[3] = {0,0,0};

	/*Reading Thetas from Angles*/
    Loc_f32Thetas[0] = 0.003141593F * Glob_s16CurrentStep0;
	Loc_f32Thetas[1] = 0.003141593F * Glob_s16CurrentStep1;
	Loc_f32Thetas[2] = 0.003141593F * Glob_s16CurrentStep2;

	/*Calculating Coordinates*/
	Loc_ErrorStatusReturn = KIN_GetCoords(Loc_f32Thetas, Loc_f32Coords);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	/*Workspace Checks*/
    if (PLATFORM_ORIGIN_MIN_Z > Loc_f32Coords[2] && 0 > inptr_f32Velocities[2])	
    {
		inptr_f32Velocities[2] = 0;
    }
	if (PLATFORM_ORIGIN_MAX_Z < Loc_f32Coords[2] && 0 < inptr_f32Velocities[2])
	{
		inptr_f32Velocities[2] = 0;
	}
    if (PLATFORM_ORIGIN_MAX_XY * PLATFORM_ORIGIN_MAX_XY < (Loc_f32Coords[0] * Loc_f32Coords[0])+(Loc_f32Coords[1] * Loc_f32Coords[1]))
    {
		if ( (0 > Loc_f32Coords[0] && 0 > inptr_f32Velocities[0]) || (0 < Loc_f32Coords[0] && 0 < inptr_f32Velocities[0]) || 0 == Loc_f32Coords[0])
		{
			inptr_f32Velocities[0] = 0;
		}
		if ( (0 > Loc_f32Coords[1] && 0 > inptr_f32Velocities[1]) || (0 < Loc_f32Coords[1] && 0 < inptr_f32Velocities[1]) || 0 == Loc_f32Coords[1])
		{
			inptr_f32Velocities[1] = 0;
		}	
    }

	/*Calculating Theta Dots*/
	Loc_ErrorStatusReturn = KIN_GetThetaDots(Loc_f32Coords, inptr_f32Velocities, Loc_f32Thetas, Loc_f32ThetaDots);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	/*Moving the Motors*/
		/*Moving Motor 0*/
	Glob_u8Motor0Dir = (0 > Loc_f32ThetaDots[0]) ? TB_DIR_CCW : TB_DIR_CW;
	Loc_f32ThetaDots[0] = fabsf(Loc_f32ThetaDots[0]);
	Loc_ErrorStatusReturn = TB6600_Engage(TB_MOTOR0, Glob_u8Motor0Dir, Loc_f32ThetaDots[0]/(2*MATH_PI)*STEPS_PER_REV*GEAR_RATIO*STEPPING_FACTOR, &MODES_UpdateCurrentStep0);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

		/*Moving Motor 1*/
	Glob_u8Motor1Dir = (0 > Loc_f32ThetaDots[1]) ? TB_DIR_CCW : TB_DIR_CW;
	Loc_f32ThetaDots[1] = fabsf(Loc_f32ThetaDots[1]);
	Loc_ErrorStatusReturn = TB6600_Engage(TB_MOTOR1, Glob_u8Motor1Dir, Loc_f32ThetaDots[1]/(2*MATH_PI)*STEPS_PER_REV*GEAR_RATIO*STEPPING_FACTOR, &MODES_UpdateCurrentStep1);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

		/*Moving Motor 2*/
	Glob_u8Motor2Dir = (0 > Loc_f32ThetaDots[2]) ? TB_DIR_CCW : TB_DIR_CW;
	Loc_f32ThetaDots[2] = fabsf(Loc_f32ThetaDots[2]);
	Loc_ErrorStatusReturn = TB6600_Engage(TB_MOTOR2, Glob_u8Motor2Dir, Loc_f32ThetaDots[2]/(2*MATH_PI)*STEPS_PER_REV*GEAR_RATIO*STEPPING_FACTOR, &MODES_UpdateCurrentStep2);
	RETURN_IF_ERROR(Loc_ErrorStatusReturn);

	return NO_ERROR;
}
/*__________________________________________________________________________________________________________________________________________*/


/*Callback Functions Definitions*/
void MODES_Calibrate(void)
{
	Glob_s16CurrentStep0 = 119; /* (0.3738495 * 180 / MATH_PI / (1.8/2) * 5) */
    Glob_s16CurrentStep1 = 119; /* (0.3738495 * 180 / MATH_PI / (1.8/2) * 5) */
	Glob_s16CurrentStep2 = 119; /* (0.3738495 * 180 / MATH_PI / (1.8/2) * 5) */

	JOY_Status Loc_JoyStatusReading;

	JOY_Read(JOYSTICK0,&Loc_JoyStatusReading);
	Glob_s8OffsetX = JOY_INIT_PERCENTX - Loc_JoyStatusReading.XPercent;
	Glob_s8OffsetY = JOY_INIT_PERCENTY - Loc_JoyStatusReading.YPercent;
	JOY_Read(JOYSTICK1,&Loc_JoyStatusReading);
	Glob_s8OffsetZ = JOY_INIT_PERCENTZ - Loc_JoyStatusReading.YPercent;
}

void MODES_UpdateMode(void)
{
	DIP_Read(&Glob_u8Mode);
	
	u8 Loc_SS0 = 0x0;       /*least significant seven segment display*/
    u8 Loc_SS1 = 0x0;       /*most significant seven segment display*/
    u8 Loc_SSCAT= 0x00;     /*the concatenation of both seven segment displays*/

    Loc_SS0 = Glob_u8Mode % 10;
    Loc_SS1 = Glob_u8Mode / 10;

    Loc_SSCAT = Loc_SS0 + (Loc_SS1 << 4);

	DDRA = 0xFF;
    PORTA = Loc_SSCAT;
}

void MODES_UpdateCurrentStep0(void)
{
	if(TB_DIR_CCW == Glob_u8Motor0Dir)
	{
		Glob_s16CurrentStep0--;
	}
	else
	{
		Glob_s16CurrentStep0++;
	}
}

void MODES_UpdateCurrentStep1(void)
{
	if(TB_DIR_CCW == Glob_u8Motor1Dir)
	{
		Glob_s16CurrentStep1--;
	}
	else
	{
		Glob_s16CurrentStep1++;
	}
}

void MODES_UpdateCurrentStep2(void)
{
	if(TB_DIR_CCW == Glob_u8Motor2Dir)
	{
		Glob_s16CurrentStep2--;
	}
	else
	{
		Glob_s16CurrentStep2++;
	}
}

void MODES_StopMoving(void)
{
	Glob_Move = 0;
}