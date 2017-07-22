#ifndef _PROJECT_H_
#define _PROJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "../UILogic/pageCommon.h"

void Clamp(uint8_t action, uint8_t *pStopFlag);
void Clamp1(uint8_t action, uint8_t *pStopFlag);
void Clamp2(uint8_t action, uint8_t *pStopFlag);
void Cutoff(uint8_t action, uint8_t *pStopFlag);
void Cutoff1(uint8_t action, uint8_t *pStopFlag);
void Cutoff2(uint8_t action, uint8_t *pStopFlag);
void HeatingCutoff(uint8_t *pStopFlag);
void Separation(uint8_t action, uint8_t *pStopFlag);
void Dislocation(uint8_t action, uint8_t *pStopFlag);
void DislocationDistance(uint8_t action, uint32_t distance, uint8_t *pStopFlag);
void Heating(uint8_t *pStopFlag);
void HeatingUp(uint8_t action, uint8_t *pStopFlag);

void HalfResetOriginStatus(void);
void ResetOriginStatus(uint8_t *pStopFlag);
void AutoRun(uint8_t *pStopFlag);

#ifdef __cplusplus
}
#endif

#endif
