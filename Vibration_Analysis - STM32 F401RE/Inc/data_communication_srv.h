/**
  ******************************************************************************
  * @file    data_communication_srv.h
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   Header for data_communication_srv.c
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
#ifndef __DATA_COMMUNICATION_SRV_H
#define __DATA_COMMUNICATION_SRV_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "MotionSP_Manager.h"
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

/** @addtogroup DATA_COMMUNICATION Data Communication
  * @{
  */
  
/** @defgroup DATA_COMM_EXPORTED_DEFINES Data Communication Exported Defines
  * @{
  */

#define FG_BLACK    30 //!< Black foreground color for terminal control escape sequences
#define FG_RED      31 //!< Red foreground color for terminal control escape sequences
#define FG_GREEN    32 //!< Green foreground color for terminal control escape sequences
#define FG_YELLOW   33 //!< Yellow foreground color for terminal control escape sequences
#define FG_BLUE     34 //!< Blue foreground color for terminal control escape sequences
#define FG_MAGENTA  35 //!< Magenta foreground color for terminal control escape sequences
#define FG_CYAN     36 //!< Cyan foreground color for terminal control escape sequences
#define FG_WHITE    37 //!< White foreground color for terminal control escape sequences

#define BG_BLACK    40 //!< Black background color for terminal control escape sequences
#define BG_RED      41 //!< Red background color for terminal control escape sequences
#define BG_GREEN    42 //!< Green background color for terminal control escape sequences
#define BG_YELLOW   43 //!< Yellow background color for terminal control escape sequences
#define BG_BLUE     44 //!< Blue background color for terminal control escape sequences
#define BG_MAGENTA  45 //!< Magenta background color for terminal control escape sequences
#define BG_CYAN     46 //!< Cyan background color for terminal control escape sequences
#define BG_WHITE    47 //!< White background color for terminal control escape sequences

/**
  * @}
  */

/** @defgroup DATA_COMM_EXPORTED_FUNCTIONS Data Communication Exported Functions
  * @{
  */
void TerminalScreenAppInfo(void);
uint8_t SetVibrationParam(void);
void SendVibrationResult(void);
void TimeDomain_UartDataSend(sAcceleroParam_t *sTimeDomain);

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

#endif /* __DATA_COMMUNICATION_SRV_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
