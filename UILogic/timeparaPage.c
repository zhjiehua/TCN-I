#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../HARDWARE/24CXX/24cxx.h"

#ifdef __cplusplus
extern "C" {
#endif

void timeparaPageButtonProcess(uint16 control_id, uint8 state)
{
	switch(control_id)
	{
		case TIMEPARA_BACK_BUTTON:
		break;
		default:
			cDebug("timeparaPage BUTTON error!\n");
		break;
	}
}
	
void timeparaPageEditProcess(uint16 control_id, uint8 *str)
{
	switch(control_id)
	{
		case TIMEPARA_CLAMP1DELAY_EDIT:
			pProjectMan->clamp1Delay = StringToInt32(str);
			AT24CXX_Write(CLAMP1DELAY_BASEADDR, (uint8_t*)&pProjectMan->clamp1Delay, 4);
		break;
		case TIMEPARA_CLAMP2DELAY_EDIT:
			pProjectMan->clamp2Delay = StringToInt32(str);
			AT24CXX_Write(CLAMP2DELAY_BASEADDR, (uint8_t*)&pProjectMan->clamp2Delay, 4);
		break;
		case TIMEPARA_CUTOFF1DELAY_EDIT:
			pProjectMan->cutoff1Delay = StringToInt32(str);
			AT24CXX_Write(CUTOFF1DELAY_BASEADDR, (uint8_t*)&pProjectMan->cutoff1Delay, 4);
		break;
		case TIMEPARA_CUTOFF2DELAY_EDIT:
			pProjectMan->cutoff2Delay = StringToInt32(str);
			AT24CXX_Write(CUTOFF2DELAY_BASEADDR, (uint8_t*)&pProjectMan->cutoff2Delay, 4);
		break;
		case TIMEPARA_CUTOFFRETURN_EDIT:
			pProjectMan->cutoffReturnDelay = StringToInt32(str);
			AT24CXX_Write(CUTOFFRETURN_BASEADDR, (uint8_t*)&pProjectMan->cutoffReturnDelay, 4);
		break;
		case TIMEPARA_CUTOFF_EDIT:
			pProjectMan->cutoffTime = StringToInt32(str);
			AT24CXX_Write(CUTOFFTIME_BASEADDR, (uint8_t*)&pProjectMan->cutoffTime, 4);
		break;
		case TIMEPARA_FUSING_EDIT:
			pProjectMan->fusingTime = StringToInt32(str);
			AT24CXX_Write(FUSINGTIME_BASEADDR, (uint8_t*)&pProjectMan->fusingTime, 4);
		break;
		case TIMEPARA_JOINT_EDIT:
			pProjectMan->jointTime = StringToInt32(str);
			AT24CXX_Write(JOINTTIME_BASEADDR, (uint8_t*)&pProjectMan->jointTime, 4);
		break;
		case TIMEPARA_HEATINGUPDELAY_EDIT:
			pProjectMan->heatingUpDelay = StringToInt32(str);
			AT24CXX_Write(HEATINGUPDELAY_BASEADDR, (uint8_t*)&pProjectMan->heatingUpDelay, 4);
		break;
		case TIMEPARA_HEATINGDOWNDELAY_EDIT:
			pProjectMan->heatingDownDelay = StringToInt32(str);
			AT24CXX_Write(HEATINGDOWNDELAY_BASEADDR, (uint8_t*)&pProjectMan->heatingDownDelay, 4);
		break;
		default:
			cDebug("timeparaPage BUTTON error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
