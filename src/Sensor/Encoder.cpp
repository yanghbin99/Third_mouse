
#include "Encoder.h"
#include "stm32g4xx_hal.h"
#include "tim.h"

#define dis_per_tick 0.009909515890 // 0.0255 * pi / 2048
#define vel_per_tick 39.63806356

EncoderVar L_encoder = {
    .pulse_num = 0,
    .vel_analyzed = 0.0,
    .dis_analyzed = 0.0,
    .dis_sum = 0.0
};

EncoderVar R_encoder = {
    .pulse_num = 0,
    .vel_analyzed = 0.0,
    .dis_analyzed = 0.0,
    .dis_sum = 0.0
};

void Encoder_calc()
{
    L_encoder.pulse_num = __HAL_TIM_GET_COUNTER(&htim1);
    R_encoder.pulse_num = __HAL_TIM_GET_COUNTER(&htim3);

    if(L_encoder.pulse_num > 30000)
        L_encoder.pulse_num -= 65537;
    if(R_encoder.pulse_num > 30000)
        R_encoder.pulse_num -= 65537;    

    TIM1 -> CNT = 0;
    TIM3 -> CNT = 0;

    L_encoder.dis_analyzed = L_encoder.pulse_num * dis_per_tick;
    R_encoder.dis_analyzed = R_encoder.pulse_num * dis_per_tick;
    
    L_encoder.vel_analyzed = L_encoder.pulse_num * vel_per_tick;
    R_encoder.vel_analyzed = R_encoder.pulse_num * vel_per_tick;
    
    L_encoder.dis_sum += L_encoder.dis_analyzed;
    R_encoder.dis_sum += R_encoder.dis_analyzed;

    L_encoder.pulse_num = 0;
    L_encoder.dis_analyzed = 0;

    R_encoder.pulse_num = 0;
    R_encoder.dis_analyzed = 0;
};
