
#ifndef ENCODER_H
#define ENCODER_H

#include "stm32g4xx_hal.h"

// radius 25.5mm
// gear ratio 3.9473684211
// 1rev = 2048pulse

typedef volatile struct EncoderVariable
{
    int         pulse_num;

    double      vel_analyzed,
                dis_analyzed,
                dis_sum;

    
} EncoderVar;

extern EncoderVar L_encoder;
extern EncoderVar R_encoder;

extern void Encoder_Init(void);
extern void Encoder_calc(void);



/*
class Encoder{
    private:
        TIM_TypeDef*    m_tim;
        const double    dis_per_tick = 0.009909515890,
                        vel_per_tick = 39.63806356;

    public:
        int             pulse_num;

        double          vel_analyzed,
                        dis_analyzed,
                        dis_sum;

        Encoder(TIM_TypeDef* tim) : m_tim(tim){};
        ~Encoder();

        void Encoder_calc();
};
*/

#endif