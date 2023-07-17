/**********************************************************************
 * Title		: FEEDBACK Program File
 * Layer		:
 * Author		:
 * Last Update	: Dec 12, 2022
 **********************************************************************/


/*Include Needed Files*/
#include "FEEDBACK_Private.h"


/*Public Functions Definitions*/
/*
 * Function	: FEEDBACK_Init		: a public function that initializes the potentiometers
 * Return 	: ErrorStatus		: Error Status of function
 */
ErrorStatus FEEDBACK_Init(void)
{
    ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;
    Loc_ErrorStatusReturn = POT_Init(FEEDBACK_CHANNEL0);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = POT_Init(FEEDBACK_CHANNEL1);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
	Loc_ErrorStatusReturn = POT_Init(FEEDBACK_CHANNEL2);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    //init the 3 limit swiches with the function that resets the 

    return NO_ERROR;
}

/*
 * Function	: FEEDBACK_ReadCurrentThetas	: a public function that calculates the anglular positions of the driver links
 * Output1	: outptr_f32Thetas	            : an array with the anglular positions of the driver links
 * Return 	: ErrorStatus		            : Error Status of function
 */
ErrorStatus FEEDBACK_ReadCurrentThetas(f32* outptr_f32Thetas)
{
    ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

    Loc_ErrorStatusReturn = POT_Read(FEEDBACK_CHANNEL0, &outptr_f32Thetas[0]);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    outptr_f32Thetas[0] += Glob_f32Offset0;

	Loc_ErrorStatusReturn = POT_Read(FEEDBACK_CHANNEL1, &outptr_f32Thetas[1]);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    outptr_f32Thetas[1] += Glob_f32Offset1;

	Loc_ErrorStatusReturn = POT_Read(FEEDBACK_CHANNEL2, &outptr_f32Thetas[2]);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    outptr_f32Thetas[2] += Glob_f32Offset2;

    return NO_ERROR;
}

/*
 * Function	: FEEDBACK_GetCorrection    	: a public function that calculates the offset of the anglular positions of the driver links
 * Return 	: ErrorStatus		            : Error Status of function
 */
ErrorStatus FEEDBACK_GetCorrection(void)
{
    ErrorStatus Loc_ErrorStatusReturn = NO_ERROR;

    Loc_ErrorStatusReturn = POT_Read(FEEDBACK_CHANNEL0, &Glob_f32Offset0);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    Glob_f32Offset0 = INIT_ANGLE0 - Glob_f32Offset0;

    Loc_ErrorStatusReturn = POT_Read(FEEDBACK_CHANNEL1, &Glob_f32Offset1);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    Glob_f32Offset1 = INIT_ANGLE1 - Glob_f32Offset1;

    Loc_ErrorStatusReturn = POT_Read(FEEDBACK_CHANNEL2, &Glob_f32Offset2);
    RETURN_IF_ERROR(Loc_ErrorStatusReturn);
    Glob_f32Offset2 = INIT_ANGLE2 - Glob_f32Offset2;

    return NO_ERROR;
}
