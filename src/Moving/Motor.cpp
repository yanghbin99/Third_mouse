
#include "main.h"
#include "hrtim.h"
#include "Motor.h"
#include "Sensor/Encoder.h"
#include "stm32g4xx_hal.h"

#define MAX_I_term 5
#define MIN_I_term -5

#define MAX_PID_OUT 4000
#define MIN_PID_OUT -4000

MotorVar L_motor;
MotorVar R_motor;

void Motor_Init(MotorVar *pmotor)
{
    memset((void *)pmotor, 0x00, sizeof(MotorVar));

    pmotor -> P_gain = 25;
    pmotor -> I_gain = 0;
    pmotor -> D_gain = 1;
    
    pmotor -> accel = 6600;
    pmotor -> user_vel = 0;
}


void HAL_HRTIM_Compare1EventCallback(HRTIM_HandleTypeDef * hhrtim, uint32_t TimerIndex)
{
    if (TimerIndex == HRTIM_TIMERINDEX_MASTER)
    {
//        HAL_GPIO_WritePin(GPIOA, RLED1_Pin, GPIO_PIN_RESET);
        Encoder_calc();
        Motor_PID();
    }

}


void Motor_PID(void)
{    
    L_motor.vel_err = L_motor.user_vel - L_encoder.vel_analyzed;
    L_motor.vel_err_sum += L_motor.vel_err * 0.00025;
    
    L_motor.vel_Pterm = L_motor.P_gain * L_motor.vel_err;
    L_motor.vel_Iterm = L_motor.I_gain * L_motor.vel_err_sum;
    if(L_motor.vel_Iterm > 5)
        L_motor.vel_Iterm = 5;
    else if(L_motor.vel_Iterm < -5)
        L_motor.vel_Iterm = -5;
    L_motor.vel_Dterm = L_motor.D_gain * ((L_motor.vel_err - L_motor.vel_pre_err) / 0.25);
    L_motor.vel_pre_err = L_motor.vel_err;

    L_motor.PID_output = L_motor.vel_Pterm + L_motor.vel_Iterm + L_motor.vel_Dterm;
    

    R_motor.vel_err = R_motor.user_vel - R_encoder.vel_analyzed;
    R_motor.vel_err_sum += R_motor.vel_err * 0.00025;
    
    R_motor.vel_Pterm = R_motor.P_gain * R_motor.vel_err;
    R_motor.vel_Iterm = R_motor.I_gain * R_motor.vel_err_sum;
    if(R_motor.vel_Iterm > 5)
        R_motor.vel_Iterm = 5;
    else if(R_motor.vel_Iterm < -5)
        R_motor.vel_Iterm = -5;
    R_motor.vel_Dterm = R_motor.D_gain * ((R_motor.vel_err - R_motor.vel_pre_err) / 0.25);
    R_motor.vel_pre_err = R_motor.vel_err;

    R_motor.PID_output = R_motor.vel_Pterm + R_motor.vel_Iterm + R_motor.vel_Dterm;

    if(L_motor.PID_output >= 0)
    {
        if(L_motor.PID_output > MAX_PID_OUT)
            L_motor.PID_output = MAX_PID_OUT;
        
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, (int) L_motor.PID_output);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
    }
    else
    {
        if(L_motor.PID_output < MIN_PID_OUT)
            L_motor.PID_output = MIN_PID_OUT;

        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, (int) (L_motor.PID_output * (-1)));
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);
    }

    if(R_motor.PID_output >= 0)
    {
        if(R_motor.PID_output > MAX_PID_OUT)
            R_motor.PID_output = MAX_PID_OUT;
        
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, (int) R_motor.PID_output);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);
    }
    else
    {
        if(R_motor.PID_output < MIN_PID_OUT)
            R_motor.PID_output = MIN_PID_OUT;
        
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, (int) (R_motor.PID_output * (-1)));
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
    }
}
