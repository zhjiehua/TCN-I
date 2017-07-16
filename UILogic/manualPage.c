#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../DCMotor/DCMotor.h"
#include "../StepMotor/StepMotor.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

#if 1	
void manualPageButtonProcess(uint16 control_id, uint8  state)
{
	switch(control_id)
	{
		case MANUAL_CLAMP1CW_BUTTON:  //夹紧1正转
		case MANUAL_CLAMP1CCW_BUTTON:	//夹紧1反转
		case MANUAL_CLAMP2CW_BUTTON:	//夹紧2正转
		case MANUAL_CLAMP2CCW_BUTTON:	//夹紧2反转
		case MANUAL_CUTOFF1CW_BUTTON:	//切断1正转
		case MANUAL_CUTOFF1CCW_BUTTON:	//切断1反转
		case MANUAL_CUTOFF2CW_BUTTON:	//切断2正转
		case MANUAL_CUTOFF2CCW_BUTTON:	//切断2反转
		case MANUAL_SEPARATECW_BUTTON:	//分离正转
		case MANUAL_SEPARATECCW_BUTTON:	//分离反转
		case MANUAL_DISLOCATECW_BUTTON:	//错位正转
		case MANUAL_DISLOCATECCW_BUTTON:	//错位反转
		case MANUAL_HEATINGUP_BUTTON: //加热片抬起
		case MANUAL_HEATINGDOWN_BUTTON: //加热片回位
		case MANUAL_HEATON_BUTTON:  //熔接加热片开
		{
			xSemaphoreTake(pProjectMan->projectStatusSem, portMAX_DELAY);
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = control_id;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
					xSemaphoreGive(pProjectMan->projectStatusSem);
				}
				else
				{
					xSemaphoreGive(pProjectMan->projectStatusSem);
					SetButtonValue(MANUALPAGE_INDEX, control_id, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				xSemaphoreGive(pProjectMan->projectStatusSem);
			}
		}		
		break;
		case MANUAL_BACK_BUTTON:
		break;
		default:
			cDebug("manualPage BUTTON error!\n");
		break;
	}
}
#else
void manualPageButtonProcess(uint16 control_id, uint8  state)
{
		switch(control_id)
	{
		case MANUAL_CLAMP1CW_BUTTON:  //夹紧1正转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CLAMP1CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP1CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}		
		break;
		case MANUAL_CLAMP1CCW_BUTTON:	//夹紧1反转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CLAMP1CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP1CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_CLAMP2CW_BUTTON:	//夹紧2正转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CLAMP2CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP2CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}		
		break;
		case MANUAL_CLAMP2CCW_BUTTON:	//夹紧2反转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CLAMP2CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP2CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_CUTOFF1CW_BUTTON:	//切断1正转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CUTOFF1CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF1CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_CUTOFF1CCW_BUTTON:	//切断1反转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CUTOFF1CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF1CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_CUTOFF2CW_BUTTON:	//切断2正转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CUTOFF2CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF2CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_CUTOFF2CCW_BUTTON:	//切断2反转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_CUTOFF2CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF2CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_SEPARATECW_BUTTON:	//分离正转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_SEPATATIONCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_SAPERATECW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_SEPARATECCW_BUTTON:	//分离反转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_SEPATATIONCCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_SAPERATECCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_DISLOCATECW_BUTTON:	//错位正转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_DISLOCATIONCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_DISLOCATECW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_DISLOCATECCW_BUTTON:	//错位反转
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_DISLOCATIONCCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_DISLOCATECCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		case MANUAL_HEATINGUP_BUTTON: //加热片抬起
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_HEATINGUP;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_HEATINGUP_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		
		case MANUAL_HEATINGDOWN_BUTTON: //加热片回位
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_HEATINGDOWN;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_HEATINGDOWN_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;
		
		case MANUAL_HEATON_BUTTON:  //熔接加热片开
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_MANUAL_HEATON;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_HEATON_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
			}
		}
		break;		
		case MANUAL_BACK_BUTTON:
		break;
		default:
			cDebug("manualPage BUTTON error!\n");
		break;
	}
}
#endif

#ifdef __cplusplus
}
#endif
