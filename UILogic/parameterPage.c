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
		case PARAMETER_CUTOFF1TEMP_EDIT:
			pProjectMan->cutoff1Temperature = StringToInt32(str); //StringToFloat(str);
			PID_UpdateSetPoint(&(pProjectMan->cutoff1PID), pProjectMan->cutoff1Temperature);
			SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_CUTOFF1TEMP_EDIT, pProjectMan->cutoff1Temperature, 0, 0);
			SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_CUTOFF1TEMP_EDIT, pProjectMan->cutoff1Temperature, 0, 0);
			AT24CXX_Write(CUTOFF1TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff1Temperature, CUTOFF1TEMP_SIZE);
		break;
		case PARAMETER_CUTOFF2TEMP_EDIT:
			pProjectMan->cutoff2Temperature = StringToInt32(str); //StringToFloat(str);
			PID_UpdateSetPoint(&(pProjectMan->cutoff2PID), pProjectMan->cutoff2Temperature);
			SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_CUTOFF2TEMP_EDIT, pProjectMan->cutoff2Temperature, 0, 0);
			SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_CUTOFF2TEMP_EDIT, pProjectMan->cutoff2Temperature, 0, 0);
			AT24CXX_Write(CUTOFF2TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff2Temperature, CUTOFF2TEMP_SIZE);
		break;
		case PARAMETER_CUTOFFTIME_EDIT:
			pProjectMan->cutoffTime = StringToInt32(str);
			AT24CXX_Write(CUTOFFTIME_BASEADDR, (uint8_t*)&pProjectMan->cutoffTime, CUTOFFTIME_SIZE);
		break;
		case PARAMETER_FUSINGTEMP_EDIT:
			pProjectMan->fusingTemperature = StringToInt32(str); //StringToFloat(str);
			SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_FUSINGTEMP_EDIT, pProjectMan->fusingTemperature, 0, 0);
			SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_FUSINGTEMP_EDIT, pProjectMan->fusingTemperature, 0, 0);
			AT24CXX_Write(FUSINGTEMP_BASEADDR, (uint8_t*)&pProjectMan->fusingTemperature, FUSINGTEMP_SIZE);
		break;
		case PARAMETER_FUSINGTIME_EDIT:
			pProjectMan->fusingTime = StringToInt32(str);
			AT24CXX_Write(FUSINGTIME_BASEADDR, (uint8_t*)&pProjectMan->fusingTime, FUSINGTIME_SIZE);
		break;
		case PARAMETER_JOINTTIME_EDIT:
			pProjectMan->jointTime = StringToInt32(str);
			AT24CXX_Write(JOINTTIME_BASEADDR, (uint8_t*)&pProjectMan->jointTime, JOINTTIME_SIZE);
		break;
		default:
			cDebug("parameterPage EDIT error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
