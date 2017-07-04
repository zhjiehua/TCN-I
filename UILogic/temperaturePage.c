#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"

#ifdef __cplusplus
extern "C" {
#endif

void temperaturePageButtonProcess(uint16 control_id, uint8  state)
{
	switch(control_id)
	{
		case TEMPERATURE_BACK_BUTTON:
		break;
		case TEMPERATURE_FORWARD_BUTTON:
		break;
		default:
			cDebug("temperaturePage BUTTON error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
