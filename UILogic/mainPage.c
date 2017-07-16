#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../HARDWARE/24CXX/24cxx.h"

#ifdef __cplusplus
extern "C" {
#endif

void tips1PageButtonProcess(uint16 control_id, uint8 state)
{
	switch(control_id)
	{
		case TIPS_OK_BUTTON:
			pProjectMan->tipsBuzzeFlag = 0;
			break;
		default:
			cDebug("tips1Page BUTTON error!\n");
		break;
	}
}
	
void logoPageButtonProcess(uint16 control_id, uint8 state)
{
	switch(control_id)
	{
		case LOGO_START_BUTTON:
			SetTextInt32(MAINPAGE_INDEX, MAIN_OUTPUT_EDIT, pProjectMan->totalOutput, 0, 0);
			break;
		default:
			cDebug("logoPage BUTTON error!\n");
		break;
	}
}
	
void mainPageButtonProcess(uint16 control_id, uint8 state)
{
	switch(control_id)
	{
		case MAIN_CLEAR_BUTTON:
			//清零总产量
			pProjectMan->totalOutput = 0;
			SetTextInt32(MAINPAGE_INDEX, MAIN_OUTPUT_EDIT, 0, 0, 0);
			AT24CXX_Write(TOTALOUTPUT_BASEADDR, (uint8_t*)&pProjectMan->totalOutput, 4);
			break;
		case MAIN_SETUP_BUTTON:
			break;
		default:
			cDebug("mainPage BUTTON error!\n");
			break;
	}
}

#ifdef __cplusplus
}
#endif
