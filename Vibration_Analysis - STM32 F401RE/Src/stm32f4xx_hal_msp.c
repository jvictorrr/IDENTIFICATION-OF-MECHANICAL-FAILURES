/**
  ******************************************************************************
  * @file    stm32f4xx_hal_msp.c
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   HAL MSP module.
  *         
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
    This file is generated automatically by MicroXplorer and eventually modified 
    by the user

  @endverbatim
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

/** @defgroup STM32F4XX_HAL_MSP STM32F4XX HAL MSP
  * @{
  */

/** @defgroup STM32F4XX_HAL_MSP_IMPORTED_VARIABLES STM32F4xx HAL MSP Imported Variables
  * @{
  */

extern UART_HandleTypeDef UartHandle;
extern DMA_HandleTypeDef hdma_SrvUart_rx;
extern DMA_HandleTypeDef hdma_SrvUart_tx;

/**
 * @}
 */

/** @defgroup STM32F4XX_HAL_MSP_IMPORTED_FUNCTIONS STM32F4xx HAL MSP Imported Functions
  * @{
  */
  
extern void _Error_Handler(char *, int);

/**
  * @}
  */


/**
  *  @brief UART MSP initialization.
  *  @param [in] huart UART peripheral handler
  *  @return None
  */
void HAL_UART_MspInit(UART_HandleTypeDef* UartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  
  SRV_UART_RX_GPIO_CLK_ENABLE();
  SRV_UART_TX_GPIO_CLK_ENABLE();
  /* Enable USARTx clock */
  SRV_UART_CLK_ENABLE();
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* UART TX GPIO pin configuration  */
  /* Service UART_TX Init */
  GPIO_InitStruct.Pin = SRV_UART_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = SRV_UART_TX_GPIO_AF;
  HAL_GPIO_Init(SRV_UART_TX_GPIO_Port, &GPIO_InitStruct);
  
  /* Service UART_RX Init */
  GPIO_InitStruct.Pin = SRV_UART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = SRV_UART_RX_GPIO_AF;
  HAL_GPIO_Init(SRV_UART_RX_GPIO_Port, &GPIO_InitStruct);
  
  /* Service UART DMA Init */
  
  /* Service UART_RX Init */
  hdma_SrvUart_rx.Instance = SRV_UART_RX_DMA;
  hdma_SrvUart_rx.Init.Channel = SRV_UART_RX_DMA_CH;
  hdma_SrvUart_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_SrvUart_rx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_SrvUart_rx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_SrvUart_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_SrvUart_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_SrvUart_rx.Init.Mode = DMA_CIRCULAR;
  hdma_SrvUart_rx.Init.Priority = DMA_PRIORITY_LOW;
  hdma_SrvUart_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  if (HAL_DMA_Init(&hdma_SrvUart_rx) != HAL_OK) {
    Error_Handler();
  }
  __HAL_LINKDMA(UartHandle, hdmarx, hdma_SrvUart_rx);
  
  /* Service UART_TX Init */
  hdma_SrvUart_tx.Instance = SRV_UART_TX_DMA;
  hdma_SrvUart_tx.Init.Channel = SRV_UART_TX_DMA_CH;
  hdma_SrvUart_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_SrvUart_tx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_SrvUart_tx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_SrvUart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_SrvUart_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_SrvUart_tx.Init.Mode = DMA_NORMAL;
  hdma_SrvUart_tx.Init.Priority = DMA_PRIORITY_LOW;
  hdma_SrvUart_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  if (HAL_DMA_Init(&hdma_SrvUart_tx) != HAL_OK) {
    Error_Handler();
  }
  __HAL_LINKDMA(UartHandle, hdmatx, hdma_SrvUart_tx);
  
  /* Service UART interrupt Init */
  HAL_NVIC_SetPriority(SRV_UART_IRQn, SRV_UART_IRQ_PP, SRV_UART_IRQ_SP);
  HAL_NVIC_EnableIRQ(SRV_UART_IRQn);
}

/**
*  @brief UART MSP de-initialization.
*  @param [in] huart UART peripheral handler
*  @return None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  /*##-1- Reset peripherals ##################################################*/
  SRV_UART_FORCE_RESET();
  SRV_UART_RELEASE_RESET();
  
  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Service UART_RX Init */
  HAL_GPIO_DeInit(SRV_UART_RX_GPIO_Port, SRV_UART_RX_Pin);
  /* Service UART_TX Init */
  HAL_GPIO_DeInit(SRV_UART_TX_GPIO_Port, SRV_UART_TX_Pin);
  
  /* Service UART DMA Deinit */
  /* Service UART_RX Deinit */
  HAL_DMA_DeInit(huart->hdmarx);
  /* Service UART_RX Deinit */
  HAL_DMA_DeInit(huart->hdmatx);
  
//  /* Service UART interrupt Deinit */
//  HAL_NVIC_DisableIRQ(SRV_UART_IRQn);
}

/**
  * @brief TIM MSP Initialization
  * This function configures the hardware resources used in this example:
  *  - Peripheral's clock enable
  *  - Peripheral's Interrupt Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM4) {
    /* TIMx Peripheral clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* Set Interrupt Group Priority */
    HAL_NVIC_SetPriority(TIM4_IRQn, 0x9, 0);

    /* Enable the TIMx global Interrupt */
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  } else if (htim->Instance == TIM5) {
     /* TIMx Peripheral clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();

    /* Set Interrupt Group Priority */
    HAL_NVIC_SetPriority(TIM5_IRQn, 0x9, 0);

    /* Enable the TIMx global Interrupt */
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
  }
}

/**
  * @brief TIM OC MSP Initialization
  * This function configures the hardware resources used in this example:
  *  - Peripheral's clock enable
  *  - Peripheral's Interrupt Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{ 
  /* TIM1 Peripheral clock enable */
  __HAL_RCC_TIM1_CLK_ENABLE();

  /*  Enable the TIM1 global Interrupt & set priority */
  HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0x9, 0);
  HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
}

/************************ (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
