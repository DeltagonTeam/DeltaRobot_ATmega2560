#ifndef MODES_PRIVATE_H
#define MODES_PRIVATE_H


/*Include Needed Files*/
#include "MODES_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Global Variables Definitions*/
volatile u8 Glob_u8Mode = 0;
static volatile s16 Glob_s16CurrentStep0 = 0;
static volatile s16 Glob_s16CurrentStep1 = 0;
static volatile s16 Glob_s16CurrentStep2 = 0;
static u8 Glob_u8Motor0Dir = TB_DIR_CW;
static u8 Glob_u8Motor1Dir = TB_DIR_CW;
static u8 Glob_u8Motor2Dir = TB_DIR_CW;
static volatile s8 Glob_s8OffsetX = 0;
static volatile s8 Glob_s8OffsetY = 0;
static volatile s8 Glob_s8OffsetZ = 0;
static volatile u8 Glob_Move = 1;
static f32 Glob_f32GCode[3][20];
/*__________________________________________________________________________________________________________________________________________*/


/*Private Definitions*/
	/*Movement Definitions*/
#define GEAR_RATIO 			(5.0F)
#define MAX_VELOCITY 		(60.0F)
#define STEPPING_FACTOR 	(2.0F)
#define STEPS_PER_REV		(200.0F)

	/*The Joysticks Calibration Angles*/
#define JOY_INIT_PERCENTX 	0      /*Middle Position of Joy Stick in Axis X*/
#define JOY_INIT_PERCENTY 	0      /*Middle Position of Joy Stick in Axis Y*/
#define JOY_INIT_PERCENTZ 	0      /*Middle Position of Joy Stick in Axis Z*/
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Declarations*/
ErrorStatus MODE_MovePlatform(f32* inptr_f32Velocities);
/*__________________________________________________________________________________________________________________________________________*/


/*Callback Functions*/
void MODE_Calibrate(void);

void MODE_UpdateMode(void);

void MODE_UpdateCurrentStep0(void);

void MODE_UpdateCurrentStep1(void);

void MODE_UpdateCurrentStep2(void);

void MODE_StopMoving(void);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MODES_PRIVATE_H*/