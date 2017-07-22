#ifndef _MANAGERMENT_H_
#define _MANAGERMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "project.h"
#include "../UILogic/pageCommon.h"
#include "../HMI/cmd_queue.h"
#include "../HMI/cmd_process.h"
#include "../HMI/hmi_user_uart.h"
#include "../PID/PID.h"
	
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#define TEMPERATURE_MASK 0
	
#define SOFTWARETIMER_COUNT 3

//定义EEPROM地址功能
#define POWERONTEST_BASEADDR		0
#define LANGUAGE_BASEADDR 			(POWERONTEST_BASEADDR+4)
//温度参数页面	
#define CUTOFF1KP_BASEADDR			(LANGUAGE_BASEADDR+1)
#define CUTOFF1KI_BASEADDR			(CUTOFF1KP_BASEADDR+4)
#define CUTOFF1KD_BASEADDR			(CUTOFF1KI_BASEADDR+4)
#define CUTOFF2KP_BASEADDR			(CUTOFF1KD_BASEADDR+4)
#define CUTOFF2KI_BASEADDR			(CUTOFF2KP_BASEADDR+4)
#define CUTOFF2KD_BASEADDR			(CUTOFF2KI_BASEADDR+4)
#define CUTOFF1TEMP_BASEADDR		(CUTOFF2KD_BASEADDR+4)
#define CUTOFF2TEMP_BASEADDR		(CUTOFF1TEMP_BASEADDR+4)
#define FUSINGTEMP_BASEADDR			(CUTOFF2TEMP_BASEADDR+4)
#define FUSINGHOLDINGTEMP_BASEADDR	(FUSINGTEMP_BASEADDR+4)
//时间参数页面
#define CLAMP1DELAY_BASEADDR		(FUSINGHOLDINGTEMP_BASEADDR+4)
#define CLAMP2DELAY_BASEADDR		(CLAMP1DELAY_BASEADDR+4)
#define CUTOFF1DELAY_BASEADDR		(CLAMP2DELAY_BASEADDR+4)
#define CUTOFF2DELAY_BASEADDR		(CUTOFF1DELAY_BASEADDR+4)
#define CUTOFFRETURN_BASEADDR		(CUTOFF2DELAY_BASEADDR+4)
#define CUTOFFTIME_BASEADDR			(CUTOFFRETURN_BASEADDR+4)
#define FUSINGTIME_BASEADDR			(CUTOFFTIME_BASEADDR+4)
#define JOINTTIME_BASEADDR			(FUSINGTIME_BASEADDR+4)
#define HEATINGUPDELAY_BASEADDR		(JOINTTIME_BASEADDR+4)
#define HEATINGDOWNDELAY_BASEADDR	(HEATINGUPDELAY_BASEADDR+4)

//电机参数页面
#define DISLOCATERETURN_BASEADDR	(HEATINGDOWNDELAY_BASEADDR+4)
#define DISLOCATESPEED_BASEADDR		(DISLOCATERETURN_BASEADDR+4)
#define HEATINGUPSPEED_BASEADDR		(DISLOCATESPEED_BASEADDR+1)
#define HEATINGDOWNSPEED_BASEADDR	(HEATINGUPSPEED_BASEADDR+1)
#define CUTOFF1HEATINGVOL_BASEADDR	(HEATINGDOWNSPEED_BASEADDR+1)
#define CUTOFF2HEATINGVOL_BASEADDR	(CUTOFF1HEATINGVOL_BASEADDR+1)
#define FUSINGHEATINGVOL_BASEADDR	(CUTOFF2HEATINGVOL_BASEADDR+1)

#define TOTALOUTPUT_BASEADDR		(FUSINGHEATINGVOL_BASEADDR+1)

#define EMERGENCYFLAG_BASEADDR		(TOTALOUTPUT_BASEADDR+4)

#define RESTOREDEFAULT_BASEADDR		(EMERGENCYFLAG_BASEADDR+100)

//定义电机对应功能
#define CLAMP1_MOTOR		DCMOTOR1	//夹紧1
#define CLAMP2_MOTOR		DCMOTOR2	//夹紧2
#define CUTOFF1_MOTOR		DCMOTOR3	//切断1
#define CUTOFF2_MOTOR		DCMOTOR4	//切断2
#define	HEATING_MOTOR		DCMOTOR5	//加热片抬起
#define	SAPERATE_MOTOR		DCMOTOR6	//分离
#define STARTLAMP_MOTOR		DCMOTOR7	//启动开关的灯
#define	DISPOS_MOTOR		0			//错位
#define CUTOFF1HEATDCMOTOR1 DCMOTOR9	//切断1加热片1
#define CUTOFF1HEATDCMOTOR2 DCMOTOR10	//切断1加热片2
#define CUTOFF2HEATDCMOTOR1 DCMOTOR11	//切断2加热片1
#define CUTOFF2HEATDCMOTOR2 DCMOTOR12	//切断2加热片2

//定义传感器对应功能
#define CLAMP1_SENSOR_L		PHSENSOR16
#define CLAMP1_SENSOR_R		PHSENSOR15
#define CLAMP2_SENSOR_L		PHSENSOR14
#define CLAMP2_SENSOR_R		PHSENSOR13
#define CUTOFF1_SENSOR_L	PHSENSOR2
#define CUTOFF1_SENSOR_R	PHSENSOR1
#define CUTOFF2_SENSOR_L	PHSENSOR12
#define CUTOFF2_SENSOR_R	PHSENSOR11
#define HEATING_SENSOR_L	PHSENSOR4
#define HEATING_SENSOR_R	PHSENSOR3
#define SAPERATE_SENSOR_L	PHSENSOR8   //PHSENSOR10暂时检测不到
#define SAPERATE_SENSOR_R	PHSENSOR9
#define DISPOS_SENSOR_L		PHSENSOR6
#define DISPOS_SENSOR_R		PHSENSOR5

//项目程序代号
#define PROJECT_MANUAL_CLAMP1CW			1
#define PROJECT_MANUAL_CLAMP1CCW		2
#define PROJECT_MANUAL_CLAMP2CW			3
#define PROJECT_MANUAL_CLAMP2CCW		4
#define PROJECT_MANUAL_CUTOFF1CW		5
#define PROJECT_MANUAL_CUTOFF1CCW		6
#define PROJECT_MANUAL_CUTOFF2CW		7
#define PROJECT_MANUAL_CUTOFF2CCW		8
#define PROJECT_MANUAL_SEPATATIONCW		9
#define PROJECT_MANUAL_SEPATATIONCCW	10
#define PROJECT_MANUAL_DISLOCATIONCW	11
#define PROJECT_MANUAL_DISLOCATIONCCW	12
#define PROJECT_MANUAL_HEATINGUP		13
#define PROJECT_MANUAL_HEATINGDOWN		14
#define PROJECT_MANUAL_HEATON			15
#define PROJECT_STATUS_CUTOFF1			16
#define PROJECT_STATUS_CUTOFF2			17
#define PROJECT_STATUS_AUTO				18
#define PROJECT_STATUS_RESET			19

#define PROJECT_RUNNING					0x80

//程序任务事件组标志的位置
#define PROJECT_EVENTPOS_CLAMP1			0
#define PROJECT_EVENTPOS_CLAMP2			1
#define PROJECT_EVENTPOS_CUTOFF1		2
#define PROJECT_EVENTPOS_CUTOFF2		3
#define PROJECT_EVENTPOS_SEPATATION		4
#define PROJECT_EVENTPOS_DISLOCATION	5
#define PROJECT_EVENTPOS_HEATINGUP		6
//#define PROJECT_EVENTPOS_HEATINGUP		6

typedef enum
{
	TIPS_NONE,
	TIPS_CANCEL,
	TIPS_OK,
}TipsButton_TypeDef;

typedef enum
{
	English = 0,
	Chinese,
}Language_TypeDef;

/************************************************************************/
/* 项目管理结构体                                                       */
/************************************************************************/
typedef struct
{
	uint8_t projectStatus; //bit7表示测试程序正在运行，bit6~bit0对应项目程序代号
	uint8_t projectStopFlag; //强制停止测试测试
	uint8_t projectCurrentStatus; //当前状态，用于LCD显示
	uint8_t tipsOKButtonFlag;
	uint8_t tipsBuzzeFlag;
	
	uint8_t autoButtonFlag; 
	uint8_t autoNResetFlag; //1:复位；2:自动
	uint8_t systemPowerUpFlag; //1：系统已经正常启动
	
	uint8_t systemEmergencyFlag; //系统上一次关电前是否有按急停
	uint8_t systemEmergencyButtonPressFlag;
	
	SemaphoreHandle_t projectStatusSem;
	EventGroupHandle_t projectEventGroup;
	
	SemaphoreHandle_t lcdUartSem;
	
	PID_TypeDef cutoff1PID;
	PID_TypeDef cutoff2PID;
	
	float cutoff1Temperature;  //切断1温度
	float cutoff2Temperature;  //切断2温度
	float fusingTemperature;  //熔接温度
	float fusingHoldingTemperature; //熔接维持温度
	uint8_t cutoff1TempControlFlag;
	uint8_t cutoff2TempControlFlag;
	uint8_t fusingTempControlFlag;
	uint8_t fusingRaisingTempControlFlag;
	uint8_t heatingUpFlag;//可以抬起加热片
	
	uint32_t clamp1Delay;	//夹紧1延时
	uint32_t clamp2Delay;	//夹紧2延时
	uint32_t cutoff1Delay;	//切断1延时
	uint32_t cutoff2Delay;	//切断2延时
	uint32_t cutoffReturnDelay;	//切断回位延时
	uint32_t cutoffTime;	//切断时间
	uint32_t fusingTime;	//熔接时间
	uint32_t jointTime;		//接合时间
	uint32_t heatingUpDelay;	//加热抬起延时
	uint32_t heatingDownDelay;
	
	uint32_t dislocateReturn; //错位回位偏移脉冲数
	uint8_t dislocateSpeed;
	uint8_t heatingUpSpeed;
	uint8_t heatingDownSpeed;
	uint8_t cutoff1HeatingVoltage;
	uint8_t cutoff2HeatingVoltage;
	uint8_t fusingHeatingVoltage;
	
	uint8_t clamp2Flag;
	uint8_t cutoff2Flag;
	
	TimerHandle_t xTimerUser[SOFTWARETIMER_COUNT];
	uint8_t timerExpireFlag[SOFTWARETIMER_COUNT];
	
	uint8_t clamp1Action;  //夹紧1
	uint8_t clamp2Action;	//夹紧2
	uint8_t cutoff1Action;	//切断1
	uint8_t cutoff2Action;	//切断2
	uint8_t separationAction;	//分离
	uint8_t dislocationAction;	//错位
	uint8_t heatingUpAction;	//加热抬起
	TaskHandle_t clamp1TaskHandle;
	TaskHandle_t clamp2TaskHandle;
	TaskHandle_t cutoff1TaskHandle;
	TaskHandle_t cutoff2TaskHandle;
	TaskHandle_t separationTaskHandle;
	TaskHandle_t dislocationTaskHandle;
	TaskHandle_t heatingUpTaskHandle;
	TaskHandle_t projectTaskHandle;
	TaskHandle_t uiTaskHandle;
	
	Language_TypeDef lang;
	uint32_t totalOutput;
	uint8_t inInputPageFlag;
	uint8_t inStatusPageFlag;
	uint8_t lcdNotifyResetFlag;
}ProjectMan_TypeDef;

/************************************************************************/
/*                                                                      */
/************************************************************************/

extern ProjectMan_TypeDef *pProjectMan;
extern uint8 cmd_buffer[CMD_MAX_SIZE];

void initProjectMan(ProjectMan_TypeDef *pm);
void initUI(void);
void initSoftwareTimer(void);

void UITask(void);
	
#ifdef __cplusplus
}
#endif

#endif
