#ifndef _PROJECT_H_
#define _PROJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "../UILogic/pageCommon.h"

////
//#define ACTION_SIZE		   sizeof(Action_TypeDef)
//#define PROJECT_SIZE       (ACTION_SIZE*ACTIONS_PER_PROJECT + NAME_SIZE + 1) 
//#define CALIBPARA_SIZE     (sizeof(float)*PUMP_COUNT)
//#define LANGUAGE_SIZE      (1)
//#define POSCALI_SIZE       (4)
////EEPROMµÿ÷∑∑÷≈‰
//#define RESET_DEFAULT	   6
//#define CALIBPARA_BASEADDR (RESET_DEFAULT+4)
//#define LANGUAGE_BASEADDR  (CALIBPARA_BASEADDR + CALIBPARA_SIZE)
//#define PROJECT_BASEADDR   (LANGUAGE_BASEADDR + LANGUAGE_SIZE)
//#define POSCALI_BASEADDR   (PROJECT_BASEADDR + PROJECT_SIZE*PROJECT_COUNT)


void Clamp(uint8_t action, uint8_t *pStopFlag);
void Clamp1(uint8_t action, uint8_t *pStopFlag);
void Clamp2(uint8_t action, uint8_t *pStopFlag);
void Cutoff(uint8_t action, uint8_t *pStopFlag);
void Cutoff1(uint8_t action, uint8_t *pStopFlag);
void Cutoff2(uint8_t action, uint8_t *pStopFlag);
void HeatingCutoff(uint8_t *pStopFlag);
void Seperation(uint8_t action, uint8_t *pStopFlag);
void Disposition(uint8_t action, uint8_t *pStopFlag);
void DispositionDistance(uint8_t action, uint32_t distance, uint8_t *pStopFlag);
void Heating(uint8_t *pStopFlag);
void HeatingUp(uint8_t action, uint8_t *pStopFlag);

void ResetOriginStatus(uint8_t *pStopFlag);
void AutoRun(uint8_t *pStopFlag);

#ifdef __cplusplus
}
#endif

#endif
