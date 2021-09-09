/**
  ******************************************************************************
  * @file    PREDMNT1_config.h
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   FP-IND-PREDMNT1 configuration
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
#ifndef __PREDMNT1_CONFIG_H
#define __PREDMNT1_CONFIG_H

/** @addtogroup Projects
  * @{
  */

/** @addtogroup APPLICATIONS Applications
  * @{
  */

/** @addtogroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @defgroup PREDMNT1_CONFIG
  * @{
  */

/** @defgroup PREDMNT1_CONFIG_EXPORTED_DEFINES PREDMNT1_CONFIG Exported Defines
  * @{
  */

/* @brief  Scale factor. It is used to scale acceleration from mg to g */ 
#define FROM_MG_TO_G            0.001
#define USE_EEPROM              1       //!< Comment to not use the mounted EEPROM
#define UART_TD_TIME_SENDING    10       //!< Time to send the Time Domain results in ms


#define ACCELERO_INSTANCE       IDP005_ISM330DLC_0
#define TEMPERATURE_INSTANCE_1  IDP005_HTS221_0
#define HUMIDITY_INSTANCE       IDP005_HTS221_0
#define TEMPERATURE_INSTANCE_2  IDP005_LPS22HB_0
#define PRESSURE_INSTANCE       IDP005_LPS22HB_0

#define ACCELERO_FIFO_XL_NO_DEC ISM330DLC_FIFO_XL_NO_DEC
#define ACCELERO_BYPASS_MODE    ISM330DLC_BYPASS_MODE
#define ACCELERO_FIFO_MODE      ISM330DLC_FIFO_MODE
#define ACCELERO_STREAM_MODE    ISM330DLC_STREAM_MODE
#define ACCELERO_DRDY_PULSED    ISM330DLC_DRDY_PULSED
#define ACCELERO_DRDY_LATCHED   ISM330DLC_DRDY_LATCHED

/*************** Debug Defines ******************/
/* For enabling the printf on UART */
#define PREDMNT1_ENABLE_PRINTF

/*************** Don't Change the following defines *************/

/* Package Version only numbers 0->9 */
#define PREDMNT1_VERSION_MAJOR '1'
#define PREDMNT1_VERSION_MINOR '1'
#define PREDMNT1_VERSION_PATCH '0'


/* Package Name */
#define PACKAGENAME   "STEVAL-BFA001V1"
#define HWUSED        "STEVAL-IDP005V1"
#define CONFIG_NAME   "Application - Vibration Analysis"

/*****************
* Sensor Setting *
******************/
#define HPF_ODR_DIV_4           ISM330DLC_XL_HP_ODR_DIV_4   //!< ISM330DLC HPF Configuration  
#define HPF_ODR_DIV_100         ISM330DLC_XL_HP_ODR_DIV_100 //!< ISM330DLC HPF Configuration 
#define HPF_ODR_DIV_9           ISM330DLC_XL_HP_ODR_DIV_9   //!< ISM330DLC HPF Configuration  
#define HPF_ODR_DIV_400         ISM330DLC_XL_HP_ODR_DIV_400 //!< ISM330DLC HPF Configuration
#define HPF_NONE                ISM330DLC_XL_HP_NA          //!< HP Filter Disabling

/* Set defaul value for HPF Cut frequency */
#define SENSOR_HPF_CUT_VALUE                    HPF_ODR_DIV_400
/* Set defaul ODR value to 6600Hz for FFT demo */
#define SENSOR_ACC_ORD_VALUE                    6660.0f
/* Set default decimation value for the FIFO with no decimation */
#define SENSOR_ACC_FIFO_DECIMATION_VALUE        1
/* Set defaul FIFO ODR value */
#define SENSOR_ACC_FIFO_ORD_VALUE               6660.0f
/* Default value for Accelerometer full scale in g */
#define SENSOR_ACC_FS_DEFAULT                   2



/*************************
* Serial control section *
**************************/
#ifdef PREDMNT1_ENABLE_PRINTF
#define PREDMNT1_PRINTF(...) printf(__VA_ARGS__)
#else /* PREDMNT1_ENABLE_PRINTF */
  #define PREDMNT1_PRINTF(...)
#endif /* PREDMNT1_ENABLE_PRINTF */

#define PREDMNT1_SCANF(...) scanf(__VA_ARGS__)


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

#endif /* __PREDMNT1_CONFIG_H */

/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
