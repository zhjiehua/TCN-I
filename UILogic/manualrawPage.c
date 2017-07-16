#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"

#include "../DCMotor/DCMotor.h"
#include "StepMotor/StepMotor.h"
#include "RelayMOS/RelayMOS.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DCMOTORSPEED 100	

void manualrawPageButtonProcess(uint16 control_id, uint8 state)
{
	switch(control_id)
	{
		case MANUALRAW_CLAMP1CW_BUTTON: //夹紧1正转
		{
			if(state)
				DCMotor_Run(CLAMP1_MOTOR, CW, DCMOTORSPEED);//DCMOTORSPEED
			else
				DCMotor_Stop(CLAMP1_MOTOR);
		}
		break;
		case MANUALRAW_CLAMP1CCW_BUTTON:
		{
			if(state)
				DCMotor_Run(CLAMP1_MOTOR, CCW, DCMOTORSPEED);//DCMOTORSPEED
			else
				DCMotor_Stop(CLAMP1_MOTOR);
		}
		break;
		case MANUALRAW_CLAMP2CW_BUTTON: //夹紧2正转
		{
			if(state)
				DCMotor_Run(CLAMP2_MOTOR, CW, DCMOTORSPEED);//DCMOTORSPEED
			else
				DCMotor_Stop(CLAMP2_MOTOR);
		}
		break;
		case MANUALRAW_CLAMP2CCW_BUTTON:
		{
			if(state)
				DCMotor_Run(CLAMP2_MOTOR, CCW, DCMOTORSPEED);//DCMOTORSPEED
			else
				DCMotor_Stop(CLAMP2_MOTOR);			
		}
		break;
		case MANUALRAW_CUTOFF1CW_BUTTON: //切断1正转
		{
			if(state)
				DCMotor_Run(CUTOFF1_MOTOR, CW, DCMOTORSPEED);
			else
				DCMotor_Stop(CUTOFF1_MOTOR);			
		}
		break;
		case MANUALRAW_CUTOFF1CCW_BUTTON:
		{
			if(state)
				DCMotor_Run(CUTOFF1_MOTOR, CCW, DCMOTORSPEED);
			else
				DCMotor_Stop(CUTOFF1_MOTOR);					
		}
		break;
		case MANUALRAW_CUTOFF2CW_BUTTON: //切断2正转
		{
			if(state)
				DCMotor_Run(CUTOFF2_MOTOR, CW, DCMOTORSPEED);
			else
				DCMotor_Stop(CUTOFF2_MOTOR);				
		}
		break;
		case MANUALRAW_CUTOFF2CCW_BUTTON:
		{
			if(state)
				DCMotor_Run(CUTOFF2_MOTOR, CCW, DCMOTORSPEED);
			else
				DCMotor_Stop(CUTOFF2_MOTOR);	
		}
		break;
		case MANUALRAW_SAPERATECW_BUTTON: //分离正转
		{
			if(state)
				DCMotor_Run(SAPERATE_MOTOR, CCW, DCMOTORSPEED);
			else
				DCMotor_Stop(SAPERATE_MOTOR);	
		}
		break;
		case MANUALRAW_SAPERATECCW_BUTTON:
		{
			if(state)
				DCMotor_Run(SAPERATE_MOTOR, CW, DCMOTORSPEED);
			else
				DCMotor_Stop(SAPERATE_MOTOR);				
		}
		break;
		case MANUALRAW_DISLOCATECW_BUTTON: //错位正转
		{
			if(state)
			{
				StepMotor_SetDir(DISPOS_MOTOR, CCW);
				StepMotor_SetSpeed(DISPOS_MOTOR, pProjectMan->dislocateSpeed);
				StepMotor_SetCMD(DISPOS_MOTOR, ENABLE);
			}
			else
			{
				StepMotor_Stop(DISPOS_MOTOR);
			}				
		}
		break;
		case MANUALRAW_DISLOCATECCW_BUTTON:
		{
			if(state)
			{
				StepMotor_SetDir(DISPOS_MOTOR, CW);
				StepMotor_SetSpeed(DISPOS_MOTOR, pProjectMan->dislocateSpeed);
				StepMotor_SetCMD(DISPOS_MOTOR, ENABLE);
			}
			else
			{
				StepMotor_Stop(DISPOS_MOTOR);
			}				
		}
		break;
		case MANUALRAW_HEATUP_BUTTON: //加热片抬起
		{
			if(state)
				DCMotor_Run(HEATING_MOTOR, CW, pProjectMan->heatingUpSpeed);
			else
				DCMotor_Stop(HEATING_MOTOR);				
		}			
		break;
		case MANUALRAW_HEATDOWN_BUTTON:
		{
			if(state)
				DCMotor_Run(HEATING_MOTOR, CCW, pProjectMan->heatingDownSpeed);
			else
				DCMotor_Stop(HEATING_MOTOR);				
		}
		break;	
		case MANUALRAW_HEATON_BUTTON: //熔接加热
		{
			RELAY = state;
		}
		break;
		case MANUALRAW_CUTOFF1HEATON_BUTTON: //切断1加热
		{
			if(state)
			{
				DCMotor_Run(CUTOFF1HEATDCMOTOR1, CW, pProjectMan->cutoff1HeatingVoltage*100/24);
				DCMotor_Run(CUTOFF1HEATDCMOTOR2, CW, pProjectMan->cutoff1HeatingVoltage*100/24);
			}
			else
			{
				DCMotor_Stop(CUTOFF1HEATDCMOTOR1);
				DCMotor_Stop(CUTOFF1HEATDCMOTOR2);
			}				
		}
		break;
		case MANUALRAW_CUTOFF2HEATON_BUTTON: //切断2加热
		{
			if(state)
			{
				DCMotor_Run(CUTOFF2HEATDCMOTOR1, CW, pProjectMan->cutoff2HeatingVoltage*100/24);
				DCMotor_Run(CUTOFF2HEATDCMOTOR2, CW, pProjectMan->cutoff2HeatingVoltage*100/24);
			}
			else
			{
				DCMotor_Stop(CUTOFF2HEATDCMOTOR1);
				DCMotor_Stop(CUTOFF2HEATDCMOTOR2);
			}
		}			
		break;
		
		case MANUALRAW_BACK_BUTTON:
		break;				
		
		default:
			cDebug("manualrawPage BUTTON error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
