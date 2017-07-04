#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "LED/led.h"
#include "Key/key.h"
#include "Beep/beep.h"
#include "Button/Button.h"
#include "PhotoelectricSensor/PhSensor.h"
#include "RelayMOS/RelayMOS.h"
#include "DCMotor/DCMotor.h"
#include "StepMotor/StepMotor.h"
#include "WDG/WDG.h"
#include "NTCResistor/NTCResistor.h"

#include "../Logic/managerment.h"
#include "CPrintf.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/************************************************

************************************************/
#define uart_TASK_PRIORITY           	( tskIDLE_PRIORITY + 3 )
#define project_TASK_PRIORITY           ( tskIDLE_PRIORITY + 2 )
#define ui_TASK_PRIORITY                ( tskIDLE_PRIORITY + 1 )

#define uart_TASK_STACKDEP            	( 100 )
#define project_TASK_STACKDEP           ( 100 )
#define ui_TASK_STACKDEP                ( 150 )

void UartTask(void);
void ProjectTask(void);
void UITask(void);

//主函数    500 / portTICK_PERIOD_MS = 500ms
int main(void)
{
//	uint8_t size;
//	size = sizeof(uint64_t);
//	printf("sizeof = ", size);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();			//初始化LED
	//AT24CXX_Init();
	Beep_Init();
	Button_Init();
	PhSensor_Init();
	RelayMOS_Init();
	DCMotor_Init();
	StepMotor_Init();
	NTCResitor_Init();
	
	initUI();
	initSoftwareTimer();
	
	//IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s
    
	cDebug("hello TCN-I project!\r\n");
	
	/* Start the tasks defined within this file/specific to this demo. */
	xTaskCreate( (TaskFunction_t)UITask, "UITask", ui_TASK_STACKDEP, NULL, ui_TASK_PRIORITY, NULL );
	xTaskCreate( (TaskFunction_t)UartTask, "UartTask", uart_TASK_STACKDEP, NULL, uart_TASK_PRIORITY, NULL );
	xTaskCreate( (TaskFunction_t)ProjectTask, "ProjectTask", project_TASK_STACKDEP, NULL, project_TASK_PRIORITY, NULL );
	
	/* Start the scheduler. */
	vTaskStartScheduler();
	
	return 0;
}

