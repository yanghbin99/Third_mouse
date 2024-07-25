
#ifndef MOTOR_H
#define MOTOR_H

#include "string.h"
#include "tim.h"
#include "gpio.h"
#include <math.h>

typedef volatile struct MotorVariable
{
    double  vel_Pterm,
            vel_Iterm,
            vel_Dterm,
            PID_output,
            vel_err,
            vel_pre_err,
            vel_err_sum;

    double  user_vel,
            accel;

    int     P_gain,
            I_gain,
            D_gain;

} MotorVar;

extern MotorVar L_motor;
extern MotorVar R_motor;

extern void Motor_Init(MotorVar *pmotor);
extern void Motor_PID(void);

#endif