/**
  ******************************************************************************
  * @file    steval_idp005_periph_conf.h
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   peripherals configuration file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STEVAL_IDP005_PERIPH_CONF_H
#define __STEVAL_IDP005_PERIPH_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"


/** @addtogroup Projects
  * @{
  */

/** @addtogroup APPLICATIONS Applications
  * @{
  */

/** @addtogroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @defgroup IDP005_PERIPH_CONF
  * @{
  */

/** @defgroup IDP005_PERIPH_CONF_EXPORTED_DEFINES IDP005_PERIPH_CONF Exported Defines
  * @{
  */

#define IOLINK_UART                             USART2
#define IOLINK_UART_CLK_ENABLE()                __HAL_RCC_USART2_CLK_ENABLE()
#define IOLINK_UART_CLK_DISABLE()               __HAL_RCC_USART2_CLK_DISABLE()
#define IOLINK_UART_RX_Pin                      GPIO_PIN_3
#define IOLINK_UART_RX_GPIO_Port                GPIOA
#define IOLINK_UART_RX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define IOLINK_UART_RX_GPIO_AF                  GPIO_AF7_USART2
#define IOLINK_UART_TX_Pin                      GPIO_PIN_2
#define IOLINK_UART_TX_GPIO_Port                GPIOA
#define IOLINK_UART_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define IOLINK_UART_TX_GPIO_AF                  GPIO_AF7_USART2
#define IOLINK_UART_IRQn                        USART2_IRQn
#define IOLINK_UART_IRQ_PP                      2
#define IOLINK_UART_IRQ_SP                      0
#define IOLINK_UART_IRQHandler                  USART2_IRQHandler

#define IOLINK_UART_RX_DMA                      DMA1_Stream5
#define IOLINK_UART_RX_DMA_CH                   DMA_CHANNEL_4
#define IOLINK_UART_DMA_CLK_ENABLE()            __HAL_RCC_DMA1_CLK_ENABLE();
#define IOLINK_UART_DMA_CLK_DISABLE()            __HAL_RCC_DMA1_CLK_DISABLE();
#define IOLINK_UART_RX_DMA_Stream_IRQn          DMA1_Stream5_IRQn
#define IOLINK_UART_RX_DMA_Stream_IRQ_PP        2
#define IOLINK_UART_RX_DMA_Stream_IRQ_SP        0
#define IOLINK_UART_RX_DMA_Stream_IRQHandler    DMA1_Stream5_IRQHandler
#define IOLINK_UART_TX_DMA                      DMA1_Stream6
#define IOLINK_UART_TX_DMA_CH                   DMA_CHANNEL_4
#define IOLINK_UART_TX_DMA_Stream_IRQn          DMA1_Stream6_IRQn
#define IOLINK_UART_TX_DMA_Stream_IRQ_PP        2
#define IOLINK_UART_TX_DMA_Stream_IRQ_SP        0
#define IOLINK_UART_TX_DMA_Stream_IRQHandler    DMA1_Stream6_IRQHandler
    
#define SRV_UART                                UART5
#define SRV_UART_CLK_ENABLE()                   __HAL_RCC_UART5_CLK_ENABLE()
#define SRV_UART_CLK_DISABLE()                  __HAL_RCC_UART5_CLK_DISABLE()
#define SRV_UART_FORCE_RESET()                  __USART5_FORCE_RESET()
#define SRV_UART_RELEASE_RESET()                __USART5_RELEASE_RESET()
#define SRV_UART_RX_Pin                         GPIO_PIN_2
#define SRV_UART_RX_GPIO_Port                   GPIOD
#define SRV_UART_RX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOD_CLK_ENABLE()
#define SRV_UART_RX_GPIO_AF                     GPIO_AF8_UART5
#define SRV_UART_TX_Pin                         GPIO_PIN_12
#define SRV_UART_TX_GPIO_Port                   GPIOC
#define SRV_UART_TX_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define SRV_UART_TX_GPIO_AF                     GPIO_AF8_UART5
#define SRV_UART_IRQn                           UART5_IRQn
#define SRV_UART_IRQ_PP                         2
#define SRV_UART_IRQ_SP                         0
#define SRV_UART_IRQHandler                     UART5_IRQHandler

#define SRV_UART_BAUDRATE                       230400
#define SRV_UART_BUFFER_SIZE                    200     
#define SRV_UART_TIMEOUT_MAX                    1000    
   
#define SRV_UART_RX_DMA                         DMA1_Stream0
#define SRV_UART_RX_DMA_CH                      DMA_CHANNEL_4
#define SRV_UART_DMA_CLK_ENABLE()               __HAL_RCC_DMA1_CLK_ENABLE();
#define SRV_UART_RX_DMA_Stream_IRQn             DMA1_Stream0_IRQn
#define SRV_UART_RX_DMA_Stream_IRQ_PP           2
#define SRV_UART_RX_DMA_Stream_IRQ_SP           0
#define SRV_UART_RX_DMA_Stream_IRQHandler       DMA1_Stream0_IRQHandler
#define SRV_UART_TX_DMA                         DMA1_Stream7
#define SRV_UART_TX_DMA_CH                      DMA_CHANNEL_4
#define SRV_UART_TX_DMA_Stream_IRQn             DMA1_Stream7_IRQn
#define SRV_UART_TX_DMA_Stream_IRQ_PP           2
#define SRV_UART_TX_DMA_Stream_IRQ_SP           0
#define SRV_UART_TX_DMA_Stream_IRQHandler       DMA1_Stream7_IRQHandler

/**
  * @}
  */   

 
/** @addtogroup STEVAL-IDP005V1_IO_I2C_BUS STEVAL-IDP005V1 IO I2C BUS
  * @{
  */

#define ENV_I2C                         I2C1
#define ENV_I2C_CLK_ENABLE()            __I2C1_CLK_ENABLE()
#define ENV_I2C_CLK_DISABLE()           __I2C1_CLK_DISABLE()
#define ENV_I2C_SDA_GPIO_CLK_ENABLE()   __GPIOB_CLK_ENABLE()
#define ENV_I2C_SCL_GPIO_CLK_ENABLE()   __GPIOB_CLK_DISABLE()
#define ENV_I2C_SDA_GPIO_PORT           GPIOB
#define ENV_I2C_SCL_GPIO_PORT           GPIOB
#define ENV_I2C_SDA_PIN                 GPIO_PIN_7
#define ENV_I2C_SCL_PIN                 GPIO_PIN_8
#define ENV_I2C_SDA_AF                  GPIO_AF4_I2C1
#define ENV_I2C_SCL_AF                  GPIO_AF4_I2C1
#define ENV_I2C_FORCE_RESET()           __I2C1_FORCE_RESET()
#define ENV_I2C_RELEASE_RESET()         __I2C1_RELEASE_RESET()
#define ENV_I2C_IRQn                    I2C1_IRQn
#define ENV_I2C_IRQ_PP                  4
#define ENV_I2C_IRQ_SP                  0
#define ENV_I2C_IRQHandler              I2C1_IRQHandler
#define ENV_I2C_EV_IRQn                 I2C1_EV_IRQn
#define ENV_I2C_ER_IRQn                 I2C1_ER_IRQn

/**
  * @}
  */   
   
/* SPI1 */
#define MOTION_SPI                      SPI1
#define MOTION_SPI_MODE                 SPI_MODE_MASTER
#define MOTION_SPI_DIRECTON             SPI_DIRECTION_2LINES
#define MOTION_SPI_DATASIZE             SPI_DATASIZE_8BIT
#define MOTION_SPI_CLKPOLARITY          SPI_POLARITY_LOW
#define MOTION_SPI_CLKPHASE             SPI_PHASE_1EDGE
#define MOTION_SPI_NSS                  SPI_NSS_SOFT
#define MOTION_SPI_FIRSTBIT             SPI_FIRSTBIT_MSB
#define MOTION_SPI_TIMODE               SPI_TIMODE_DISABLED
#define MOTION_SPI_CRCPOLYNOMIAL        7
#define MOTION_SPI_BAUNDRATEPRESCALER   SPI_BAUDRATEPRESCALER_16
#define MOTION_SPI_CRCCALCULATION       SPI_CRCCALCULATION_DISABLED
#define MOTION_SPI_MAX_CLOCK            10000000 /* in MHz */
#define MOTION_SPI_BUS_CLOCK            HAL_RCC_GetPCLK2Freq()
#define SPIx_TIMEOUT_MAX                1000 /*<! Maximum timeout value for BUS waiting loops */
#define SPIx_BUFFERSIZE                 264
   
#define MOTION_SPI_CLK_ENABLE()         __HAL_RCC_SPI1_CLK_ENABLE()
#define MOTION_SPI_CLK_DISABLE()        __HAL_RCC_SPI1_CLK_DISABLE()
#define MOTION_SPI_FORCE_RESET()        __HAL_RCC_SPI1_FORCE_RESET()
#define MOTION_SPI_RELEASE_RESET()      __HAL_RCC_SPI1_RELEASE_RESET()   

   
// SPI Reset Pin: PA.8
#define MOTION_SPI_RESET_PIN          GPIO_PIN_8
#define MOTION_SPI_RESET_MODE         GPIO_MODE_OUTPUT_PP
#define MOTION_SPI_RESET_PULL         GPIO_PULLUP
#define MOTION_SPI_RESET_SPEED        GPIO_SPEED_LOW
#define MOTION_SPI_RESET_ALTERNATE    0
#define MOTION_SPI_RESET_PORT         GPIOA
#define MOTION_SPI_RESET_CLK_ENABLE() __GPIOA_CLK_ENABLE()

// SCLK: PB.3
#define MOTION_SPI_SCLK_PIN             GPIO_PIN_3
#define MOTION_SPI_SCLK_MODE            GPIO_MODE_AF_PP
#define MOTION_SPI_SCLK_PULL            GPIO_PULLUP
#define MOTION_SPI_SCLK_SPEED           GPIO_SPEED_HIGH
#define MOTION_SPI_SCLK_ALTERNATE       GPIO_AF5_SPI1
#define MOTION_SPI_SCLK_PORT            GPIOB
#define MOTION_SPI_SCLK_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTION_SPI_SCLK_CLK_DISABLE()   __HAL_RCC_GPIOB_CLK_DISABLE()

// MISO (Master Input Slave Output): PB.4
#define MOTION_SPI_MISO_PIN             GPIO_PIN_4
#define MOTION_SPI_MISO_MODE            GPIO_MODE_AF_PP
#define MOTION_SPI_MISO_PULL            GPIO_NOPULL
#define MOTION_SPI_MISO_SPEED           GPIO_SPEED_HIGH
#define MOTION_SPI_MISO_ALTERNATE       GPIO_AF5_SPI1
#define MOTION_SPI_MISO_PORT            GPIOB
#define MOTION_SPI_MISO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTION_SPI_MISO_CLK_DISABLE()   __HAL_RCC_GPIOB_CLK_DISABLE()

// MOSI (Master Output Slave Input): PB.5
#define MOTION_SPI_MOSI_PIN             GPIO_PIN_5
#define MOTION_SPI_MOSI_MODE            GPIO_MODE_AF_PP
#define MOTION_SPI_MOSI_PULL            GPIO_NOPULL
#define MOTION_SPI_MOSI_SPEED           GPIO_SPEED_HIGH
#define MOTION_SPI_MOSI_ALTERNATE       GPIO_AF5_SPI1
#define MOTION_SPI_MOSI_PORT            GPIOB
#define MOTION_SPI_MOSI_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define MOTION_SPI_MOSI_CLK_DISABLE()   __HAL_RCC_GPIOB_CLK_DISABLE()

// NSS/CSN/CS: PG.2
#define MOTION_SPI_CS_PIN               GPIO_PIN_2
#define MOTION_SPI_CS_MODE              GPIO_MODE_OUTPUT_PP
#define MOTION_SPI_CS_PULL              GPIO_PULLUP
#define MOTION_SPI_CS_SPEED             GPIO_SPEED_HIGH
#define MOTION_SPI_CS_ALTERNATE         GPIO_AF5_SPI1
#define MOTION_SPI_CS_PORT              GPIOG
#define MOTION_SPI_CS_CLK_ENABLE()      __HAL_RCC_GPIOG_CLK_ENABLE()
#define MOTION_SPI_CS_CLK_DISABLE()     __HAL_RCC_GPIOG_CLK_DISABLE()
 
// IRQ: PA.0
#define MOTION_SPI_IRQ_PIN            GPIO_PIN_0
#define MOTION_SPI_IRQ_MODE           GPIO_MODE_IT_RISING
#define MOTION_SPI_IRQ_PULL           GPIO_NOPULL
#define MOTION_SPI_IRQ_SPEED          GPIO_SPEED_HIGH
#define MOTION_SPI_IRQ_ALTERNATE      0
#define MOTION_SPI_IRQ_PORT           GPIOA
#define MOTION_SPI_IRQ_CLK_ENABLE()   __GPIOA_CLK_ENABLE()
   
#define MOTION_SPI_EXTI_IRQn          EXTI0_IRQn
#define MOTION_SPI_EXTI_IRQHandler    EXTI0_IRQHandler
#define MOTION_SPI_EXTI_PIN           MOTION_SPI_IRQ_PIN
#define MOTION_SPI_EXTI_PORT          MOTION_SPI_IRQ_PORT

#define MOTION_SPI_RX_DMA                       DMA2_Stream2
#define MOTION_SPI_RX_DMA_CH                    DMA_CHANNEL_3
#define MOTION_SPI_DMA_CLK_ENABLE()             __HAL_RCC_DMA2_CLK_ENABLE();
#define MOTION_SPI_RX_DMA_Stream_IRQn           DMA2_Stream2_IRQn
#define MOTION_SPI_RX_DMA_Stream_IRQ_PP         1
#define MOTION_SPI_RX_DMA_Stream_IRQ_SP         0
#define MOTION_SPI_RX_DMA_Stream_IRQHandler     DMA2_Stream2_IRQHandler
#define MOTION_SPI_TX_DMA                       DMA2_Stream3
#define MOTION_SPI_TX_DMA_CH                    DMA_CHANNEL_3
#define MOTION_SPI_TX_DMA_Stream_IRQn           DMA2_Stream3_IRQn
#define MOTION_SPI_TX_DMA_Stream_IRQ_PP         1
#define MOTION_SPI_TX_DMA_Stream_IRQ_SP         0
#define MOTION_SPI_TX_DMA_Stream_IRQHandler     DMA2_Stream3_IRQHandler
   
/** @addtogroup STEVAL-IDP005V1_IO_MEMORY STEVAL-IDP005V1 IO Memory
  * @{
  */

#define M95M01_DF_HOLD_GPIO_PORT                GPIOI
#define M95M01_DF_HOLD_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOI_CLK_ENABLE()
#define M95M01_DF_HOLD_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOI_CLK_DISABLE()
#define M95M01_DF_HOLD_PIN                      GPIO_PIN_5
#define M95M01_DF_W_GPIO_PORT                   GPIOI
#define M95M01_DF_W_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOI_CLK_ENABLE()
#define M95M01_DF_W_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOI_CLK_DISABLE()
#define M95M01_DF_W_PIN                         GPIO_PIN_6

/**
  * @}
  */

/** @addtogroup STEVAL_IDP005V1_IO_SYSTICK_SW_IRQ IDP005_IO SYSTICK SW IRQ 
  * @{
  */

#define SYSTICK_SW_PIN                           GPIO_PIN_1
#define SYSTICK_SW_IRQn                          EXTI1_IRQn
#define SYSTICK_SW_IRQ_PP                        3
#define SYSTICK_SW_IRQ_SP                        0
#define SYSTICK_SW_IRQHandler                    EXTI1_IRQHandler

/**
  * @}
  */

/** @addtogroup STEVAL_IDP005V1_IO_IOLINK IDP005 IO-Link
  * @{
  */

#define L6362A_EN_DIAG_GPIO_PORT                GPIOE
#define L6362A_EN_DIAG_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOE_CLK_ENABLE()
#define L6362A_EN_DIAG_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOE_CLK_DISABLE()
#define L6362A_EN_DIAG_PIN                      GPIO_PIN_7
#define L6362A_OL_GPIO_PORT                     GPIOE
#define L6362A_OL_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOE_CLK_ENABLE()
#define L6362A_OL_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOE_CLK_DISABLE()
#define L6362A_OL_PIN                           GPIO_PIN_8
#define L6362A_EXTI_IRQn                        EXTI9_5_IRQn
#define L6362A_EXTI_IRQ_PP                      6
#define L6362A_EXTI_IRQ_SP                      0
#define L6362A_EXTI_IRQHandler                  EXTI9_5_IRQHandler

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
   
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_PERIPH_CONF_H */


/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
