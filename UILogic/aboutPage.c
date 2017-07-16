#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../HARDWARE/24CXX/24cxx.h"
#include "../HARDWARE/DCMotor/DCMotor.h"
#include "../HardwareCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

void aboutPageButtonProcess(uint16 control_id, uint8  state)
{
	switch(control_id)
	{
		default:
			cDebug("aboutPage BUTTON error!\n");
		break;
	}
}

//void aboutPageEditProcess(uint16 control_id, uint8 *str)
//{
//	switch(control_id)
//	{	   
//		default:
//			cDebug("aboutPage EDIT error!\n");
//		break;
//	}
//}

#ifdef __cplusplus
}
#endif
