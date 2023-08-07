#ifndef MODES_CONFIG_H
#define MODES_CONFIG_H


/*Include Needed Files*/
	/*Libraries*/
#include <math.h>
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/MACROS.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/MATH/MATH_Interface.h"

	/*HAL*/
#include "../../HAL/JOY/JOY_Interface.h"
#include "../../HAL/TB6600/TB6600_Interface.h"
#include "../../HAL/PB/PB_Interface.h"
#include "../../HAL/DIP/DIP_Interface.h"

	/*APP*/
#include "../KIN/KIN_Interface.h"
#include "../FEEDBACK/FEEDBACK_Interface.h"
/*__________________________________________________________________________________________________________________________________________*/


/*Choose Push Buttons*/
#define PB_UPDATE		PB1
#define PB_CALIBRATE	PB2
#define PB_USE			PB0

/*Defining Coordinate Arrays for G Code Mode*/
#define NO_OF_COORDS 7
static f32 Glob_f32GCode_XCoords[NO_OF_COORDS] = {0, 	60, 	60, 	-60, 	-60,	60,		0};
static f32 Glob_f32GCode_YCoords[NO_OF_COORDS] = {0, 	60, 	-60,	-60, 	60, 	60,		0};
static f32 Glob_f32GCode_ZCoords[NO_OF_COORDS] = {-375, -375, 	-375, 	-375, 	-375, 	-375,	-375};
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MODES_CONFIG_H*/
