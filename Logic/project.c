#ifdef __cplusplus	  
extern "C" {
#endif

#include "project.h"
#include "managerment.h"
#include "CPrintf.h"
#include "stdio.h"
#include "stdint.h"
	
#include "../HARDWARE/DCMotor/DCMotor.h"
#include "../HARDWARE/StepMotor/StepMotor.h"
#include "../HARDWARE/Beep/beep.h"
#include "../HARDWARE/NTCResistor/NTCResistor.h"
#include "../HARDWARE/RelayMOS/RelayMOS.h"
#include "../HARDWARE/24CXX/24cxx.h"
#include "../HARDWARE/LED/led.h"
	
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

//夹紧1
//action : 0,夹紧松开; !=0,夹紧
//stopFlag : 0,继续动作; !=0,主动退出动作
void Clamp1(uint8_t action, uint8_t *pStopFlag)
{
	PhSensorEnum_TypeDef sensor;
	Direction_TypeDef dir;
	
	if(action)
	{
		dir = CW;
		sensor = CLAMP1_SENSOR_L;
	}
	else
	{
		dir = CCW;
		sensor = CLAMP1_SENSOR_R;
	}
	
	PhSensor_SingleScan(sensor);
	if(!PhSensor_SingleCheck(sensor) || *pStopFlag)
		return;
	
	DCMotor_Run(CLAMP1_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if((!PhSensor_SingleCheck(sensor)) || *pStopFlag)
		{
			if(action && !*pStopFlag)
				vTaskDelay(pProjectMan->clamp1Delay);//80
			DCMotor_Stop(CLAMP1_MOTOR);
			break;
		}
		
		vTaskDelay(5);
	}
}

//夹紧2
//action : 0,夹紧松开; !=0,夹紧
//stopFlag : 0,继续动作; !=0,主动退出动作
void Clamp2(uint8_t action, uint8_t *pStopFlag)
{
	PhSensorEnum_TypeDef sensor;
	Direction_TypeDef dir;
	
	if(action)
	{
		dir = CW;
		sensor = CLAMP2_SENSOR_L;
	}
	else
	{
		dir = CCW;
		sensor = CLAMP2_SENSOR_R;
	}
	
	PhSensor_SingleScan(sensor);
	if(!PhSensor_SingleCheck(sensor) || *pStopFlag)
		return;
	
	DCMotor_Run(CLAMP2_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if((!PhSensor_SingleCheck(sensor)) || *pStopFlag)
		{
			if(action && !*pStopFlag)
				vTaskDelay(pProjectMan->clamp2Delay);//80
			DCMotor_Stop(CLAMP2_MOTOR);
			break;
		}
		
		vTaskDelay(5);
	}
}

//切断1
//action : 0,切断松开; !=0,切断
//stopFlag : 0,继续动作; !=0,主动退出动作
void Cutoff1(uint8_t action, uint8_t *pStopFlag)
{
	PhSensorEnum_TypeDef sensor;
	Direction_TypeDef dir;
	uint8_t sensorFlag;
	
	if(action)
	{
		dir = CW;
		sensor = CUTOFF1_SENSOR_L;
		
		PhSensor_SingleScan(sensor);
		if(PhSensor_SingleCheck(sensor) || *pStopFlag)
			return;
	}
	else
	{
		dir = CCW;
		sensor = CUTOFF1_SENSOR_R;
		
		PhSensor_SingleScan(sensor);
		if(!PhSensor_SingleCheck(sensor) || *pStopFlag)
			return;
	}
	
	DCMotor_Run(CUTOFF1_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if(action)
			sensorFlag = PhSensor_SingleCheck(sensor);
		else
		{
			//sensorFlag = !PhSensor_SingleCheck(sensor);
			
			pProjectMan->timerExpireFlag[0] = 0;
			xTimerChangePeriod( pProjectMan->xTimerUser[0], pProjectMan->cutoffReturnDelay, 0);//4000/portTICK_PERIOD_MS
		
			while(!*pStopFlag && !pProjectMan->timerExpireFlag[0])
			{
				vTaskDelay(5);
			}
			if(*pStopFlag)
				xTimerStop( pProjectMan->xTimerUser[0], 0);
			
			sensorFlag = 1;
		}
		
		if(sensorFlag || *pStopFlag)//这个传感器特别一点
		{
			if(action && !*pStopFlag)//刀片轴有点松，切断时要延迟一点再停
			{
				vTaskDelay(pProjectMan->cutoff1Delay);//330
			}
			
			DCMotor_Stop(CUTOFF1_MOTOR);
			break;
		}
		
		vTaskDelay(5);
	}
}

//切断2
//action : 0,切断松开; !=0,切断
//stopFlag : 0,继续动作; !=0,主动退出动作
void Cutoff2(uint8_t action, uint8_t *pStopFlag)
{
	PhSensorEnum_TypeDef sensor;
	Direction_TypeDef dir;
	uint8_t sensorFlag;

	if(action)
	{
		dir = CW;
		sensor = CUTOFF2_SENSOR_L;
	}
	else
	{
		dir = CCW;
		sensor = CUTOFF2_SENSOR_R;
	}
	
	PhSensor_SingleScan(sensor);
	if(!PhSensor_SingleCheck(sensor) || *pStopFlag)
		return;
	
	DCMotor_Run(CUTOFF2_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if(action)
			sensorFlag = !PhSensor_SingleCheck(sensor);
		else
		{
			//sensorFlag = !PhSensor_SingleCheck(sensor);
			
			pProjectMan->timerExpireFlag[1] = 0;
			xTimerChangePeriod( pProjectMan->xTimerUser[1], pProjectMan->cutoffReturnDelay, 0);//4000/portTICK_PERIOD_MS
		
			while(!*pStopFlag && !pProjectMan->timerExpireFlag[1])
			{
				vTaskDelay(5);
			}
			if(*pStopFlag)
				xTimerStop( pProjectMan->xTimerUser[1], 0);
			
			sensorFlag = 1;
		}
		
		if(sensorFlag || *pStopFlag)
		{
			if(action && !*pStopFlag)//刀片轴有点松，切断时要延迟一点再停
			{
				vTaskDelay(pProjectMan->cutoff2Delay);//420
			}
			DCMotor_Stop(CUTOFF2_MOTOR);
			break;
		}
		
		vTaskDelay(5);
	}
}

#if 0
//加热片加热
//stopFlag : 0,继续动作; !=0,主动退出动作
void HeatingCutoff(uint8_t *pStopFlag)
{
	uint8_t flag1, flag2;
	flag1 = 0;
	flag2 = 0;
	
	DCMotor_Run(CUTOFF1HEATDCMOTOR1, CW, 100);
	DCMotor_Run(CUTOFF1HEATDCMOTOR2, CW, 100);
	DCMotor_Run(CUTOFF2HEATDCMOTOR1, CW, 100);
	DCMotor_Run(CUTOFF2HEATDCMOTOR2, CW, 100);
	flag1 = 0;
	flag2 = 0;
	while(1)
	{
		if((!flag1 && (adcTemp[0].temperature >= pProjectMan->cutoff1Temperature)) || *pStopFlag)
		{
			DCMotor_Stop(CUTOFF1HEATDCMOTOR1);
			DCMotor_Stop(CUTOFF1HEATDCMOTOR2);
			flag1 = 1;
		}
		if((!flag2 && (adcTemp[1].temperature >= pProjectMan->cutoff2Temperature)) || *pStopFlag)
		{
			DCMotor_Stop(CUTOFF2HEATDCMOTOR1);
			DCMotor_Stop(CUTOFF2HEATDCMOTOR2);
			flag2 = 1;
		}
		if(flag1 && flag2)
			break;
		
		if(flag1 && !flag2)
		{
			if(adcTemp[0].temperature <= pProjectMan->cutoff1Temperature)
			{
				DCMotor_Run(CUTOFF1HEATDCMOTOR1, CW, 100);
				DCMotor_Run(CUTOFF1HEATDCMOTOR2, CW, 100);
				flag1 = 0;
			}
		}
		else if(!flag1 && flag2)
		{
			if(adcTemp[1].temperature <= pProjectMan->cutoff2Temperature)
			{
				DCMotor_Run(CUTOFF2HEATDCMOTOR1, CW, 100);
				DCMotor_Run(CUTOFF2HEATDCMOTOR2, CW, 100);
				flag2 = 0;
			}
		}
		
		vTaskDelay(5);
	}
}

//加热片加热
//stopFlag : 0,继续动作; !=0,主动退出动作
void HeatingCutoff1(uint8_t *pStopFlag)
{
	DCMotor_Run(CUTOFF1HEATDCMOTOR1, CW, 100);
	DCMotor_Run(CUTOFF1HEATDCMOTOR2, CW, 100);
	while(1)
	{
		if((adcTemp[0].temperature >= pProjectMan->cutoff1Temperature) || *pStopFlag)
		{
			DCMotor_Stop(CUTOFF1HEATDCMOTOR1);
			DCMotor_Stop(CUTOFF1HEATDCMOTOR2);
			break;
		}
		vTaskDelay(5);
	}
}

//加热片加热
//stopFlag : 0,继续动作; !=0,主动退出动作
void HeatingCutoff2(uint8_t *pStopFlag)
{
	DCMotor_Run(CUTOFF2HEATDCMOTOR1, CW, 100);
	DCMotor_Run(CUTOFF2HEATDCMOTOR2, CW, 100);
	while(1)
	{
		if((adcTemp[1].temperature >= pProjectMan->cutoff2Temperature) || *pStopFlag)
		{
			DCMotor_Stop(CUTOFF2HEATDCMOTOR1);
			DCMotor_Stop(CUTOFF2HEATDCMOTOR2);
			break;
		}
		vTaskDelay(5);
	}
}
#endif

//分离
//action : 0,分离; !=0,分离闭合
//stopFlag : 0,继续动作; !=0,主动退出动作
void Separation(uint8_t action, uint8_t *pStopFlag)
{
	PhSensorEnum_TypeDef sensor;
	Direction_TypeDef dir;
	
	if(action)
	{
		dir = CCW;
		sensor = SAPERATE_SENSOR_L;
	}
	else
	{
		dir = CW;
		sensor = SAPERATE_SENSOR_R;
	}
	
	PhSensor_SingleScan(sensor);
	if(!PhSensor_SingleCheck(sensor))
		return;
	
	DCMotor_Run(SAPERATE_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if(!PhSensor_SingleCheck(sensor) || *pStopFlag)
		{
			DCMotor_Stop(SAPERATE_MOTOR);
			break;
		}
		vTaskDelay(5);
	}
}

//错位
//action : 0,错位回位; !=0,错位
//stopFlag : 0,继续动作; !=0,主动退出动作
void Dislocation(uint8_t action, uint8_t *pStopFlag)
{
	PhSensorEnum_TypeDef sensor;
	Direction_TypeDef dir;
	
	if(action)
	{
		dir = CCW;
		sensor = DISPOS_SENSOR_L;
	}
	else
	{
		dir = CW;
		sensor = DISPOS_SENSOR_R;
	}
	
	PhSensor_SingleScan(sensor);
	if(!PhSensor_SingleCheck(sensor))
		return;
	
	StepMotor_SetDir(DISPOS_MOTOR, dir);
	StepMotor_SetSpeed(DISPOS_MOTOR, 9);
	StepMotor_SetCMD(DISPOS_MOTOR, ENABLE);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if(!PhSensor_SingleCheck(sensor) || *pStopFlag)
		{
			StepMotor_Stop(DISPOS_MOTOR);
			break;
		}
		vTaskDelay(5);
	}
}

//错位一定距离
//action : 0,错位回位; !=0,错位
//stopFlag : 0,继续动作; !=0,主动退出动作
void DislocationDistance(uint8_t action, uint32_t distance, uint8_t *pStopFlag)
{
	Direction_TypeDef dir;
	
	if(action)
		dir = CCW;
	else
		dir = CW;
	
	StepMotor_SetDir(DISPOS_MOTOR, dir);
	StepMotor_SetSpeed(DISPOS_MOTOR, 9);
	StepMotor_SetPluse(DISPOS_MOTOR, distance);
	StepMotor_SetCMD(DISPOS_MOTOR, ENABLE);
	while(1)
	{
		if(!StepMotor_IsStop(DISPOS_MOTOR) || *pStopFlag)
			break;
		
		vTaskDelay(5);
	}
}

//熔接加热
//stopFlag : 0,继续动作; !=0,主动退出动作
void Heating(uint8_t *pStopFlag)
{
	//熔接加热
	pProjectMan->fusingTempControlFlag = 0;
	pProjectMan->fusingRaisingTempControlFlag = 1;
	RELAY = 1;
	while(1)
	{
		if(adcTemp[2].temperature >= pProjectMan->fusingTemperature || *pStopFlag)
			break;
		vTaskDelay(5);
	}
	RELAY = 0;
	pProjectMan->fusingRaisingTempControlFlag = 0;
	pProjectMan->fusingTempControlFlag = 1;//退出温度控制，准备降温
}

//加热片抬起
//action : 0,加热片回位; !=0,加热片抬起
//stopFlag : 0,继续动作; !=0,主动退出动作
void HeatingUp(uint8_t action, uint8_t *pStopFlag)
{
	if(action)
	{
		DCMotor_Run(HEATING_MOTOR, CW, pProjectMan->heatingUpSpeed);//30
		
		pProjectMan->timerExpireFlag[2] = 0;
		xTimerChangePeriod( pProjectMan->xTimerUser[2], pProjectMan->heatingUpDelay, 0);
		while(!pProjectMan->timerExpireFlag[2] && !*pStopFlag)
			vTaskDelay(5);
		if(*pStopFlag)
		{
			xTimerStop( pProjectMan->xTimerUser[2], 0 );
		}
		
		DCMotor_Stop(HEATING_MOTOR);
	}
	else
	{
		PhSensor_SingleScan(HEATING_SENSOR_R);
		if(!PhSensor_SingleCheck(HEATING_SENSOR_R))
			return;
		
		DCMotor_Run(HEATING_MOTOR, CCW, pProjectMan->heatingDownSpeed);//30
		while(1)
		{
			PhSensor_SingleScan(HEATING_SENSOR_R);
			if(!PhSensor_SingleCheck(HEATING_SENSOR_R) || *pStopFlag)
			{
				vTaskDelay(pProjectMan->heatingDownDelay);
				
				DCMotor_Stop(HEATING_MOTOR);
				break;
			}
			vTaskDelay(5);
		}
	}
}

//半复位，用于在急停状态下
void HalfResetOriginStatus(void)
{
	uint32_t cutoffReturnDelay = pProjectMan->cutoffReturnDelay;
	pProjectMan->cutoffReturnDelay = 500;
	
	//切断回位
	pProjectMan->cutoff1Action = 0;
	pProjectMan->cutoff2Action = 0;
	vTaskResume( pProjectMan->cutoff1TaskHandle );
	vTaskResume( pProjectMan->cutoff2TaskHandle );
	
	//夹紧松开
	pProjectMan->clamp1Action = 0;
	pProjectMan->clamp2Action = 0;
	vTaskResume( pProjectMan->clamp1TaskHandle );
	vTaskResume( pProjectMan->clamp2TaskHandle );
	
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP2, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF2, pdTRUE, pdFALSE, portMAX_DELAY);
	
	pProjectMan->cutoffReturnDelay = cutoffReturnDelay;
}

//恢复为原始状态
//stopFlag : 0,继续动作; !=0,主动退出动作
void ResetOriginStatus(uint8_t *pStopFlag)
{
	pProjectMan->projectCurrentStatus = 10;
	
	//分离
	pProjectMan->separationAction = 0;
	vTaskResume( pProjectMan->separationTaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_SEPATATION, pdTRUE, pdFALSE, portMAX_DELAY);

	//放下加热片
	pProjectMan->heatingUpAction = 0;
	vTaskResume( pProjectMan->heatingUpTaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_HEATINGUP, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//错位回位
	pProjectMan->dislocationAction = 0;
	vTaskResume( pProjectMan->dislocationTaskHandle );

	//切断
	pProjectMan->cutoff1Action = 1;
	pProjectMan->cutoff2Action = 1;
	vTaskResume( pProjectMan->cutoff1TaskHandle );
	vTaskResume( pProjectMan->cutoff2TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF2, pdTRUE, pdFALSE, portMAX_DELAY);

	//切断回位
	pProjectMan->cutoff1Action = 0;
	pProjectMan->cutoff2Action = 0;
	vTaskResume( pProjectMan->cutoff1TaskHandle );
	vTaskResume( pProjectMan->cutoff2TaskHandle );

	//夹紧松开
	pProjectMan->clamp1Action = 0;
	pProjectMan->clamp2Action = 0;
	vTaskResume( pProjectMan->clamp1TaskHandle );
	vTaskResume( pProjectMan->clamp2TaskHandle );
	
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_DISLOCATION, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//分离闭合
	pProjectMan->separationAction = 1;
	vTaskResume( pProjectMan->separationTaskHandle );
	
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP2, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF2, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_SEPATATION, pdTRUE, pdFALSE, portMAX_DELAY);
	
	pProjectMan->projectCurrentStatus = 0;
}

//自动运行1个周期
//stopFlag : 0,继续动作; !=0,主动退出动作
void AutoRun(uint8_t *pStopFlag)
{
	//熔接加热
	pProjectMan->fusingTempControlFlag = 0;
	pProjectMan->fusingRaisingTempControlFlag = 1;//加热到熔接温度点

	//夹紧
	pProjectMan->projectCurrentStatus = 1;
	pProjectMan->clamp1Action = 1;
	pProjectMan->clamp2Action = 1;
	vTaskResume( pProjectMan->clamp1TaskHandle );
	vTaskResume( pProjectMan->clamp2TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP2, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//切断加热片达到指定温度	
	//切断，并延时一定时间自动回位
	pProjectMan->projectCurrentStatus = 2;
	pProjectMan->cutoff1Action = 2;
	pProjectMan->cutoff2Action = 2;
	vTaskResume( pProjectMan->cutoff1TaskHandle );
	vTaskResume( pProjectMan->cutoff2TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF2, pdTRUE, pdFALSE, portMAX_DELAY);
	
	vTaskDelay(1000);
	
	//分离
	pProjectMan->projectCurrentStatus = 3;
	pProjectMan->separationAction = 0;
	vTaskResume( pProjectMan->separationTaskHandle );
	
	//错位
	pProjectMan->projectCurrentStatus = 4;
	pProjectMan->dislocationAction = 1;
	vTaskResume( pProjectMan->dislocationTaskHandle );
	
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_SEPATATION, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_DISLOCATION, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//是否加热到指定温度
	pProjectMan->projectCurrentStatus = 5;
#if !TEMPERATURE_MASK
	while(!pProjectMan->heatingUpFlag && !pProjectMan->projectStopFlag)
		vTaskDelay(5);
#endif
	pProjectMan->fusingTempControlFlag = 0;
	pProjectMan->fusingRaisingTempControlFlag = 0;//返回维持温度点
	
	//抬起加热片
	pProjectMan->projectCurrentStatus = 6;
	pProjectMan->heatingUpAction = 1;
	vTaskResume( pProjectMan->heatingUpTaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_HEATINGUP, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//延时熔接时间
	pProjectMan->timerExpireFlag[2] = 0;
	xTimerChangePeriod( pProjectMan->xTimerUser[2], pProjectMan->fusingTime, 0);
	while(!pProjectMan->timerExpireFlag[2] && !pProjectMan->projectStopFlag)
		vTaskDelay(5);
	if(pProjectMan->projectStopFlag)
		xTimerStop( pProjectMan->xTimerUser[2], 0 );
	
	//放下加热片
	pProjectMan->heatingUpAction = 0;
	vTaskResume( pProjectMan->heatingUpTaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_HEATINGUP, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//分离闭合
	pProjectMan->projectCurrentStatus = 7;
	pProjectMan->separationAction = 1;
	vTaskResume( pProjectMan->separationTaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_SEPATATION, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//延时接合时间
	pProjectMan->timerExpireFlag[2] = 0;
	xTimerChangePeriod( pProjectMan->xTimerUser[2], pProjectMan->jointTime, 0);
	while(!pProjectMan->timerExpireFlag[2] && !pProjectMan->projectStopFlag)
		vTaskDelay(5);
	if(pProjectMan->projectStopFlag)
		xTimerStop( pProjectMan->xTimerUser[2], 0 );
	
	//夹紧松开
	pProjectMan->projectCurrentStatus = 8;
	pProjectMan->clamp1Action = 0;
	pProjectMan->clamp2Action = 0;
	vTaskResume( pProjectMan->clamp1TaskHandle );
	vTaskResume( pProjectMan->clamp2TaskHandle );
	
	//错位一点
	pProjectMan->dislocationAction = 2;
	vTaskResume( pProjectMan->dislocationTaskHandle );
	
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP2, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_DISLOCATION, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//提示取走连通管
	xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
	SetTextValue(TIPS1PAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"1 请尽快取走连通管；\r\n2 并尽快用双手将管捏通！");
	SetScreen(TIPS1PAGE_INDEX);
	SetTextValue(TIPS1PAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"1 请尽快取走连通管；\r\n2 并尽快用双手将管捏通！");
	pProjectMan->tipsBuzzeFlag = 1;
	xSemaphoreGive(pProjectMan->lcdUartSem);
	
	//等待切断回位
	pProjectMan->projectCurrentStatus = 9;
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF1, pdTRUE, pdFALSE, portMAX_DELAY);
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF2, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//提示取走剩余的管
	xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
	SetTextValue(TIPS1PAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"1 请尽快取走剩余的管；\r\n2 注意:在冷却前不要用手捏！");
	SetScreen(TIPS1PAGE_INDEX);
	SetTextValue(TIPS1PAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"1 请尽快取走剩余的管；\r\n2 注意:在冷却前不要用手捏！");
	pProjectMan->tipsBuzzeFlag = 1;
	xSemaphoreGive(pProjectMan->lcdUartSem);
	
	pProjectMan->projectCurrentStatus = 80;
}

void AutoRun_Cutoff1(uint8_t *pStopFlag)
{
	//夹紧
	pProjectMan->clamp2Action = 1;
	vTaskResume( pProjectMan->clamp2TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP2, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//切断，并延时一定时间再回位
	pProjectMan->cutoff1Action = 2;
	vTaskResume( pProjectMan->cutoff1TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF1, pdTRUE, pdFALSE, portMAX_DELAY);
	
	vTaskDelay(1000);
	
	//分离
	pProjectMan->separationAction = 0;
	vTaskResume( pProjectMan->separationTaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_SEPATATION, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//等待降温延时完成，这时切断已经回位
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF1, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//夹紧松开
	pProjectMan->clamp2Action = 0;
	vTaskResume( pProjectMan->clamp2TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP2, pdTRUE, pdFALSE, portMAX_DELAY);
}

void AutoRun_Cutoff2(uint8_t *pStopFlag)
{
	//夹紧
	pProjectMan->clamp1Action = 1;
	vTaskResume( pProjectMan->clamp1TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP1, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//切断，并延时一定时间再回位
	pProjectMan->cutoff2Action = 2;
	vTaskResume( pProjectMan->cutoff2TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF2, pdTRUE, pdFALSE, portMAX_DELAY);
	
	vTaskDelay(1000);
	
	//分离
	pProjectMan->separationAction = 0;
	vTaskResume( pProjectMan->separationTaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_SEPATATION, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//等待降温延时完成，这时切断已经回位
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CUTOFF2, pdTRUE, pdFALSE, portMAX_DELAY);
	
	//夹紧松开
	pProjectMan->clamp1Action = 0;
	vTaskResume( pProjectMan->clamp1TaskHandle );
	xEventGroupWaitBits(pProjectMan->projectEventGroup, 1UL<<PROJECT_EVENTPOS_CLAMP1, pdTRUE, pdFALSE, portMAX_DELAY);
}

void ProjectTask(void)
{
	uint32_t j;
	static uint8_t systemPreheatingFlag = 0;
	
//	while(!pProjectMan->lcdNotifyResetFlag)
//		vTaskDelay(100);
//	
//	pProjectMan->lcdNotifyResetFlag = 0;
	ResetDevice();//复位串口屏
	ResetDevice();//复位串口屏
	
	for(j=0;j<336;j++);
	//for(j=0;j<65536;j++);
	//for(j=0;j<65536;j++);
	
	//发送握手命令
	SetHandShake();//发送握手命令
	SetHandShake();//发送握手命令，第一个握手命令会丢失
	SetHandShake();//发送握手命令
	
	while(!pProjectMan->lcdNotifyResetFlag)
		vTaskDelay(100);
	
#ifndef STM32SIM	
	while(1)
	{
		if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))
		{
			static uint8_t flag = 0;
			if(!flag)
			{
				flag = 1;
				xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
				SetTextValue(TIPSPAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"请松开急停旋钮！");
				SetScreen(TIPSPAGE_INDEX);
				xSemaphoreGive(pProjectMan->lcdUartSem);
			}
		}
		else
			break;
		
		vTaskDelay(10);
	}
#endif
	
	//如果上次关机前有按急停，则松开夹紧和切断回位
	if(pProjectMan->systemEmergencyFlag)
	{
		xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
		SetTextValue(TIPS1PAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"1 请将设备上的管清理走；\r\n2 清理完后请手动复位！");
		SetScreen(TIPS1PAGE_INDEX);
		xSemaphoreGive(pProjectMan->lcdUartSem);
		
		HalfResetOriginStatus();
		
		pProjectMan->tipsBuzzeFlag = 2;//开蜂鸣器
		
		pProjectMan->systemEmergencyFlag = 0;
		AT24CXX_Write(EMERGENCYFLAG_BASEADDR, (uint8_t*)&pProjectMan->systemEmergencyFlag, 1);
		pProjectMan->autoButtonFlag = 1;
		
		//vTaskDelay(1000);
	}
	else
	{
		xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
		SetTextValue(LOGOPAGE_INDEX, LOGO_STATUS_EDIT, (uint8_t*)"系统复位中……");
		SetScreen(LOGOPAGE_INDEX);
		xSemaphoreGive(pProjectMan->lcdUartSem);
#ifndef STM32SIM
		ResetOriginStatus(&pProjectMan->projectStopFlag);
#endif
		pProjectMan->autoButtonFlag = 0;
		
		xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
		SetTextValue(LOGOPAGE_INDEX, LOGO_STATUS_EDIT, (uint8_t*)"系统预热中……");
		SetScreen(LOGOPAGE_INDEX);
		xSemaphoreGive(pProjectMan->lcdUartSem);
	}
	
	pProjectMan->systemPowerUpFlag = 2;
	
//	while(1)
//	{
//		if((adcTemp[0].temperature >= pProjectMan->cutoff1Temperature)
//			&& (adcTemp[1].temperature >= pProjectMan->cutoff2Temperature)
//			&& (adcTemp[2].temperature >= pProjectMan->fusingHoldingTemperature))
//		{
//			xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
//			SetTextInt32(MAINPAGE_INDEX, MAIN_OUTPUT_EDIT, pProjectMan->totalOutput, 0, 0);
//			SetScreen(MAINPAGE_INDEX);
//			xSemaphoreGive(pProjectMan->lcdUartSem);	
//			break;
//		}
//		else
//			vTaskDelay(10);
//	}
	
	while(1)
	{
#if 1	
		if((pProjectMan->systemPowerUpFlag == 2) && (pProjectMan->tipsBuzzeFlag == 0))
		{
			if(!systemPreheatingFlag)
			{
				xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
				SetTextValue(LOGOPAGE_INDEX, LOGO_STATUS_EDIT, (uint8_t*)"系统预热中……");
				SetScreen(LOGOPAGE_INDEX);
				xSemaphoreGive(pProjectMan->lcdUartSem);
				
				systemPreheatingFlag = 1;
			}
			
#ifndef STM32SIM			
			if((adcTemp[0].temperature >= pProjectMan->cutoff1Temperature)
				&& (adcTemp[1].temperature >= pProjectMan->cutoff2Temperature)
				&& (adcTemp[2].temperature >= pProjectMan->fusingHoldingTemperature))
#endif
			{
				xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
				SetTextInt32(MAINPAGE_INDEX, MAIN_OUTPUT_EDIT, pProjectMan->totalOutput, 0, 0);
#ifndef STM32SIM				
				SetScreen(MAINPAGE_INDEX);
#else
				SetScreen(SETUPPAGE_INDEX);
#endif
				xSemaphoreGive(pProjectMan->lcdUartSem);

				pProjectMan->systemPowerUpFlag = 1;
			}
		}
		
		if(pProjectMan->projectStatus&PROJECT_RUNNING)
		{
			switch(pProjectMan->projectStatus&0x7F)
			{
				case PROJECT_MANUAL_CLAMP1CW:
#ifndef STM32SIM
					Clamp1(1, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP1CW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);				
				break;
				case PROJECT_MANUAL_CLAMP1CCW:
#ifndef STM32SIM
					Clamp1(0, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP1CCW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_CLAMP2CW:
#ifndef STM32SIM
					Clamp2(1, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP2CW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_CLAMP2CCW:
#ifndef STM32SIM
					Clamp2(0, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CLAMP2CCW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_CUTOFF1CW:
#ifndef STM32SIM
					Cutoff1(1, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF1CW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_CUTOFF1CCW:
#ifndef STM32SIM
					Cutoff1(0, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF1CCW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_CUTOFF2CW:
#ifndef STM32SIM
					Cutoff2(1, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF2CW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_CUTOFF2CCW:
#ifndef STM32SIM
					Cutoff2(0, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_CUTOFF2CCW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_HEATINGUP:
#ifndef STM32SIM
					HeatingUp(1, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_HEATINGUP_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_HEATINGDOWN:
#ifndef STM32SIM
					HeatingUp(0, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_HEATINGDOWN_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_SEPATATIONCW:
#ifndef STM32SIM
					Separation(1, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_SEPARATECW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_SEPATATIONCCW:
#ifndef STM32SIM
					Separation(0, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_SEPARATECCW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_DISLOCATIONCW:
#ifndef STM32SIM
					Dislocation(1, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_DISLOCATECW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_MANUAL_DISLOCATIONCCW:
#ifndef STM32SIM
					Dislocation(0, &(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(MANUALPAGE_INDEX, MANUAL_DISLOCATECCW_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				
				case PROJECT_STATUS_CUTOFF1:
#ifndef STM32SIM
					AutoRun_Cutoff1(&(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(STATUSPAGE_INDEX, STATUS_CUTOFF1_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_STATUS_CUTOFF2:
#ifndef STM32SIM
					AutoRun_Cutoff2(&(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(STATUSPAGE_INDEX, STATUS_CUTOFF2_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				
				case PROJECT_STATUS_RESET:
#ifndef STM32SIM
					ResetOriginStatus(&(pProjectMan->projectStopFlag));
#endif
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(STATUSPAGE_INDEX, STATUS_RESET_BUTTON, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
				case PROJECT_STATUS_AUTO:
					if(pProjectMan->usableTimes > 0)
					{
#ifndef STM32SIM
						AutoRun(&(pProjectMan->projectStopFlag));
#endif
						pProjectMan->totalOutput++;
						if(pProjectMan->totalOutput > 0xFFFFFFFF)
							pProjectMan->totalOutput = 0;
						
//						pProjectMan->usableTimes--;
//						AT24CXX_Write(USABLETIMES_BASEADDR, (uint8_t*)&pProjectMan->usableTimes, 2);

						AT24CXX_Write(TOTALOUTPUT_BASEADDR, (uint8_t*)&pProjectMan->totalOutput, 4);
					}
					
					xSemaphoreTake(pProjectMan->lcdUartSem, portMAX_DELAY);
					SetButtonValue(STATUSPAGE_INDEX, STATUS_AUTO_BUTTON, 0);
					SetTextInt32(MAINPAGE_INDEX, MAIN_OUTPUT_EDIT, pProjectMan->totalOutput, 0, 0);
					xSemaphoreGive(pProjectMan->lcdUartSem);
				break;
			}
			xSemaphoreTake(pProjectMan->projectStatusSem, portMAX_DELAY);
			if((pProjectMan->projectStatus&0x7F) != PROJECT_STATUS_RESET)
				pProjectMan->autoButtonFlag = 1;
			else
				pProjectMan->autoButtonFlag = 0;
			pProjectMan->projectStatus = 0;
			pProjectMan->projectStopFlag = 0;
			pProjectMan->autoNResetFlag = 0;
			xSemaphoreGive(pProjectMan->projectStatusSem);
		}
		else
			vTaskDelay(10);
#endif
		
		LED2Task(); //LED2闪烁指示PROJECT线程正在运行	
	}
}

#ifdef __cplusplus
}
#endif
