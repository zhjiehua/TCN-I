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

uint8_t heatingUpFlag = 0;
uint8_t cutoff1Flag = 0;
uint8_t cutoff2Flag = 0;
	
void testPageButtonProcess(uint16 control_id, uint8  state)
{
	switch(control_id)
	{
		case TEST_CLAMP1CW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CLAMP1CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP1CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}		
		break;
		case TEST_CLAMP1CCW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CLAMP1CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP1CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case TEST_CLAMP2CW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CLAMP2CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP2CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}		
		break;
		case TEST_CLAMP2CCW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CLAMP2CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP2CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case TEST_HEATINGUP_BUTTON: //加热片抬起
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_HEATINGUP;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_HEATINGUP_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
			
//			if(!heatingUpFlag)
//			{
//				heatingUpFlag = 1;
//				DCMotor_Run(HEATING_MOTOR, CW, 30);
//				while(1)
//				{
//					PhSensor_SingleScan(HEATING_SENSOR_L);
//					if(!PhSensor_SingleCheck(HEATING_SENSOR_L))
//					{
//						vTaskDelay(40);
//						DCMotor_Stop(HEATING_MOTOR);
//						break;
//					}
//					vTaskDelay(5);
//				}
//			}
//			else
//			{
//				heatingUpFlag = 0;
//				
//				DCMotor_Run(HEATING_MOTOR, CCW, 30);
//				while(1)
//				{
//					PhSensor_SingleScan(HEATING_SENSOR_R);
//					if(!PhSensor_SingleCheck(HEATING_SENSOR_R))
//					{
//						DCMotor_Stop(HEATING_MOTOR);
//						break;
//					}
//					vTaskDelay(5);
//				}
//			}
		}
		break;
		
		case TEST_HEATINGDOWN_BUTTON: //加热片放下
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_HEATINGDOWN;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_HEATINGDOWN_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		
		case TEST_CUTOFF1CW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CUTOFF1CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF1CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
			
//			if(!cutoff1Flag)
//			{
//				cutoff1Flag = 1;
//				//切断
//				DCMotor_Run(CUTOFF1_MOTOR, CW, 100);
//				while(1)
//				{
//					PhSensor_SingleScan(CUTOFF1_SENSOR_L);
//					if(PhSensor_SingleCheck(CUTOFF1_SENSOR_L))//这个传感器特别一点
//					{
//						DCMotor_Stop(CUTOFF1_MOTOR);
//						break;
//					}
//					vTaskDelay(5);
//				}
//			}
//			else
//			{
//				cutoff1Flag = 0;
//				DCMotor_Run(CUTOFF1_MOTOR, CCW, 100);
//				while(1)
//				{
//					PhSensor_SingleScan(CUTOFF1_SENSOR_R);
//					if(!PhSensor_SingleCheck(CUTOFF1_SENSOR_R))
//					{
//						DCMotor_Stop(CUTOFF1_MOTOR);
//						break;
//					}
//					vTaskDelay(5);
//				}
//			}
		}
		break;
		case TEST_CUTOFF1CCW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CUTOFF1CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF1CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case TEST_CUTOFF2CW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CUTOFF2CW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF2CW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
			
//			if(!cutoff2Flag)
//			{
//				cutoff2Flag = 1;
//				//切断
//				DCMotor_Run(CUTOFF1_MOTOR, CW, 100);
//				while(1)
//				{
//					PhSensor_SingleScan(CUTOFF1_SENSOR_L);
//					if(PhSensor_SingleCheck(CUTOFF1_SENSOR_L))//这个传感器特别一点
//					{
//						DCMotor_Stop(CUTOFF1_MOTOR);
//						break;
//					}
//					vTaskDelay(5);
//				}
//			}
//			else
//			{
//				cutoff2Flag = 0;
//				DCMotor_Run(CUTOFF1_MOTOR, CCW, 100);
//				while(1)
//				{
//					PhSensor_SingleScan(CUTOFF1_SENSOR_R);
//					if(!PhSensor_SingleCheck(CUTOFF1_SENSOR_R))
//					{
//						DCMotor_Stop(CUTOFF1_MOTOR);
//						break;
//					}
//					vTaskDelay(5);
//				}
//			}
		}
		break;
		case TEST_CUTOFF2CCW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_CUTOFF2CCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF2CCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case TEST_SEPERATECW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_SEPATATIONCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_SEPERATECW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case TEST_SEPERATECCW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_SEPATATIONCCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_SEPERATECCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case TEST_DISPOSCW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_DISPOSITIONCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_DISPOSCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		case TEST_DISPOSCCW_BUTTON:
		{
			if(state)
			{
				if(!(pProjectMan->projectStatus & PROJECT_RUNNING))
				{
					pProjectMan->projectStopFlag = 0;
					pProjectMan->projectStatus = PROJECT_TEST_DISPOSITIONCCW;
					pProjectMan->projectStatus |= PROJECT_RUNNING;
				}
				else
				{
					SetButtonValue(TESTPAGE_INDEX, TEST_DISPOSCCW_BUTTON, 0);
				}
			}
			else
			{
				pProjectMan->projectStopFlag = 1;
				pProjectMan->projectStatus = 0;
			}
		}
		break;
		
		case TEST_BACK_BUTTON:
		break;
		case TEST_FORWARD_BUTTON:
		break;
		default:
			cDebug("testPage BUTTON error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
