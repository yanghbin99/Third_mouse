#ifndef IR_H
#define IR_H

#include "stm32g4xx_hal.h"
#include "string.h"


typedef volatile struct IRVariable
{
    int         ADC_converted[3],
                ADC_sum,
                Min_val,
                Max_val,
                Cnt_conversion;
    
    float       ADC_average;

} IRVar;

extern IRVar LF_SEN;
extern IRVar LS_SEN;
extern IRVar LD_SEN;
extern IRVar RF_SEN;
extern IRVar RS_SEN;
extern IRVar RD_SEN;

void IR_Init(IRVar *pIR);

#endif