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
#include "../RelayMOS/RelayMOS.h"
#include "LED/led.h"
	
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

//夹紧
//action : 0,夹紧松开; !=0,夹紧
//stopFlag : 0,继续动作; !=0,主动退出动作
void Clamp(uint8_t action, uint8_t *pStopFlag)
{
	uint8_t flag1, flag2;
	PhSensorEnum_TypeDef clamp1Sensor, clamp2Sensor;
	Direction_TypeDef dir;
	
	if(action)
	{
		dir = CW;
		clamp1Sensor = CLAMP1_SENSOR_L;
		clamp2Sensor = CLAMP2_SENSOR_L;
	}
	else
	{
		dir = CCW;
		clamp1Sensor = CLAMP1_SENSOR_R;
		clamp2Sensor = CLAMP2_SENSOR_R;
	}
	
	DCMotor_Run(CLAMP1_MOTOR, dir, 100);
	DCMotor_Run(CLAMP2_MOTOR, dir, 100);
	flag1 = 0;
	flag2 = 0;
	while(1)
	{
		PhSensor_SingleScan(clamp1Sensor);
		if((!flag1 && (!PhSensor_SingleCheck(clamp1Sensor))) || *pStopFlag)
		{
			DCMotor_Stop(CLAMP1_MOTOR);
			flag1 = 1;
		}
		PhSensor_SingleScan(clamp2Sensor);
		if((!flag2 && (!PhSensor_SingleCheck(clamp2Sensor))) || *pStopFlag)
		{
			DCMotor_Stop(CLAMP2_MOTOR);
			flag2 = 1;
		}
		if(flag1 && flag2)
			break;
		
		vTaskDelay(5);
	}
}

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
	if(!PhSensor_SingleCheck(sensor))
		return;
	
	DCMotor_Run(CLAMP1_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if((!PhSensor_SingleCheck(sensor)) || *pStopFlag)
		{
			vTaskDelay(80);
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
	if(!PhSensor_SingleCheck(sensor))
		return;
	
	DCMotor_Run(CLAMP2_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if((!PhSensor_SingleCheck(sensor)) || *pStopFlag)
		{
			vTaskDelay(80);
			DCMotor_Stop(CLAMP2_MOTOR);
			break;
		}
		
		vTaskDelay(5);
	}
}

//切断
//action : 0,切断松开; !=0,切断
//stopFlag : 0,继续动作; !=0,主动退出动作
void Cutoff(uint8_t action, uint8_t *pStopFlag)
{
	uint8_t flag1, flag2;
	flag1 = 0;
	flag2 = 0;
	
#if 0	
	if(action)//切断
	{
		DCMotor_Run(CUTOFF1_MOTOR, CW, 100);
		DCMotor_Run(CUTOFF2_MOTOR, CW, 100);
		while(1)
		{
			PhSensor_SingleScan(CUTOFF1_SENSOR_L);
			if((!flag1 && (PhSensor_SingleCheck(CUTOFF1_SENSOR_L))) || *pStopFlag)//这个传感器特别一点
			{
				DCMotor_Stop(CUTOFF1_MOTOR);
				flag1 = 1;
			}
			PhSensor_SingleScan(CUTOFF2_SENSOR_L);
			if((!flag2 && (!PhSensor_SingleCheck(CUTOFF2_SENSOR_L))) || *pStopFlag)
			{
				DCMotor_Stop(CUTOFF2_MOTOR);
				flag2 = 1;
			}
			if(flag1 && flag2)
				break;
			
			vTaskDelay(5);
		}
	}
	else//切断松开
	{
		DCMotor_Run(CUTOFF1_MOTOR, CCW, 100);
		DCMotor_Run(CUTOFF2_MOTOR, CCW, 100);
		while(1)
		{
//			PhSensor_SingleScan(CUTOFF1_SENSOR_R);
//			if((!flag1 && (!PhSensor_SingleCheck(CUTOFF1_SENSOR_R))) || *pStopFlag)
//			{
//				DCMotor_Stop(CUTOFF1_MOTOR);
//				flag1 = 1;
//			}
			PhSensor_SingleScan(CUTOFF2_SENSOR_R);
			if((!flag2 && (!PhSensor_SingleCheck(CUTOFF2_SENSOR_R))) || *pStopFlag)
			{
				DCMotor_Stop(CUTOFF2_MOTOR);
				flag2 = 1;
				
				DCMotor_Stop(CUTOFF1_MOTOR);
				flag1 = 1;
			}
			
			if(flag1 && flag2)
				break;
			
			vTaskDelay(5);
		}
	}//if(action)
	
#else
	
	if(action)//切断
	{
		DCMotor_Run(CUTOFF1_MOTOR, CW, 100);
		DCMotor_Run(CUTOFF2_MOTOR, CW, 100);
		while((flag1 != 2) || (flag2 != 2))
		{
			if(*pStopFlag)
			{
				DCMotor_Stop(CUTOFF1_MOTOR);
				DCMotor_Stop(CUTOFF2_MOTOR);

				if( xTimerIsTimerActive( pProjectMan->xTimerUser[0] ) == pdTRUE )
					xTimerStop( pProjectMan->xTimerUser[0], 0);
				if( xTimerIsTimerActive( pProjectMan->xTimerUser[1] ) == pdTRUE )
					xTimerStop( pProjectMan->xTimerUser[1], 0);
				break;
			}
			
			switch(flag1)
			{
				case 0:
					PhSensor_SingleScan(CUTOFF1_SENSOR_L);
					if(PhSensor_SingleCheck(CUTOFF1_SENSOR_L))//这个传感器特别一点
					{
						flag1 = 1;
						
		//				for(i=0;i<SOFTWARETIMER_COUNT;i++)
		//				{
		//					if( xTimerIsTimerActive( pProjectMan->xTimerUser[i] ) == pdFALSE )
		//						xTimerStart( pProjectMan->xTimerUser[i], 0 );
		//				}
						
						//修改定时器周期并启动
						xTimerChangePeriod( pProjectMan->xTimerUser[0], 300, 0);
						pProjectMan->timerExpireFlag[0] = 0;
					}
				break;
				case 1:
					if(pProjectMan->timerExpireFlag[0])
					{
						DCMotor_Stop(CUTOFF1_MOTOR);
						flag1 = 2;
					}
				break;
				default:
				break;
			}
			
			switch(flag2)
			{
				case 0:
					PhSensor_SingleScan(CUTOFF2_SENSOR_L);
					if(!PhSensor_SingleCheck(CUTOFF2_SENSOR_L))//这个传感器特别一点
					{
						flag2 = 1;
						
						//修改定时器周期并启动
						xTimerChangePeriod( pProjectMan->xTimerUser[1], 380, 0);
						pProjectMan->timerExpireFlag[1] = 0;
					}
				break;
				case 1:
					if(pProjectMan->timerExpireFlag[1])
					{
						DCMotor_Stop(CUTOFF2_MOTOR);
						flag2 = 2;
					}
				break;
				default:
				break;
			}	
			
			vTaskDelay(5);
		}
	}
	else//切断松开
	{
		DCMotor_Run(CUTOFF1_MOTOR, CCW, 100);
		DCMotor_Run(CUTOFF2_MOTOR, CCW, 100);
		
		//修改定时器周期并启动
		xTimerChangePeriod( pProjectMan->xTimerUser[0], 4000/portTICK_PERIOD_MS, 0);
		pProjectMan->timerExpireFlag[0] = 0;
		xTimerChangePeriod( pProjectMan->xTimerUser[1], 4000/portTICK_PERIOD_MS, 0);
		pProjectMan->timerExpireFlag[1] = 0;
		
		while((flag1 != 1) || (flag2 != 1))
		{
			if(*pStopFlag)
			{
				DCMotor_Stop(CUTOFF1_MOTOR);
				DCMotor_Stop(CUTOFF2_MOTOR);
				
				if( xTimerIsTimerActive( pProjectMan->xTimerUser[0] ) == pdTRUE )
					xTimerStop( pProjectMan->xTimerUser[0], 0);
				if( xTimerIsTimerActive( pProjectMan->xTimerUser[1] ) == pdTRUE )
					xTimerStop( pProjectMan->xTimerUser[1], 0);
				
				break;
			}
			
			switch(flag1)
			{
				case 0:
					PhSensor_SingleScan(CUTOFF1_SENSOR_R);
					if((!PhSensor_SingleCheck(CUTOFF1_SENSOR_R)) || pProjectMan->timerExpireFlag[0])
					{
						DCMotor_Stop(CUTOFF1_MOTOR);
						flag1 = 1;
					}
				break;
				default:
				break;
			}
			
			switch(flag2)
			{
				case 0:
					PhSensor_SingleScan(CUTOFF2_SENSOR_R);
					if((!PhSensor_SingleCheck(CUTOFF2_SENSOR_R)) || pProjectMan->timerExpireFlag[1])
					{
						DCMotor_Stop(CUTOFF2_MOTOR);
						flag2 = 1;
					}
				break;
				default:
				break;
			}
			
			vTaskDelay(5);
		}
	}//if(action)
#endif	
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
		if(PhSensor_SingleCheck(sensor))
			return;
	}
	else
	{
		dir = CCW;
		sensor = CUTOFF1_SENSOR_R;
		
		PhSensor_SingleScan(sensor);
		if(!PhSensor_SingleCheck(sensor))
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
			
			vTaskDelay(5000);
			sensorFlag = 1;
		}
		
		if(sensorFlag || *pStopFlag)//这个传感器特别一点
		{
			if(action)//刀片轴有点松，切断时要延迟一点再停
			{
				vTaskDelay(330);
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
	if(!PhSensor_SingleCheck(sensor))
		return;
	
	DCMotor_Run(CUTOFF2_MOTOR, dir, 100);
	while(1)
	{
		PhSensor_SingleScan(sensor);
		if((!PhSensor_SingleCheck(sensor)) || *pStopFlag)
		{
			if(action)//刀片轴有点松，切断时要延迟一点再停
			{
				vTaskDelay(380);
			}
			DCMotor_Stop(CUTOFF2_MOTOR);
			break;
		}
		
		vTaskDelay(5);
	}
}

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

//分离
//action : 0,分离; !=0,分离闭合
//stopFlag : 0,继续动作; !=0,主动退出动作
void Seperation(uint8_t action, uint8_t *pStopFlag)
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
void Disposition(uint8_t action, uint8_t *pStopFlag)
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
void DispositionDistance(uint8_t action, uint32_t distance, uint8_t *pStopFlag)
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
	pProjectMan->heating = 1;
	RELAY = 1;
	while(1)
	{
		if(adcTemp[2].temperature >= pProjectMan->fusingTemperature || *pStopFlag)
			break;
		vTaskDelay(5);
	}
	RELAY = 0;
	pProjectMan->heating = 0;
}

//加热片抬起
//action : 0,加热片回位; !=0,加热片抬起
//stopFlag : 0,继续动作; !=0,主动退出动作
void HeatingUp(uint8_t action, uint8_t *pStopFlag)
{
//	PhSensorEnum_TypeDef sensor;
//	Direction_TypeDef dir;
//	
//	if(action)
//	{
//		dir = CW;
//		sensor = HEATING_SENSOR_L;
//	}
//	else
//	{
//		dir = CCW;
//		sensor = HEATING_SENSOR_R;
//	}
//	
//	PhSensor_SingleScan(sensor);
//	if(!PhSensor_SingleCheck(sensor))
//		return;
//	
//	DCMotor_Run(HEATING_MOTOR, dir, 30);
//	while(1)
//	{
//		PhSensor_SingleScan(sensor);
//		if(!PhSensor_SingleCheck(sensor) || *pStopFlag)
//		{
//			if(action)
//				vTaskDelay(40);			
//			DCMotor_Stop(HEATING_MOTOR);
//			break;
//		}
//		vTaskDelay(5);
//	}

	if(action)
	{
		DCMotor_Run(HEATING_MOTOR, CW, 30);
		vTaskDelay(1000);			
		DCMotor_Stop(HEATING_MOTOR);
	}
	else
	{
		PhSensor_SingleScan(HEATING_SENSOR_R);
		if(!PhSensor_SingleCheck(HEATING_SENSOR_R))
			return;
		
		DCMotor_Run(HEATING_MOTOR, CCW, 30);
		while(1)
		{
			PhSensor_SingleScan(HEATING_SENSOR_R);
			if(!PhSensor_SingleCheck(HEATING_SENSOR_R) || *pStopFlag)
			{	
				DCMotor_Stop(HEATING_MOTOR);
				break;
			}
			vTaskDelay(5);
		}
	}
}

//恢复为原始状态
//stopFlag : 0,继续动作; !=0,主动退出动作
void ResetOriginStatus(uint8_t *pStopFlag)
{
	Seperation(0, pStopFlag); //分离
	HeatingUp(0, pStopFlag); //加热片回位
	Disposition(0, pStopFlag); //错位回位
	Cutoff(1, pStopFlag); //切断，同步回位点，因为切断回位时只用到1个传感器
	Cutoff(0, pStopFlag); //切断回位
	Clamp(0, pStopFlag); //夹紧松开
	Seperation(1, pStopFlag); //分离闭合
}

//自动运行1个周期
//stopFlag : 0,继续动作; !=0,主动退出动作
void AutoRun(uint8_t *pStopFlag)
{
	//Clamp(1, pStopFlag); //夹紧
	pProjectMan->clamp2Flag = 1;
	Clamp1(1, pStopFlag); //夹紧1夹紧，夹紧2夹紧在另外一个线程
	while(1)
	{
		if(pProjectMan->clamp2Flag)
			vTaskDelay(5);
		else
			break;
	}
	
	//HeatingCutoff(pStopFlag); //切断加热片加热
	
	Cutoff(1, pStopFlag); //切断
//	pProjectMan->cutoff2Flag = 1;
//	Cutoff1(1, pStopFlag); //切断1切断，切断2切断在另外一个线程
//	while(1)
//	{
//		if(pProjectMan->cutoff2Flag)
//			vTaskDelay(5);
//		else
//			break;
//	}
	
	Seperation(0, pStopFlag); //分离
	Disposition(1, pStopFlag); //错位
	Cutoff(0, pStopFlag); //切断回位
	Heating(pStopFlag); //熔接加热片加热
	HeatingUp(1, pStopFlag); //加热片抬起
	vTaskDelay(pProjectMan->fusingTime*1000); //延时
	HeatingUp(0, pStopFlag); //加热片放下
	Seperation(1, pStopFlag); //分离闭合
	vTaskDelay(pProjectMan->jointTime*1000); //延时
	Clamp(0, pStopFlag); //夹紧松开
	DispositionDistance(0, 17000, pStopFlag); //错位回来一点

#if 0	
	Clamp1(1, pStopFlag); //夹紧
	HeatingCutoff2(pStopFlag); //切断加热片加热
	Cutoff2(1, pStopFlag); //切断
	
	vTaskDelay(5000);
	//vTaskDelay(5000);
	
	Seperation(0, pStopFlag); //分离
	Cutoff2(0, pStopFlag); //切断
#endif

#if 0	
	Clamp2(1, pStopFlag); //夹紧
	HeatingCutoff1(pStopFlag); //切断加热片加热
	Cutoff1(1, pStopFlag); //切断
	
	vTaskDelay(5000);
	vTaskDelay(5000);
	
	Seperation(0, pStopFlag); //分离
	Cutoff1(0, pStopFlag); //切断回位
#endif

}

void ProjectTask(void)
{
	while(1)
	{
#if 1	
		if(pProjectMan->projectStatus&PROJECT_RUNNING)
		{
			switch(pProjectMan->projectStatus&0x7F)
			{
				case PROJECT_TEST_CLAMP1CW:
					Clamp1(1, &(pProjectMan->projectStopFlag));
				
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP1CW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP1CW_BUTTON, 0);
					//GetControlValue(TESTPAGE_INDEX, TEST_CLAMP1CW_BUTTON);
					
				break;
				case PROJECT_TEST_CLAMP1CCW:
					Clamp1(0, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP1CCW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP1CCW_BUTTON, 0);
				break;
				case PROJECT_TEST_CLAMP2CW:
					Clamp2(1, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP2CW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP2CW_BUTTON, 0);
				break;
				case PROJECT_TEST_CLAMP2CCW:
					Clamp2(0, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP2CCW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CLAMP2CCW_BUTTON, 0);
				break;
				case PROJECT_TEST_CUTOFF1CW:
					Cutoff1(1, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF1CW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF1CW_BUTTON, 0);
				break;
				case PROJECT_TEST_CUTOFF1CCW:
					Cutoff1(0, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF1CCW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF1CCW_BUTTON, 0);
				break;
				case PROJECT_TEST_CUTOFF2CW:
					Cutoff2(1, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF2CW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF2CW_BUTTON, 0);
				break;
				case PROJECT_TEST_CUTOFF2CCW:
					Cutoff2(0, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF2CCW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_CUTOFF2CCW_BUTTON, 0);
				break;
				case PROJECT_TEST_HEATINGUP:
					HeatingUp(1, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_HEATINGUP_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_HEATINGUP_BUTTON, 0);
				break;
				case PROJECT_TEST_HEATINGDOWN:
					HeatingUp(0, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_HEATINGDOWN_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_HEATINGDOWN_BUTTON, 0);
				break;
				case PROJECT_TEST_SEPATATIONCW:
					Seperation(1, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_SEPERATECW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_SEPERATECW_BUTTON, 0);
				break;
				case PROJECT_TEST_SEPATATIONCCW:
					Seperation(0, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_SEPERATECCW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_SEPERATECCW_BUTTON, 0);
				break;
				case PROJECT_TEST_DISPOSITIONCW:
					Disposition(1, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_DISPOSCW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_DISPOSCW_BUTTON, 0);
				break;
				case PROJECT_TEST_DISPOSITIONCCW:
					Disposition(0, &(pProjectMan->projectStopFlag));
					SetButtonValue(TESTPAGE_INDEX, TEST_DISPOSCCW_BUTTON, 0);
					SetButtonValue(TESTPAGE_INDEX, TEST_DISPOSCCW_BUTTON, 0);
				break;
				case PROJECT_PARAMETER_RESET:
					ResetOriginStatus(&(pProjectMan->projectStopFlag));
					SetButtonValue(PARAMETERPAGE_INDEX, PARAMETER_RESET_BUTTON, 0);
					SetButtonValue(PARAMETERPAGE_INDEX, PARAMETER_RESET_BUTTON, 0);
				break;
				case PROJECT_PARAMETER_AUTO:
					AutoRun(&(pProjectMan->projectStopFlag));
					SetButtonValue(PARAMETERPAGE_INDEX, PARAMETER_AUTO_BUTTON, 0);
					SetButtonValue(PARAMETERPAGE_INDEX, PARAMETER_AUTO_BUTTON, 0);
				break;
			}
			pProjectMan->projectStatus = 0;
			pProjectMan->projectStopFlag = 0;
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
