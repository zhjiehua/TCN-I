#include "Button.h"
#include "usart.h"
#include "stm32f10x_exti.h"
#include "PhotoelectricSensor/PhSensor.h"
#include "../Logic/managerment.h"
#include "../DCMotor/DCMotor.h"
#include "../StepMotor/StepMotor.h"
#include "../RelayMOS/RelayMOS.h"
#include "../WDG/WDG.h"
#include "../HARDWARE/24CXX/24cxx.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//·äÃùÆ÷Çý¶¯´úÂë	   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ÐÞ¸ÄÈÕÆÚ:2012/9/2
//°æ±¾£ºV1.0
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

Button_TypeDef button[BUTTON_COUNT];

//³õÊ¼»¯PB8ÎªÊä³ö¿Ú.²¢Ê¹ÄÜÕâ¸ö¿ÚµÄÊ±ÖÓ		    
//·äÃùÆ÷³õÊ¼»¯
void Button_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);	 //Ê¹ÄÜGPIOB¶Ë¿ÚÊ±ÖÓ

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//BEEP-->PB.8 ¶Ë¿ÚÅäÖÃ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //ÉÏÀ­ÊäÈë
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //ËÙ¶ÈÎª50MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);	 //¸ù¾Ý²ÎÊý³õÊ¼»¯GPIOB.8
    
    // NVIC ÅäÖÃ
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//ÇÀÕ¼ÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		//×ÓÓÅÏÈ¼¶3
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷  
    
    //Íâ²¿ÖÐ¶ÏÅäÖÃ
    EXTI_ClearITPendingBit(EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    EXTI_Init(&EXTI_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	uint8_t i;
	uint32_t oldBasePri = portSET_INTERRUPT_MASK_FROM_ISR();
	
    button[0].flag = 1;

	//¹ÒÆðËùÓÐÈÎÎñ
//	vTaskSuspend(pProjectMan->projectTaskHandle);
//	vTaskSuspend(pProjectMan->uiTaskHandle);
//	vTaskSuspend(pProjectMan->heatingUpTaskHandle);
//	vTaskSuspend(pProjectMan->dislocationTaskHandle);
//	vTaskSuspend(pProjectMan->separationTaskHandle);
//	vTaskSuspend(pProjectMan->cutoff2TaskHandle);
//	vTaskSuspend(pProjectMan->cutoff1TaskHandle);
//	vTaskSuspend(pProjectMan->clamp2TaskHandle);
//	vTaskSuspend(pProjectMan->clamp1TaskHandle);
	
	//¼±Í££¬Í£Ö¹ËùÓÐµç»úºÍ¼ÓÈÈÆ¬µÈÊä³ö
	for(i=0;i<DCMOTOR_COUNT;i++)
	{
		DCMotor_Stop((DCMotorEnum_TypeDef)i);
	}
	for(i=0;i<STEPMOTOR_COUNT;i++)
	{
		StepMotor_Stop(i);
		TIM_Cmd(StepMotorPin[i].TIMx, DISABLE);
	}
	RELAY = 0;

	pProjectMan->systemEmergencyButtonPressFlag = 1;
	
//	//ÌáÊ¾ÖØÐÂÉÏµç
//	SetTextValue(TIPSPAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"1 ÇëËÉ¿ª¼±Í£°´Å¥£»\r\n2 ÇëÖØÐÂÉÏµç£¡");
//	SetScreen(TIPSPAGE_INDEX);
//	
//	IWDG_Feed();//Î¹¹·	
//	pProjectMan->systemEmergencyFlag = 1;
//	AT24CXX_Write(EMERGENCYFLAG_BASEADDR, (uint8_t*)(&(pProjectMan->systemEmergencyFlag)), 1);
//	IWDG_Feed();//Î¹¹·	
//	
//	while(1)
//	{
//		//ÌáÊ¾ÖØÐÂÉÏµç
//		SetTextValue(TIPSPAGE_INDEX, TIPS_TIPS_EDIT, (uint8_t*)"1 ÇëËÉ¿ª¼±Í£°´Å¥£»\r\n2 ÇëÖØÐÂÉÏµç£¡");
//		SetScreen(TIPSPAGE_INDEX);
//		IWDG_Feed();//Î¹¹·	
//	}
	
    EXTI_ClearITPendingBit(EXTI_Line0);
	portCLEAR_INTERRUPT_MASK_FROM_ISR(oldBasePri);
}

void EXTI1_IRQHandler(void)
{
    button[1].flag = 1;
	
	pProjectMan->tipsBuzzeFlag = 0;//¹Ø·äÃùÆ÷
	
	if(!(pProjectMan->projectStatus&PROJECT_RUNNING) && pProjectMan->systemPowerUpFlag)
	{
		if(pProjectMan->autoButtonFlag)
		{
			pProjectMan->autoNResetFlag = 1;//¸´Î»
			//pProjectMan->autoButtonFlag = 0;
		}
		else
		{
			pProjectMan->autoNResetFlag = 2;//×Ô¶¯
			//pProjectMan->autoButtonFlag = 1;
		}
	}
	
    EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
    button[2].flag = 1;
    
    EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
    button[3].flag = 1;
    
    EXTI_ClearITPendingBit(EXTI_Line3);
}
