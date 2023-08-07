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
/*__________________________________________________________________________________________________________________________________________*/


/*Private Definitions*/
	/*Movement Definitions*/
#define GEAR_RATIO 			(5.0F)
#define MAX_VELOCITY 		(240.0F)
#define STEPPING_FACTOR 	(2.0F)
#define STEP_ANGLE_DEG		(1.8F)
#define STEPS_PER_REV		(200.0F)
#define RADS_PER_STEP		(0.003141593F)	/* (STEP_ANGLE_DEG/STEPPING_FACTOR) * (MATH_PI / 180) / GEAR_RATIO) */

	/*The Joysticks Calibration Angles*/
#define JOY_INIT_PERCENTX 	0      /*Middle Position of Joy Stick in Axis X*/
#define JOY_INIT_PERCENTY 	0      /*Middle Position of Joy Stick in Axis Y*/
#define JOY_INIT_PERCENTZ 	0      /*Middle Position of Joy Stick in Axis Z*/
/*__________________________________________________________________________________________________________________________________________*/


/*Private Functions Declarations*/
ErrorStatus MODES_MovePlatform(const f32* inptr_f32Velocities, const f32* inptr_f32Thetas);
/*__________________________________________________________________________________________________________________________________________*/


/*Callback Functions*/
void MODES_Calibrate(void);

void MODES_UpdateMode(void);

void MODES_UpdateCurrentStep0(void);

void MODES_UpdateCurrentStep1(void);

void MODES_UpdateCurrentStep2(void);
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MODES_PRIVATE_H*/