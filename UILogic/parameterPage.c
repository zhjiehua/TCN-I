#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../HARDWARE/24CXX/24cxx.h"
#include "../DCMotor/DCMotor.h"

#ifdef __cplusplus
extern "C" {
#endif

void parameterPageButtonProcess(uint16 control_id, uint8  state)
{
	switch(control_id)
	{
		case PARAMETER_AUTO_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_PARAMETER_AUTO;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, PARAMETER_AUTO_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, PARAMETER_AUTO_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case PARAMETER_RESET_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_PARAMETER_RESET;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, PARAMETER_RESET_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, PARAMETER_RESET_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}	
		break;
		
		case PARAMETER_BACK_BUTTON:
		break;
		case PARAMETER_FORWARD_BUTTON:
		break;
		default:
			cDebug("parameterPage BUTTON error!\n");
		break;
	}
}

void parameterPageEditProcess(uint16 control_id, uint8 *str)
{
	switch(control_id)
	{
		case PARAMETER_CUTOFFTEMP_EDIT:
			pProjectMan->cutoff1Temperature = StringToFloat(str);
			pProjectMan->cutoff2Temperature = pProjectMan->cutoff1Temperature;
		break;
		case PARAMETER_CUTOFFTIME_EDIT:
		break;
		case PARAMETER_FUSINGTEMP_EDIT:
			pProjectMan->fusingTemperature = StringToFloat(str);
		break;
		case PARAMETER_FUSINGTIME_EDIT:
		break;
		case PARAMETER_JOINTTIME_EDIT:
		break;
		default:
			cDebug("parameterPage EDIT error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
