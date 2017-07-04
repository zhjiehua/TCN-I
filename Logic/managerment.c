#include "managerment.h"
#include "stddef.h"
#include "string.h"
#include "stdio.h"
#include "CPrintf.h"
#include "../HARDWARE/DCMotor/dcmotor.h"
#include "../HARDWARE/StepMotor/stepmotor.h"
#include "../HARDWARE/Beep/beep.h"
#include "../HARDWARE/24CXX/24cxx.h"
#include "../HMI/hmi_driver.h"
#include "../HMI/hmi_user_uart.h"
#include "NTCResistor/NTCResistor.h"
#include "LED/led.h"
#include "RelayMOS/RelayMOS.h"
#include "../PID/PID.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CUTOFF1HEATINGTEMP	112.0 //115.0
#define CUTOFF2HEATINGTEMP	117.0 //120.0	
#define HEATINGTEMP			160.0	
	
/************************************************************************/
/* 定义项目管理结构体                                                   */
/************************************************************************/
static ProjectMan_TypeDef ProjectMan;
ProjectMan_TypeDef *pProjectMan = &ProjectMan;

/************************************************************************/
/* 串口接收缓冲区                                                       */
/************************************************************************/
uint8 cmd_buffer[CMD_MAX_SIZE];

#define EEPROM_DEFAULT 0x11223345

//定时器回调函数
void vTimerCallback( TimerHandle_t xTimer )
{
	// do something no block
	// 获取定时器ID
	uint32_t ulID = ( uint32_t ) pvTimerGetTimerID( xTimer );

	pProjectMan->timerExpireFlag[ulID] = 1;
	
	//停止定时器
	xTimerStop( xTimer, 0 );
}

//初始化软件定时器
void initSoftwareTimer(void)
{
	uint32_t i;
	for(i=0;i<SOFTWARETIMER_COUNT;i++)
	{
		//申请定时器
		pProjectMan->xTimerUser[i] = xTimerCreate
					   //定时器名字，只在调试时候用
					   ("Timer's name",
					   //溢出周期，这里设置成10ms
					   10 / portTICK_PERIOD_MS,   
					   //是否自动重载，这里设置为自动重载
					   pdTRUE,
					   //用于识别是哪个定时器调用回调函数
					  ( void * ) i,
					   //回调函数
					  vTimerCallback);

		 if( pProjectMan->xTimerUser[i] != NULL ) {
			//启动定时器，0表示不阻塞
			xTimerStart( pProjectMan->xTimerUser[i], 0 );
		}
		else
		{
			while(1);
		}
	}
}

void initUI(void)
{
	//初始化项目结构体
	int16 i;
	uint32 j;
	uint32_t dat;

    UartInit(38400);

#if 0    
	AT24CXX_Read(RESET_DEFAULT, (uint8_t*)(&dat), sizeof(uint32_t));//是否第一次开机，读3次
	if(dat != EEPROM_DEFAULT)
		AT24CXX_Read(RESET_DEFAULT, (uint8_t*)(&dat), sizeof(uint32_t));
	if(dat != EEPROM_DEFAULT)
		AT24CXX_Read(RESET_DEFAULT, (uint8_t*)(&dat), sizeof(uint32_t));

	if(dat != EEPROM_DEFAULT) //是，初始化EEPROM中的数据
	{
		cDebug("RESET_DEFAULT\n");

		pProjectMan->lang = English;
		AT24CXX_Write(LANGUAGE_BASEADDR, (uint8_t*)(&pProjectMan->lang), LANGUAGE_SIZE);

//		SetScreen(TIPS0PAGE_INDEX);//跳转到提示0页面
//		//if(pProjectMan->lang == 0)
//			SetTextValue(TIPS0PAGE_INDEX, TIPS0_TIPS_EDIT, (uint8_t*)"Restore factory settings……");
//		//else
//		//	SetTextValue(TIPS0PAGE_INDEX, TIPS0_TIPS_EDIT, "正在恢复出厂设置……");
		
		pProjectMan->cutoff1Temperature = CUTOFF1HEATINGTEMP;
		pProjectMan->cutoff2Temperature = CUTOFF2HEATINGTEMP;
		pProjectMan->fusingTemperature = HEATINGTEMP;
		
		pProjectMan->cutoffTime = 4;
		pProjectMan->fusingTime = 4;
		pProjectMan->jointTime = 4;
		
		AT24CXX_Write(CUTOFF1TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff1Temperature, CUTOFF1TEMP_SIZE);
		AT24CXX_Write(CUTOFF2TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff2Temperature, CUTOFF2TEMP_SIZE);
		AT24CXX_Write(FUSINGTEMP_BASEADDR, (uint8_t*)&pProjectMan->fusingTemperature, FUSINGTEMP_SIZE);
		AT24CXX_Write(CUTOFFTIME_BASEADDR, (uint8_t*)&pProjectMan->cutoffTime, CUTOFFTIME_SIZE);
		AT24CXX_Write(FUSINGTIME_BASEADDR, (uint8_t*)&pProjectMan->fusingTime, FUSINGTIME_SIZE);
		AT24CXX_Write(JOINTTIME_BASEADDR, (uint8_t*)&pProjectMan->jointTime, JOINTTIME_SIZE);
		
		dat = EEPROM_DEFAULT;
		AT24CXX_Write(RESET_DEFAULT, (uint8_t*)&dat, sizeof(uint32_t));

		SetScreen(LOGOPAGE_INDEX);//跳转到LOGO页面
	}
	else //否，从EEPROM中读取数据
	{
		cDebug("read data from EEPROM\n");

		AT24CXX_Read(LANGUAGE_BASEADDR, (uint8_t*)(&pProjectMan->lang), LANGUAGE_SIZE); //读出语言参数

//		if(pProjectMan->lang == 0)
//		{
//			SetTextValue(LOGOPAGE_INDEX, LOGO_STATUS_EDIT, (uint8_t*)"System initializing……");
//		}
//		else
//			SetTextValue(LOGOPAGE_INDEX, LOGO_STATUS_EDIT, (uint8_t*)"系统初始化中……");

		AT24CXX_Read(CUTOFF1TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff1Temperature, CUTOFF1TEMP_SIZE);
		AT24CXX_Read(CUTOFF2TEMP_BASEADDR, (uint8_t*)&pProjectMan->cutoff2Temperature, CUTOFF2TEMP_SIZE);
		AT24CXX_Read(FUSINGTEMP_BASEADDR, (uint8_t*)&pProjectMan->fusingTemperature, FUSINGTEMP_SIZE);
		AT24CXX_Read(CUTOFFTIME_BASEADDR, (uint8_t*)&pProjectMan->cutoffTime, CUTOFFTIME_SIZE);
		AT24CXX_Read(FUSINGTIME_BASEADDR, (uint8_t*)&pProjectMan->fusingTime, FUSINGTIME_SIZE);
		AT24CXX_Read(JOINTTIME_BASEADDR, (uint8_t*)&pProjectMan->jointTime, JOINTTIME_SIZE);
	}
#endif
	
//   	//设置语言
//	if(pProjectMan->lang == 0)
//		SetLanguage(0, 0);
//	else
//		SetLanguage(0, 1);

	//初始化项目管理结构体
	pProjectMan->cutoff1Temperature = CUTOFF1HEATINGTEMP;
	pProjectMan->cutoff2Temperature = CUTOFF2HEATINGTEMP;
	pProjectMan->fusingTemperature = HEATINGTEMP;
	pProjectMan->cutoffTime = 4;
	pProjectMan->fusingTime = 2;
	pProjectMan->jointTime = 4;
	
	//设置温度控件值SetTextFloat
	SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_CUTOFFTEMP_EDIT, pProjectMan->cutoff1Temperature, 0, 0);
	SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_CUTOFFTEMP_EDIT, pProjectMan->cutoff1Temperature, 0, 0);
	SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_FUSINGTEMP_EDIT, pProjectMan->fusingTemperature, 0, 0);
	SetTextInt32(PARAMETERPAGE_INDEX, PARAMETER_FUSINGTEMP_EDIT, pProjectMan->fusingTemperature, 0, 0);

	/*清空串口接收缓冲区*/
	queue_reset();

	//延时一段时间
	for(j=0;j<65536;j++);

	cDebug("initUI success\n");

	//发送握手命令
	SetHandShake();//发送握手命令
	SetHandShake();//发送握手命令，第一个握手命令会丢失
	//SetHandShake();//发送握手命令
	
	//SetScreen(MAINPAGE_INDEX);
	SetScreen(PARAMETERPAGE_INDEX);
	
	//除能主界面的状态按钮
	for(j=1;j<=9;j++)
		SetControlEnable(MAINPAGE_INDEX, j, 0);

	//除能输入点界面的状态按钮
	for(j=1;j<=16;j++)
		SetControlEnable(INPUTPAGE_INDEX, j, 0);
}

void UITask(void)
{
    qsize size;
	
	uint8_t pwmPercent;
	int32_t pidOut;
	
	PID_Init(&(pProjectMan->cutoff1PID), 8.0, 0.0, 0.0);
	PID_UpdateSetPoint(&(pProjectMan->cutoff1PID), pProjectMan->cutoff1Temperature);
	
	PID_Init(&(pProjectMan->cutoff2PID), 8.0, 0.0, 0.0);
	PID_UpdateSetPoint(&(pProjectMan->cutoff2PID), pProjectMan->cutoff2Temperature);
	
    while(1)
    {
        //处理UI数据
		size = queue_find_cmd(cmd_buffer, CMD_MAX_SIZE); //从缓冲区获取一条指令
		if(size > 0)//接收到指令
		{
			ProcessMessage((PCTRL_MSG)cmd_buffer, size);//处理指令
		}
        
        //IWDG_Feed();//喂狗
        
		NTCResistorTask(); //更新温度值
		
		PhSensorScanTask();	//更新输入点
		
		LED1Task(); //LED1闪烁指示UI线程正在运行

#if 1
		//PID调节
		if(adcTemp[0].temperature < pProjectMan->cutoff1Temperature)
		{
			if(pProjectMan->cutoff1Temperature - adcTemp[0].temperature > 10)
			{
				pwmPercent = 100;
			}
			else
			{
				PID_UpdateActualPoint(&(pProjectMan->cutoff1PID), adcTemp[0].temperature);
				pidOut = PID_Calc(&(pProjectMan->cutoff1PID));
				//pwmPercent += pidOut;
				cDebug("---pidOut1 = %d\r\n", pidOut);
				if(pidOut > 5)
					pwmPercent = 100;
				else
					pwmPercent = (pidOut+5)*100/(5+5);
				//cDebug("---pwmPercent = %d\r\n", pwmPercent);
			}
		}
		else
		{
			if(adcTemp[0].temperature - pProjectMan->cutoff1Temperature > 5)
			{
				pwmPercent = 0;
			}
			else
			{
				PID_UpdateActualPoint(&(pProjectMan->cutoff1PID), adcTemp[0].temperature);
				pidOut = PID_Calc(&(pProjectMan->cutoff1PID));
				//pwmPercent += pidOut;
				//pwmPercent = pidOut;
				cDebug("+++pidOut1 = %d\r\n", pidOut);
				if(pidOut < -5)
					pwmPercent = 0;
				else
					pwmPercent = (pidOut+5)*100/(5+5);
				//cDebug("+++pwmPercent = %d\r\n", pwmPercent);
			}
		}
		
		if(pwmPercent >= 100)
			pwmPercent = 100;
		else if(pwmPercent <= 0)
			pwmPercent = 0;
		
		DCMotor_Run(CUTOFF1HEATDCMOTOR1, CW, pwmPercent);
		DCMotor_Run(CUTOFF1HEATDCMOTOR2, CW, pwmPercent);
		//printf("DCMotor Percent = %d\r\n", percent);

		//====================================================================================
		if(adcTemp[1].temperature < pProjectMan->cutoff2Temperature)
		{
			if(pProjectMan->cutoff2Temperature - adcTemp[1].temperature > 10)
			{
				pwmPercent = 100;
			}
			else
			{
				PID_UpdateActualPoint(&(pProjectMan->cutoff2PID), adcTemp[1].temperature);
				pidOut = PID_Calc(&(pProjectMan->cutoff2PID));
				//pwmPercent += pidOut;
				cDebug("---pidOut2 = %d\r\n", pidOut);
				if(pidOut > 5)
					pwmPercent = 100;
				else
					pwmPercent = (pidOut+5)*100/(5+5);
				//cDebug("---pwmPercent = %d\r\n", pwmPercent);
			}
		}
		else
		{
			if(adcTemp[1].temperature - pProjectMan->cutoff2Temperature > 5)
			{
				pwmPercent = 0;
			}
			else
			{
				PID_UpdateActualPoint(&(pProjectMan->cutoff2PID), adcTemp[1].temperature);
				pidOut = PID_Calc(&(pProjectMan->cutoff2PID));
				//pwmPercent += pidOut;
				//pwmPercent = pidOut;
				cDebug("+++pidOut2 = %d\r\n", pidOut);
				if(pidOut < -5)
					pwmPercent = 0;
				else
					pwmPercent = (pidOut+5)*100/(5+5);
				//cDebug("+++pwmPercent = %d\r\n", pwmPercent);
			}
		}
		
		if(pwmPercent >= 100)
			pwmPercent = 100;
		else if(pwmPercent <= 0)
			pwmPercent = 0;
		
		DCMotor_Run(CUTOFF2HEATDCMOTOR1, CW, pwmPercent);
		DCMotor_Run(CUTOFF2HEATDCMOTOR2, CW, pwmPercent);
		
		//=================================================================
		if(!pProjectMan->heating)
		{
			if(adcTemp[2].temperature >= pProjectMan->cutoff2Temperature+10)
			{
				RELAY = 0;
			}
			else if(adcTemp[2].temperature <= (pProjectMan->cutoff2Temperature+5))
			{
				RELAY = 1;
			}
		}
#endif
		
        vTaskDelay(10);
    }
}

#ifdef __cplusplus
}
#endif
