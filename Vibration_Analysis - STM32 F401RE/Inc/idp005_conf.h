/**
  ******************************************************************************
  * @file    idp005_conf.h
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   This file contains definitions for the MEMS components
  *          bus interfaces
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
#ifndef __IDP005_CONF_H__
#define __IDP005_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "idp005.h"
#include "idp005_bus.h"
#include "idp005_errno.h"

/** @addtogroup Projects
  * @{
  */

/** @addtogroup APPLICATIONS Applications
  * @{
  */

/** @addtogroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @addtogroup IDP005_CONF IDP005 Configuration Define
  * @{
  */
  

/* ########################## HSE/HSI Values adaptation ##################### */
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).  
  */
#if !defined  (HSE_VALUE) 
    #define HSE_VALUE    (24000000U) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#define USE_IDP005_ENV_SENSOR_HTS221_0          1U
#define USE_IDP005_ENV_SENSOR_LPS22HB_0         1U
#define USE_IDP005_MOTION_SENSOR_ISM330DLC_0	1U

#define IDP005_I2C_Init					BSP_I2C1_Init
#define IDP005_I2C_DeInit				BSP_I2C1_DeInit
#define IDP005_I2C_ReadReg				BSP_I2C1_ReadReg
#define IDP005_I2C_WriteReg     		BSP_I2C1_WriteReg
#define IDP005_GetTick		        	BSP_GetTick
  
#define BSP_ISM330DLC_SPI_Init          BSP_SPI1_Init
#define BSP_ISM330DLC_SPI_DeInit        BSP_SPI1_DeInit
#define BSP_ISM330DLC_SPI_Send	        BSP_SPI1_Send
#define BSP_ISM330DLC_SPI_Recv          BSP_SPI1_Recv
    
// NSS/CSN/CS: PG.2
#define BSP_ISM330DLC_CS_PIN            GPIO_PIN_2
#define BSP_ISM330DLC_CS_PORT           GPIOG


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

#endif /* __IDP005_CONF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

