#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../HARDWARE/24CXX/24cxx.h"
#include "../HARDWARE/DCMotor/DCMotor.h"
#include "../HardwareCommon.h"
#include "NTCResistor/NTCResistor.h"

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void setupPageButtonProcess(uint16 control_id, uint8  state)
{
	switch(control_id)
	{
		case SETUP_MANUAL_BUTTON:
		break;
		case SETUP_STATUS_BUTTON:
		{
			SetTextInt32(STATUSPAGE_INDEX, STATUS_TEMPCUTOFF1_EDIT, adcTemp[0].temperature, 0, 0);
			SetTextInt32(STATUSPAGE_INDEX, STATUS_TEMPCUTOFF2_EDIT, adcTemp[1].temperature, 0, 0);
			SetTextInt32(STATUSPAGE_INDEX, STATUS_TEMPFUSING_EDIT, adcTemp[2].temperature, 0, 0);
			pProjectMan->inStatusPageFlag = 1;
		}
		break;
		case SETUP_TEMPPARA_BUTTON:
		{
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF1KP_EDIT, pProjectMan->cutoff1PID.Proportion*10, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF1KI_EDIT, pProjectMan->cutoff1PID.Integral*10, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF1KD_EDIT, pProjectMan->cutoff1PID.Derivative*10, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF2KP_EDIT, pProjectMan->cutoff2PID.Proportion*10, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF2KI_EDIT, pProjectMan->cutoff2PID.Integral*10, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF2KD_EDIT, pProjectMan->cutoff2PID.Derivative*10, 0, 0);
			
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF1TEMP_EDIT, pProjectMan->cutoff1Temperature, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF2TEMP_EDIT, pProjectMan->cutoff2Temperature, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_FUSINGTEMP_EDIT, pProjectMan->fusingTemperature, 0, 0);
			SetTextInt32(TEMPPARAPAGE_INDEX, TEMPPARA_FUSINGHOLDINGTEMP_EDIT, pProjectMan->fusingHoldingTemperature, 0, 0);
			
			SetButtonValue(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF1TEMPCRL_BUTTON, pProjectMan->cutoff1TempControlFlag);
			SetButtonValue(TEMPPARAPAGE_INDEX, TEMPPARA_CUTOFF2TEMPCRL_BUTTON, pProjectMan->cutoff2TempControlFlag);
			SetButtonValue(TEMPPARAPAGE_INDEX, TEMPPARA_FUSINGTEMPCRL_BUTTON, pProjectMan->fusingTempControlFlag);
		}
		break;
		case SETUP_TIMEPARA_BUTTON:
		{
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_CLAMP1DELAY_EDIT, pProjectMan->clamp1Delay, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_CLAMP2DELAY_EDIT, pProjectMan->clamp2Delay, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_CUTOFF1DELAY_EDIT, pProjectMan->cutoff1Delay, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_CUTOFF2DELAY_EDIT, pProjectMan->cutoff2Delay, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_CUTOFFRETURN_EDIT, pProjectMan->cutoffReturnDelay, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_CUTOFF_EDIT, pProjectMan->cutoffTime, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_FUSING_EDIT, pProjectMan->fusingTime, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_JOINT_EDIT, pProjectMan->jointTime, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_HEATINGUPDELAY_EDIT, pProjectMan->heatingUpDelay, 0, 0);
			SetTextInt32(TIMEPARAPAGE_INDEX, TIMEPARA_HEATINGDOWNDELAY_EDIT, pProjectMan->heatingDownDelay, 0, 0);
		}
		break;
		case SETUP_MOTORPARA_BUTTON:
		{
			SetTextInt32(MOTORPARAPAGE_INDEX, MOTORPARA_DISLOCATERETURN_EDIT, pProjectMan->dislocateReturn, 0, 0);
			SetTextInt32(MOTORPARAPAGE_INDEX, MOTORPARA_DISLOCATESPEED_EDIT, pProjectMan->dislocateSpeed, 0, 0);
			SetTextInt32(MOTORPARAPAGE_INDEX, MOTORPARA_HEATINGUPSPEED_EDIT, pProjectMan->heatingUpSpeed, 0, 0);
			SetTextInt32(MOTORPARAPAGE_INDEX, MOTORPARA_HEATINGDOWNSPEED_EDIT, pProjectMan->heatingDownSpeed, 0, 0);
			SetTextInt32(MOTORPARAPAGE_INDEX, MOTORPARA_CUROFF1HEATVOL_EDIT, pProjectMan->cutoff1HeatingVoltage, 0, 0);
			SetTextInt32(MOTORPARAPAGE_INDEX, MOTORPARA_CUROFF2HEATVOL_EDIT, pProjectMan->cutoff2HeatingVoltage, 0, 0);
			SetTextInt32(MOTORPARAPAGE_INDEX, MOTORPARA_FUSINGHEATVOL_EDIT, pProjectMan->fusingHeatingVoltage, 0, 0);
		}
		break;
		case SETUP_INPUT_BUTTON:
			pProjectMan->inInputPageFlag = 1;
		break;
		case SETUP_MANUALRAW_BUTTON:
		break;
		case SETUP_ABOUT_BUTTON:
			SetTextValue(ABOUTPAGE_INDEX, ABOUT_VERSION_EDIT, (uint8_t *)VERSION);
		break;
		case SETUP_BACK_BUTTON:
			SetTextInt32(MAINPAGE_INDEX, MAIN_OUTPUT_EDIT, pProjectMan->totalOutput, 0, 0);
		break;
		default:
			cDebug("setupPage BUTTON error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
