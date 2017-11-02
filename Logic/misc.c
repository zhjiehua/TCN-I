#include "misc.h"
#include "stm32f10x.h"

void GetChipID(uint32_t *chipID)
{
#ifdef STM32SIM
	chipID[0] = *(__IO uint32_t*)(0X1FFFF7F0); //¸ß×Ö½Ú
	chipID[1] = *(__IO uint32_t*)(0X1FFFF7EC);
	chipID[2] = *(__IO uint32_t*)(0X1FFFF7E8); //µÍ×Ö½Ú
#else
	chipID[0] = 0X0FFFF7F0;
	chipID[1] = 0X0FFFF7EC;
	chipID[2] = 0X1FFFF7E8;
#endif
	//STM32_FLASH_SIZE = *(__IO uint32_t*)(0X1FFFF7E0);
}
