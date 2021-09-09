/**
  ******************************************************************************
  * @file    main.h 
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "PREDMNT1_config.h"
#include "data_communication_srv.h"
#include <stdbool.h>

/** @defgroup Projects
  * @{
  */

/** @defgroup APPLICATIONS Applications
  * @{
  */

/** @defgroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @defgroup MAIN Main
  * @{
  */

/** @defgroup MAIN_EXPORTED_TYPES Main Exported Types
  * @{
  */

/**
  * @brief MCU identifiers
  */
typedef struct
{
  uint16_t McuDevId;    //!< Device identifier
  uint16_t McuRevId;    //!< Revision identifier
  uint32_t u_id_31_0;   //!< 31:0 unique ID bits
  uint32_t u_id_63_32;  //!< 63:32 unique ID bits
  uint32_t u_id_95_64;  //!< 95:64 unique ID bits
  uint16_t FlashSize;   //!< The size of the device Flash memory expressed in Kbytes
  uint8_t Package;      //!< Package data
} sMcuId_t;

/**
  * @}
  */

/** @defgroup MAIN_EXPORTED_FUNCTIONS Main Exported Functions
  * @{
  */

void Error_Handler(void);
void Get_McuId(sMcuId_t *pMcuId);

/**
  * @}
  */


/** @defgroup MAIN_Exported_Defines Main Exported Defines
  * @{
  */

#define MCR_F2I_1D(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (int32_t)((in-out_int)*10);};
#define MCR_F2I_2D(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (int32_t)((in-out_int)*100);};
#define MCR_F2I_3D(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (abs)((int32_t)((in-out_int)*1000));};

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

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
