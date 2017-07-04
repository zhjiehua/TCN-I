#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"

#ifdef __cplusplus
extern "C" {
#endif

void mainPageButtonProcess(uint16 control_id, uint8 state)
{
	switch(control_id)
	{
		case MAIN_CLEAR_BUTTON:
			//清零总产量
			break;
		case MAIN_MANUAL_BUTTON:
			break;
		default:
			cDebug("mainPage BUTTON error!\n");
			break;
	}
}

#ifdef __cplusplus
}
#endif
