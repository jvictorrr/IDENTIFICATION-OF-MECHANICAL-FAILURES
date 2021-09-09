/**
  ******************************************************************************
  * @file    main.c
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

#include <limits.h>
#include "TargetFeatures.h"
#include "main.h"
#include "MotionSP_Manager.h"


/** @addtogroup Projects
  * @{
  */

/** @addtogroup APPLICATIONS Applications
  * @{
  */

/** @addtogroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @addtogroup MAIN Main
  * @{
  */

/** @defgroup MAIN_PRIVATE_VARIABLES Main Private Variables
  * @{
  */

volatile uint8_t AccIntReceived= 0;
volatile uint8_t FifoEnabled = 0;
float sensitivity;
uint8_t IsFirstTime = 1;

/**
  * @}
  */


/** @defgroup MAIN_IMPORTED_VARIABLES Main Imported Variables
  * @{
  */

extern uint32_t StartTick;
extern uint8_t TimeDomainHeaderIsSent;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void InitVibrationAnalysis(void);

/** @addtogroup MAIN_PRIVATE_FUNCTIONS Main Private Functions
  * @{
  */

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main(void)
{
  HAL_Init();
  
  /* Configure the System clock */
  SystemClock_Config();
  
  InitTargetPlatform(TARGET_IDP005);
  
  //PREDMNT1_PRINTF("\33[%dm", FG_GREEN);
	
	/* Output a message on Hyperterminal using printf function */
 // PREDMNT1_PRINTF("\r\nStarting project\r\n");
  
  /* Set the vibration parameters with default values */
  MotionSP_SetDefaultVibrationParam();
  
  /* Condition Monitoring Initialization */
  InitVibrationAnalysis();
  IsFirstTime = 1;

	/* Infinite loop */
  while (1)
  {
    if (IsFirstTime)
    {
    //  PREDMNT1_PRINTF("\33[%dm", FG_CYAN);
    //  PREDMNT1_PRINTF("\r\n");
      
      IsFirstTime = 0;
      enable_FIFO();
      
      TimeDomainHeaderIsSent = 0;
      /* SYSTICK SW interrupt init */
      HAL_NVIC_SetPriority(SYSTICK_SW_IRQn, SYSTICK_SW_IRQ_PP, SYSTICK_SW_IRQ_SP);
      HAL_NVIC_EnableIRQ(SYSTICK_SW_IRQn);
      /* Start of the Time Window */
      StartTick = HAL_GetTick();
    }  
    
    do
    {
     /* Frequency Domain Analysis */
     MotionSP_VibrationAnalysis();
    } while (FinishAvgFlag != 1); 
    

    
     /* Send data to UART */
    if (FinishAvgFlag == 1)
    { 
      HAL_NVIC_DisableIRQ(SYSTICK_SW_IRQn);
      FinishAvgFlag = 0;
      SendVibrationResult();
      
      /* Condition Monitoring Initialization */
      InitVibrationAnalysis();
      restart_FIFO();
      IsFirstTime = 1;
    }
  }
}

/** @brief Condition Monitoring Initialization
  * @param None
  * @retval None
  */
static void InitVibrationAnalysis(void)
{
  //PREDMNT1_PRINTF("\33[%dm", FG_WHITE);
//  PREDMNT1_PRINTF("\r\n");
  
  SetVibrationParam();
  
  /* Initializes the vibration parameters with default values */
  MotionSP_VibrationInit();

  /* Initializes accelerometer with vibration parameters values */
  if(SetAccelerometerParameters())
  {
 //   PREDMNT1_PRINTF("\tOK Set Accelerometer Parameters\r\n");
  }
  else
  {
 //   PREDMNT1_PRINTF("\tFailed Set Accelerometer Parameters\r\n");
  }

  /* Configure the FIFO settings in according with others parammeters changed*/
  MotionSP_ConfigFifo(); //Configure FIFO
}

/**
  *  @brief   Get MCU Identifiers
  *  @details See "MCU device ID code" paragraph into the MCU Reference Manual
  *  @param   pMcuId Pointer to the MCU ID structure to be filled
  *  @return  None
  */
void Get_McuId(sMcuId_t *pMcuId)
{
#define DEV_ID_MASK       (uint32_t)0x00000FFF
#define REV_ID_MASK       (uint32_t)0xFFFF0000
#define DEV_ID_BIT        0
#define REV_ID_BIT        16

#define UNQ_DEV_ID_BASE   0x1FFF7A10U //!< Unique device ID register (96 bits) base address
#define FLASH_SIZE_BASE   0x1FFF7A22U //!< Flash size register base address
#define PACKAGE_DATA_BASE 0x1FFF7BF0U //!< Package data register base address
  
  if (pMcuId != NULL)
  {
    /* Read the device Id code */
    pMcuId->McuDevId = (uint16_t)(((uint32_t)(DBGMCU->IDCODE) & DEV_ID_MASK) >> DEV_ID_BIT);
    pMcuId->McuRevId = (uint16_t)(((uint32_t)(DBGMCU->IDCODE) & REV_ID_MASK) >> REV_ID_BIT);
    
    /* Read the unique device ID registers (96 bits) */
    pMcuId->u_id_31_0 = *((uint32_t *)(UNQ_DEV_ID_BASE+0x00));
    pMcuId->u_id_63_32 = *((uint32_t *)(UNQ_DEV_ID_BASE+0x04));
    pMcuId->u_id_95_64 = *((uint32_t *)(UNQ_DEV_ID_BASE+0x08));
    
    /* Read the size of the device Flash memory expressed in Kbytes */
    pMcuId->FlashSize = *((uint16_t *)(FLASH_SIZE_BASE));

    /* Read the package data */
    pMcuId->Package = (uint8_t)(((*((uint16_t *)(PACKAGE_DATA_BASE)))>>8)&0x07);
  }
}


/**
  * @brief 	System Clock Configuration
  * @return None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief  SYSTICK callback.
  * @return None
  */
void HAL_SYSTICK_Callback(void)
{
  // Launch SW IRQ for SYSTICK
  HAL_NVIC_SetPendingIRQ(SYSTICK_SW_IRQn);
}


/**
 * @brief  EXTI line detection callback.
 * @param  uint16_t GPIO_Pin Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch(GPIO_Pin)
 {
   case ISM330DLC_INT1_GPIO_PIN:
     __NOP();
     break;
   case ISM330DLC_INT2_GPIO_PIN:

     AccIntReceived = 1;
     if (FifoEnabled)
       FuncOn_FifoFull();
     else 
       FuncOn_DRDY_XL();
     break;
   case SYSTICK_SW_PIN:
     /* Time Domain Analysis */
     TimeDomain_UartDataSend(&sTimeDomain);
     break;
 }
}

/**
  * @}
  */


/** @addtogroup MAIN_EXPORTED_FUNCTIONS Main Exported Functions
  * @{
  */

/**
  * @brief This function provides accurate delay (in milliseconds) based 
  *        on variable incremented.
  * @note This is a user implementation using WFI state
  * @param Delay: specifies the delay time length, in milliseconds.
  * @retval None
  */
void HAL_Delay(__IO uint32_t Delay)
{
  uint32_t tickstart = 0;
  tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < Delay){
    __WFI();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1){
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: PREDMNT1_PRINTF("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1){
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
