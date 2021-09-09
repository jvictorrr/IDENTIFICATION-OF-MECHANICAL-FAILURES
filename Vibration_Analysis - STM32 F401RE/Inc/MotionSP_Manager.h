/**
  ******************************************************************************
  * @file    MotionSP_Manager.h
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   Header for MotionSP_Manager.c
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
#ifndef _MOTIONSP_MANAGER_H_
#define _MOTIONSP_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif
  
#include "MotionSP.h"
#include "TargetFeatures.h"

/* Define ------------------------------------------------------------------*/
#define ACCELEROMETER_PARAMETER_NRMAX   4
#define MOTIONSP_PARAMETER_NRMAX        7

/* Pattern of acc X axis */
#define PATTERN_ACC_X_AXIS  0
/* Pattern of acc Y axis */
#define PATTERN_ACC_Y_AXIS  1
/* Pattern of acc Z axis */
#define PATTERN_ACC_Z_AXIS  2

/* Typedefs ------------------------------------------------------------------*/
  
/**
 * @brief  Struct for Accelerometer parameters
 */
typedef struct
{
  /* Accelerometer Internal High Pass Filter  */
  uint8_t hw_hpf_cut;
  /* Accelerometer ODR in Hz */
  uint16_t AccOdr;
  /* FIFO ODR in Hz */
  uint16_t FifoOdr;
  /* Accelerometer full scale in g */
  uint16_t fs;
  /* Accelerometer full size to configure */
  uint16_t AccFifoSize;
} sAccelerometer_Parameter_t;


typedef struct
{
  const char *name;
  const float *odr_list;
  const float *odr_om_list;
  const uint32_t *fs_list;
//  const OP_MODE_t *opmode_list;
//  const ACTIVE_AXIS_t *axis_list;
  const uint32_t *samples_list;
  const uint8_t hp_filter_available;
} sensor_setting_t;

/* Exported Functions Prototypes ---------------------------------------------*/
void FuncOn_FifoFull(void);
void FuncOn_DRDY_XL(void);
void MotionSP_SetDefaultVibrationParam(void);
void MotionSP_VibrationInit(void);
void MotionSP_ConfigFifo(void);

uint8_t SetAccelerometerParameters(void);
void MotionSP_VibrationAnalysis(void);

uint8_t enable_FIFO(void);
uint8_t disable_FIFO(void);
uint8_t restart_FIFO(void);

#ifdef __cplusplus
}
#endif

#endif /* _MOTIONSP_MANAGER_H_ */

/************************ (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/

