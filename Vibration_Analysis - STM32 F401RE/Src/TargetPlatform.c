/**
  ******************************************************************************
  * @file    TargetPlatform.c
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   Initialization of the Target Platform
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
#include <stdio.h>
#include "TargetFeatures.h"
#include "main.h"

/** @addtogroup Projects
  * @{
  */

/** @addtogroup APPLICATIONS Applications
  * @{
  */

/** @addtogroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @addtogroup TARGET_PLATFORM Target Platform
  * @{
  */

/** @defgroup TARGET_PLATFORM_PRIVATE_VARIABLES Target Platform Private Variables
  * @{
  */

TargetFeatures_t TargetBoardFeatures;

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
static void ISM330DLC_GPIO_Init(void);
static void Init_MEM1_Sensors(void);

/** @addtogroup TARGET_PLATFORM_PRIVATE_FUNCTIONS Target Platform Private Functions
  * @{
  */

/**
  * @brief  Initialize all the Target platform's Features
  * @param  TargetType_t BoardType
  * @retval None
  */
void InitTargetPlatform(TargetType_t BoardType)
{
  TargetBoardFeatures.BoardType = BoardType;
  
#ifdef PREDMNT1_ENABLE_PRINTF
  /* UART Initialization */
  if(UART_Global_Init()!=HAL_OK) {
    Error_Handler();
  } else {
   // PREDMNT1_PRINTF("\33[%dm", BG_BLACK);
  //  PREDMNT1_PRINTF("\33[%dm", FG_MAGENTA);
   // PREDMNT1_PRINTF("\33[2J\33[H");  //Erase Screen and Cursor Home
   // PREDMNT1_PRINTF("UART Initialized\r\n\r\n");
  }
#endif /* PREDMNT1_ENABLE_PRINTF */
  
	/* Send Application Info via service UART */
  TerminalScreenAppInfo();
    
  /* Initialize LED */
  BSP_LED_Init(USER_LED);
  
  //PREDMNT1_PRINTF("SPI ");
  /* Initialize the SPI driver for ISM330DLC */
  if(BSP_SPI1_Init()!=HAL_OK) 
  {
   // PREDMNT1_PRINTF("not initialized\r\n");
    Error_Handler();
  }
  else
  {
    //PREDMNT1_PRINTF("initialized\r\n");
  }    
  
  /* Reset all the Target's Features */
  memset(&TargetBoardFeatures, 0, sizeof(TargetFeatures_t));

  /* Discovery and Initialize all the MEMS Target's Features */
  Init_MEM1_Sensors();

  /* @brief  Enable the Debug Module during STOP mode */
//  HAL_DBGMCU_EnableDBGStopMode();  
}

/**
  * @brief	Initialize the Accelerometer Configuration Pin
  * @return	None
  */
static void ISM330DLC_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  MOTION_SPI_CS_CLK_ENABLE();
  
  /* Configure CS_PIN pin */
  GPIO_InitStruct.Pin = MOTION_SPI_CS_PIN;
  GPIO_InitStruct.Mode = MOTION_SPI_CS_MODE;
  GPIO_InitStruct.Pull = MOTION_SPI_CS_PULL;
  GPIO_InitStruct.Speed = MOTION_SPI_CS_SPEED;
  HAL_GPIO_Init(MOTION_SPI_CS_PORT, &GPIO_InitStruct);
  
  /* SD chip select high */
  MOTION_CS_HIGH();
 
  /* Configure ISM330DLC INT1 pin ************************************* */
 /* GPIO Ports Clock Enable */
  ISM330DLC_INT1_GPIO_CLK_ENABLE();

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = ISM330DLC_INT1_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ISM330DLC_INT1_GPIO_PORT, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  /* Enable and set EXTI Interrupt priority */
  HAL_NVIC_SetPriority(ISM330DLC_INT1_EXTI_IRQn, ISM330DLC_INT1_EXTI_IRQ_PP, ISM330DLC_INT1_EXTI_IRQ_SP);
  HAL_NVIC_EnableIRQ(ISM330DLC_INT1_EXTI_IRQn);

  /* Configure ISM330DLC INT1 pin ************************************* */
  /* GPIO Ports Clock Enable */
  ISM330DLC_INT2_GPIO_CLK_ENABLE();

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = ISM330DLC_INT2_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ISM330DLC_INT2_GPIO_PORT, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  /* Enable and set EXTI Interrupt priority */
  HAL_NVIC_SetPriority(ISM330DLC_INT2_EXTI_IRQn, ISM330DLC_INT2_EXTI_IRQ_PP, ISM330DLC_INT2_EXTI_IRQ_SP);
  HAL_NVIC_EnableIRQ(ISM330DLC_INT2_EXTI_IRQn);
  
 
}

/** @brief Initialize all the MEMS1 sensors
 * @param None
 * @retval None
 */
static void Init_MEM1_Sensors(void)
{
  //PREDMNT1_PRINTF("MEMS initializations\r\n");
  
  if(ACCELERO_INSTANCE == IDP005_ISM330DLC_0)
  {
    ISM330DLC_GPIO_Init();
    //PREDMNT1_PRINTF("\tISM330DLC used\r\n");
  }
  
  /* Accelero & Gyro */
  if(IDP005_MOTION_SENSOR_Init(ACCELERO_INSTANCE, MOTION_ACCELERO | MOTION_GYRO)==BSP_ERROR_NONE) {
   // PREDMNT1_PRINTF("\tOK Accelero Sensor\r\n");
    //PREDMNT1_PRINTF("\tOK Gyroscope Sensor\r\n");
  }  
  
  /*  Enable all the sensors */
  if(IDP005_MOTION_SENSOR_Enable(ACCELERO_INSTANCE, MOTION_ACCELERO)==BSP_ERROR_NONE);
    //PREDMNT1_PRINTF("\tEnabled Accelero Sensor\r\n");
  if(IDP005_MOTION_SENSOR_Enable(ACCELERO_INSTANCE, MOTION_GYRO)==BSP_ERROR_NONE);
    //PREDMNT1_PRINTF("\tEnabled Gyroscope Sensor\r\n");
}

/**
  * @brief  This function switches on the LED
  * @param  None
  * @retval None
  */
void LedOnTargetPlatform(void)
{
    BSP_LED_On(USER_LED);
    TargetBoardFeatures.LedStatus=1;
}

/**
  * @brief  This function switches off the LED
  * @param  None
  * @retval None
  */
void LedOffTargetPlatform(void)
{
  BSP_LED_Off(USER_LED);
  TargetBoardFeatures.LedStatus=0;
}

/** @brief  This function toggles the LED
  * @param  None
  * @retval None
  */
void LedToggleTargetPlatform(void)
{
  BSP_LED_Toggle(USER_LED);
}

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
