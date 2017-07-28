#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../HARDWARE/24CXX/24cxx.h"

#ifdef __cplusplus
extern "C" {
#endif

void tempparaPageButtonProcess(uint16 control_id, uint8 state)
{
	switch(control_id)
	{
		case TEMPPARA_CUTOFF1TEMPCRL_BUTTON:
			pProjectMan->cutoff1TempControlFlag = state;
		break;
		case TEMPPARA_CUTOFF2TEMPCRL_BUTTON:
			pProjectMan->cutoff2TempControlFlag = state;
		break;
		case TEMPPARA_FUSINGTEMPCRL_BUTTON:
			pProjectMan->fusingTempControlFlag = state;
		break;
		case TEMPPARA_BACK_BUTTON:
		break;
		default:
			cDebug("tempparaPage BUTTON error!\n");
		break;
	}
}

void tempparaPageEditProcess(uint16 control_id, uint8 *str)
{
	switch(control_id)
	{
		case TEMPPARA_CUTOFF1KP_EDIT:
			pProjectMan->cutoff1PID.Proportion = StringToInt32(str)/10.0;
			AT24CXX_Write(CUTOFF1KP_BASEADDR, (uint8_t*)&pProjectMan->cutoff1PID.Proportion, 4);
		break;
		case TEMPPARA_CUTOFF1KI_EDIT:
			pProjectMan->cutoff1PID.Integral = StringToInt32(str)/10.0;
			AT24CXX_Write(CUTOFF1KI_BASEADDR, (uint8_t*)&pProjectMan->cutoff1PID.Integral, 4);
		break;
		case TEMPPARA_CUTOFF1KD_EDIT:
			pProjectMan->cutoff2PID.Derivative = StringToInt32(str)/10.0;
			AT24CXX_Write(CUTOFF2KD_BASEADDR, (uint8_t*)&pProjectMan->cutoff1PID.Derivative, 4);
		break;
		case TEMPPARA_CUTOFF2KP_EDIT:
			pProjectMan->cutoff2PID.Proportion = StringToInt32(str)/10.0;
			AT24CXX_Write(CUTOFF2KP_BASEADDR, (uint8_t*)&pProjectMan->cutoff2PID.Proportion, 4);
		break;
		case TEMPPARA_CUTOFF2KI_EDIT:
			pProjectMan->cutoff1PID.Integral = StringToInt32(str)/10.0;
			AT24CXX_Write(CUTOFF2KI_BASEADDR, (uint8_t*)&pProjectMan->cutoff2PID.Integral, 4);
		break;
		case TEMPPARA_CUTOFF2KD_EDIT:
			pProjectMan->cutoff2PID.Derivative = StringToInt32(str)/10.0;
			AT24CXX_Write(CUTOFF2KD_BASEADDR, (uint8_t*)&pProjectMan->cutoff2PID.Derivative, 4);
		break;
		case TEMPPARA_CUTOFF1TEMP_EDIT:
			pProjectMan->cutoff1Temperature = StringToInt32(str);
			//PID_UpdateSetPoint(&(pProjectMan->cutoff1PID), pProjectMan->cutoff1Temperature);
			AT24CXX_Write(CUTOFF1TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff1Temperature, 4);
		break;
		case TEMPPARA_CUTOFF1HOLDINGTEMP_EDIT:
			pProjectMan->cutoff1HoldingTemperature = StringToInt32(str);
			PID_UpdateSetPoint(&(pProjectMan->cutoff1PID), pProjectMan->cutoff1HoldingTemperature);
			AT24CXX_Write(CUTOFF1HOLDINGTEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff1HoldingTemperature, 4);
		break;
		case TEMPPARA_CUTOFF2TEMP_EDIT:
			pProjectMan->cutoff2Temperature = StringToInt32(str);
			//PID_UpdateSetPoint(&(pProjectMan->cutoff2PID), pProjectMan->cutoff2Temperature);
			AT24CXX_Write(CUTOFF2TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff2Temperature, 4);
		break;
		case TEMPPARA_CUTOFF2HOLDINGTEMP_EDIT:
			pProjectMan->cutoff2HoldingTemperature = StringToInt32(str);
			PID_UpdateSetPoint(&(pProjectMan->cutoff2PID), pProjectMan->cutoff2HoldingTemperature);
			AT24CXX_Write(CUTOFF2HOLDINGTEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff2HoldingTemperature, 4);
		break;
		case TEMPPARA_FUSINGTEMP_EDIT:
			pProjectMan->fusingTemperature = StringToInt32(str);
			AT24CXX_Write(FUSINGTEMP_BASEADDR, (uint8_t*)&pProjectMan->fusingTemperature, 4);
		break;
		case TEMPPARA_FUSINGHOLDINGTEMP_EDIT:
			pProjectMan->fusingHoldingTemperature = StringToInt32(str);
			AT24CXX_Write(FUSINGHOLDINGTEMP_BASEADDR, (uint8_t*)&pProjectMan->fusingHoldingTemperature, 4);
		break;
		default:
			cDebug("tempparaPage EDIT error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
