#include "main.h"
#include "Core/Variable.h"
#include "Sensor/IR.h"
#include "Sensor/Encoder.h"
#include "Moving/Motor.h"
#include "Interface/fonts.h"
#include "Interface/ssd1306.h"
#include <iomanip>

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  Peripheral_Init();
  SSD1306_Init();

  char variable[9];
  unsigned char variable2[9];
  uint8_t* SSD1306_Buffer = GetBufferPointer();
  int16_t Left_qep_count;
  int16_t Right_qep_count;
  uint16_t length;

  volatile int i = 0;
  volatile int j = 0;

  IR_Init(&LF_SEN);
  IR_Init(&LS_SEN);
  IR_Init(&LD_SEN);
  IR_Init(&RD_SEN);
  IR_Init(&RS_SEN);
  IR_Init(&RF_SEN);

  Motor_Init(&L_motor);
  Motor_Init(&R_motor);

//  HAL_HRTIM_
  /* Start HRTIM's TIMER A, B, C, D */
//  HAL_HRTIM_WaveformCountStart_IT(&hhrtim1, HRTIM_TIMERID_MASTER | HRTIM_TIMERID_TIMER_B | HRTIM_TIMERID_TIMER_E | HRTIM_TIMERID_TIMER_F);
  /* Enable HRTIM's outputs TA2, TB1, TC2, TD1, TD2 */
//  HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TB2 | HRTIM_OUTPUT_TB1 | HRTIM_OUTPUT_TE1 | HRTIM_OUTPUT_TE2 | HRTIM_OUTPUT_TF1 | HRTIM_OUTPUT_TF2);

  HAL_HRTIM_WaveformCountStart_IT(&hhrtim1, HRTIM_TIMERID_MASTER);

  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1 | TIM_CHANNEL_2);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1 | TIM_CHANNEL_2);

  HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB1);
  HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB2);
  HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE1);
  HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE2);
  HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_F, HRTIM_OUTPUT_TF1);
  HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_F, HRTIM_OUTPUT_TF2);

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);  //오른 모터 / 앞
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);  //왼 모터 / 뒤
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);  //왼 모터 / 앞
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);  //오른 모터 / 뒤

  HAL_OPAMP_Start(&hopamp1);
  HAL_OPAMP_Start(&hopamp2);
  HAL_OPAMP_Start(&hopamp3);
  HAL_OPAMP_Start(&hopamp4);
  HAL_OPAMP_Start(&hopamp5);
  HAL_OPAMP_Start(&hopamp6);

  HAL_ADC_Start_IT(&hadc1);
  HAL_ADC_Start_IT(&hadc2);
  HAL_ADC_Start_IT(&hadc3);
  HAL_ADC_Start_IT(&hadc4);
  HAL_ADC_Start_IT(&hadc5);

  HAL_GPIO_WritePin(GPIOB, LLED1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, M_stby_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(GPIOA, RLED1_Pin, GPIO_PIN_SET);
  
  while (1)
  {
    sprintf(variable, "%4d %4d", LD_SEN.ADC_converted[0], RD_SEN.ADC_converted[0]);
    SSD1306_GotoXY(0, 0);
    SSD1306_Puts(variable, &Font_5x7, SSD1306_COLOR_BLACK);
    sprintf(variable, "%4d %4d", LS_SEN.ADC_converted[0], RS_SEN.ADC_converted[0]);
    SSD1306_GotoXY(0, 1);
    SSD1306_Puts(variable, &Font_5x7, SSD1306_COLOR_BLACK);
    sprintf(variable, "%4d %4d", LF_SEN.ADC_converted[0], RF_SEN.ADC_converted[0]);
    SSD1306_GotoXY(0, 2);
    SSD1306_Puts(variable, &Font_5x7, SSD1306_COLOR_BLACK);
    SSD1306_UpdateScreen();

//    L_motor.user_vel = 200;
//    R_motor.user_vel = 200;
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

void Peripheral_Init(void)
{
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_ADC4_Init();
  MX_ADC5_Init();
  MX_HRTIM1_Init();
  MX_OPAMP1_Init();
  MX_OPAMP2_Init();
  MX_OPAMP3_Init();
  MX_OPAMP4_Init();
  MX_OPAMP5_Init();
  MX_OPAMP6_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_TIM20_Init();
}
