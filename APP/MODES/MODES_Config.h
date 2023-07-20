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

/*Range to ignore velocity fluctuations at*/
#define MODES_SKIP_RANGE 	(1.0F)
/*__________________________________________________________________________________________________________________________________________*/


#endif /*MODES_CONFIG_H*/
