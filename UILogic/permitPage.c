#include "pageCommon.h"
#include "../Logic/managerment.h"
#include "CPrintf.h"
#include "../HARDWARE/24CXX/24cxx.h"
#include "../HARDWARE/DCMotor/DCMotor.h"
#include "../HardwareCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ACTIVEMASK 0x0502
	
void permitPageButtonProcess(uint16 control_id, uint8 state)
{
	uint16_t usableTimes;
	uint16_t validateCode;
	uint16_t temp;
	
	switch(control_id)
	{
		case PERMIT_RANDOMCODE_BUTTON:
			//生产随机码
			srand(SysTick->VAL);
			pProjectMan->randomCode = rand();
			SetTextInt32(PERMITPAGE_INDEX, PERMIT_RANDOMCODE_EDIT, pProjectMan->randomCode, 0, 0);
		break;
		case PERMIT_ACTIVE_BUTTON:
			//激活
			validateCode = pProjectMan->serial&0x0000FFFF;
			temp = pProjectMan->randomCode&0x0000FFFF;
			validateCode ^= ACTIVEMASK;
			temp ^= ACTIVEMASK;
			validateCode += temp;
			
			if(validateCode == (pProjectMan->activeCode&0xFFFF0000)>>16)//有效码正确
			{
				usableTimes = (pProjectMan->serial&0xFFFF0000)>>16;
				temp = (pProjectMan->randomCode&0xFFFF0000)>>16;
				usableTimes ^= ACTIVEMASK;
				temp ^= ACTIVEMASK;
				usableTimes += temp;
				temp = pProjectMan->activeCode&0x0000FFFF;
				usableTimes = abs(temp - usableTimes);
				
				pProjectMan->usableTimes += usableTimes;
				SetTextInt32(PERMITPAGE_INDEX, PERMIT_USABLETIMES_EDIT, pProjectMan->usableTimes, 0, 0);
				AT24CXX_Write(USABLETIMES_BASEADDR, (uint8_t*)&pProjectMan->usableTimes, 2);
				
				//生产新的随机码
				srand(SysTick->VAL);
				pProjectMan->randomCode = rand();
				SetTextInt32(PERMITPAGE_INDEX, PERMIT_RANDOMCODE_EDIT, pProjectMan->randomCode, 0, 0);
			}
		break;
		case PERMIT_BACK_BUTTON:
		break;
		default:
			cDebug("permitPage BUTTON error!\n");
		break;
	}
}

void permitPageEditProcess(uint16 control_id, uint8 *str)
{
	switch(control_id)
	{	 
		case PERMIT_ACTIVECODE_EDIT:
			pProjectMan->activeCode = StringToInt32(str);
		break;
		default:
			cDebug("permitPage EDIT error!\n");
		break;
	}
}

#ifdef __cplusplus
}
#endif
