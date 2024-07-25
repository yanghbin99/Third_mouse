
#include "main.h"
#include "gpio.h"
#include "Sensor/IR.h"
#include "stm32g4xx_hal.h"

IRVar LF_SEN;
IRVar LS_SEN;
IRVar LD_SEN;
IRVar RF_SEN;
IRVar RS_SEN;
IRVar RD_SEN;

void IR_Init(IRVar *pIR)
{
    memset((void *)pIR, 0x00, sizeof(IRVar));
}

/*
void HAL_HRTIM_Compare2EventCallback(HRTIM_HandleTypeDef * hhrtim, uint32_t TimerIndex)
{
    if (TimerIndex == HRTIM_TIMERINDEX_MASTER)
    {

//        HAL_ADC_Start_IT(&hadc2);   //RS
//        HAL_ADC_Start_IT(&hadc5);   //LF
    }
}

void HAL_HRTIM_Compare3EventCallback(HRTIM_HandleTypeDef * hhrtim, uint32_t TimerIndex)
{
    if (TimerIndex == HRTIM_TIMERINDEX_MASTER)
    {
//        HAL_ADC_Start_IT(&hadc4);   //LD
//        HAL_ADC_Start_IT(&hadc5);   //RD
    }
}

void HAL_HRTIM_Compare4EventCallback(HRTIM_HandleTypeDef * hhrtim, uint32_t TimerIdx)
{
    if (TimerIdx == HRTIM_TIMERINDEX_MASTER)
    {
//        HAL_ADC_Start_IT(&hadc1);   //RF
//        HAL_ADC_Start_IT(&hadc3);   //LS        
    }
}
*/
/*
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1) //RF
    {
        if(RF_SEN.Cnt_conversion < 2)
        {
            RF_SEN.ADC_converted[RF_SEN.Cnt_conversion] = HAL_ADC_GetValue(&hadc1);
            RF_SEN.Cnt_conversion++;
            HAL_ADC_StartSampling(&hadc1);
        }
        else
        {
            for(int i = 0; i < RF_SEN.Cnt_conversion; i++)
                RF_SEN.ADC_sum += RF_SEN.ADC_converted[i];
            RF_SEN.ADC_average = RF_SEN.ADC_sum / 3;
            RF_SEN.Cnt_conversion = 0;
        }
    }
    if (hadc->Instance == ADC2) //RS
    {
        if(RS_SEN.Cnt_conversion < 2)
        {
//            HAL_GPIO_WritePin(GPIOA, RLED2_Pin, GPIO_PIN_SET);            
            RS_SEN.ADC_converted[RS_SEN.Cnt_conversion] = HAL_ADC_GetValue(&hadc2);
            RS_SEN.Cnt_conversion++;
            HAL_ADC_StartSampling(&hadc2);
        }
        else
        {
            for(int i = 0; i < RS_SEN.Cnt_conversion; i++)
                RS_SEN.ADC_sum += RS_SEN.ADC_converted[i];
            RS_SEN.ADC_average = RS_SEN.ADC_sum / 3;
            RS_SEN.Cnt_conversion = 0;
        }
    }
    if (hadc->Instance == ADC3) //LS
    {
        if(LS_SEN.Cnt_conversion < 2)
        {
            HAL_GPIO_WritePin(GPIOA, RLED2_Pin, GPIO_PIN_RESET);
            LS_SEN.ADC_converted[LS_SEN.Cnt_conversion] = HAL_ADC_GetValue(&hadc3);
            LS_SEN.Cnt_conversion++;
            HAL_ADC_StartSampling(&hadc3);
        }
        else
        {
            for(int i = 0; i < LS_SEN.Cnt_conversion; i++)
                LS_SEN.ADC_sum += LS_SEN.ADC_converted[i];
            LS_SEN.ADC_average = LS_SEN.ADC_sum / 3;
            LS_SEN.Cnt_conversion = 0;
            HAL_GPIO_WritePin(GPIOA, RLED2_Pin, GPIO_PIN_SET); 
        }
    }
    if (hadc->Instance == ADC4) //LD
    {
        if(LD_SEN.Cnt_conversion < 2)
        {
            LD_SEN.ADC_converted[LD_SEN.Cnt_conversion] = HAL_ADC_GetValue(&hadc4);
            LD_SEN.Cnt_conversion++;
            HAL_ADC_StartSampling(&hadc4);
        }
        else
        {
             
            for(int i = 0; i < LD_SEN.Cnt_conversion; i++)
                LD_SEN.ADC_sum += LD_SEN.ADC_converted[i];
            LD_SEN.ADC_average = LD_SEN.ADC_sum / 3;
            LD_SEN.Cnt_conversion = 0;
        }
    }
    if (hadc->Instance == ADC5) //RD
    {
        if(RD_SEN.Cnt_conversion < 2)
        {
            RD_SEN.ADC_converted[RD_SEN.Cnt_conversion] = HAL_ADC_GetValue(&hadc5);
            RD_SEN.Cnt_conversion++;
            HAL_ADC_StartSampling(&hadc5);
        }
        else
        {
            for(int i = 0; i < RD_SEN.Cnt_conversion; i++)
                RD_SEN.ADC_sum += RD_SEN.ADC_converted[i];
            RD_SEN.ADC_average = RD_SEN.ADC_sum / 3;
            RD_SEN.Cnt_conversion = 0;
        }
            
    }
}
*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1) //RF
    {
        RF_SEN.ADC_converted[0] = HAL_ADC_GetValue(&hadc1);
    }
    if (hadc->Instance == ADC2) //RS
    {
        RS_SEN.ADC_converted[0] = HAL_ADC_GetValue(&hadc2);
    }
    if (hadc->Instance == ADC3) //LS
    {
        LS_SEN.ADC_converted[0] = HAL_ADC_GetValue(&hadc3);
    }
    if (hadc->Instance == ADC4) //LD
    {
        LD_SEN.ADC_converted[0] = HAL_ADC_GetValue(&hadc4);
    }
    if (hadc->Instance == ADC5) //RD
    {
        RD_SEN.ADC_converted[0] = HAL_ADC_GetValue(&hadc5);
    }
}