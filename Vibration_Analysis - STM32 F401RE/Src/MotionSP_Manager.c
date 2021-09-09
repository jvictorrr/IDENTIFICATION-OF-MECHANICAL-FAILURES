/**
  ******************************************************************************
  * @file    MotionSP_Manager.c
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   This file includes 
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

/** @addtogroup MOTIONSP_MANAGER MotionSP Manager
  * @{
  */

/** @defgroup MOTIONSP_MANAGER_PRIVATE_VARIABLES MotionSP Manager Private Variables
  * @{
  */

uint8_t RestartFlag = 1;
sAccelerometer_Parameter_t Accelerometer_Parameters;
uint32_t StartTick = 0;
static uint8_t Accelero_Drdy = 0;
static float MotionSP_Sensitivity;
static bool IsAcceleroFifoToRead = false;

/**
  * @}
  */


/** @defgroup MOTIONSP_MANAGER_IMPORTED_VARIABLES MotionSP Manager Imported Variables
  * @{
  */

extern volatile uint8_t AccIntReceived;
extern volatile uint8_t FifoEnabled;
extern sAxesMagBuff_t AccAxesAvgMagBuff;

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
static uint8_t MotionSP_AccMeasInit(void);
static uint8_t AccOdrMeas(sAcceleroODR_t *pAcceleroODR);
static void AcceleroFifoRead(IDP005_MOTION_SENSOR_AxesRaw_t *pSensorAxesRaw);
static void FillCircBuffFromFifo(sCircBuffer_t *pAccCircBuff, float AccSensitivity);



/** @addtogroup MOTIONSP_MANAGER_PRIVATE_FUNCTIONS MotionSP Manager Private Functions
  * @{
  */

/**
  * @brief  Init the Accelerometer Settings and MotionSP Vibration parameters
  *         using the default values from MotionSP_Config.h & PREDMNT1_config.h         
  * @param  None
  * @return None
  */   
void MotionSP_SetDefaultVibrationParam(void)
{ 
//  PREDMNT1_PRINTF("\r\n\tSet Accelerometer & Vibration Parameters\r\n");

  /* Set default parameters for accelerometer */
  Accelerometer_Parameters.hw_hpf_cut = SENSOR_HPF_CUT_VALUE;
  Accelerometer_Parameters.AccOdr     = SENSOR_ACC_ORD_VALUE;
  Accelerometer_Parameters.FifoOdr    = SENSOR_ACC_FIFO_ORD_VALUE;
  Accelerometer_Parameters.fs         = SENSOR_ACC_FS_DEFAULT;

  /* Set default parameters for MotionSP library */
  MotionSP_Parameters.size      = SIZE_DEFAULT;
  MotionSP_Parameters.tau       = TAU_DEFAULT;
  MotionSP_Parameters.window    = WINDOW_DEFAULT;
  MotionSP_Parameters.td_type   = TD_DEFAULT;
  MotionSP_Parameters.tacq      = TACQ_DEFAULT;
  MotionSP_Parameters.ovl       = OVL_DEFAULT;
}

/**
  * @brief  Init the MotionSP Vibration parameters
  * @param  None
  * @return None
  */ 
void MotionSP_VibrationInit(void)
{
//  PREDMNT1_PRINTF("\33[%dm", FG_GREEN);
  
//  PREDMNT1_PRINTF("\r\nMotionSP Vibration Initialization\r\n\r\n");
   
  if ((MotionSP_Parameters.size) <= FFT_SIZE_MAX) 
  {
        /* Send the parameters to terminal */
 //   PREDMNT1_PRINTF("MotionSP Parameters are:\r\n");
//    PREDMNT1_PRINTF("\tFFT size: %i\r\n", MotionSP_Parameters.size);
 //   PREDMNT1_PRINTF("\tFFT ovl : %i%%\r\n", MotionSP_Parameters.ovl);
  //  PREDMNT1_PRINTF("\tTacq    : %i ms\r\n", MotionSP_Parameters.tacq);

    // Reset the real accelero ODR value
    memset((void *)(&AcceleroODR), 0x00, sizeof(sAcceleroODR_t));
    // Reset the accelero circular buffer
    memset((void *)(&AccCircBuffer), 0x00, sizeof(sCircBuffer_t)); 
 
    // Set the initial position of the accelero circular buffer
    AccCircBuffer.IdPos = (uint16_t)(-1);

    /* Create circular buffer and initialize result variables */
    AccCircBuffer.Size = (uint16_t)((float)(MotionSP_Parameters.size*(((float)CIRC_BUFFER_RATIO)/10)));
    
    magSize = MotionSP_Parameters.size/2;

    // Reset the TimeDomain parameter values
    memset((void *)(&sTimeDomain), 0x00, sizeof(sAcceleroParam_t));
    
    // Reset the counters of the number of sums about the calculation of the average
    memset((void *)(&AccSumCnt), 0x00, sizeof(sSumCnt_t));  

    MotionSP_SetWindFiltArray(Filter_Params, MotionSP_Parameters.size, (Filt_Type_t)MotionSP_Parameters.window);

    /* Reset the flag to enable the first FFT computation */
    fftIsEnabled = 0;

    arm_rfft_fast_init_f32(&fftS, MotionSP_Parameters.size);

    /* It is the minimum value to do the first FFT */
    accCircBuffIndexForFft = MotionSP_Parameters.size - 1;

    FinishAvgFlag = 0;
    RestartFlag = 1;    
  }
  else
  {
    /* Send fault info to terminal */
  //  PREDMNT1_PRINTF("\r\n\tFFT size is out of range.\r\n");
  }  
}

/**
  * @brief  Set accelerometer parameters for MotionSP Vibration
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */   
uint8_t SetAccelerometerParameters(void)
{
  int8_t BSP_Error= 0;
  uint8_t ret= 1;
  
 // PREDMNT1_PRINTF("Update Accelerometer Settings:\r\n");

   /* Enable the HP Filter */
  if ((BSP_Error = IDP005_MOTION_SENSOR_Enable_HP_Filter(ACCELERO_INSTANCE, 
                                                         SENSOR_HPF_CUT_VALUE)) != BSP_ERROR_NONE)
  {
  //  PREDMNT1_PRINTF("\tError Enable HP Filter (BSP_ERROR = %d)\r\n", BSP_Error);
    ret= 0;
  }
  else
  {
 //   PREDMNT1_PRINTF("\tOk Enable HP Filter\r\n");
  }

  
 /* Set FS value */
  if ((BSP_Error = IDP005_MOTION_SENSOR_SetFullScale(ACCELERO_INSTANCE, 
                                                     MOTION_ACCELERO,
                                                     Accelerometer_Parameters.fs)) != BSP_ERROR_NONE)
  {
 //   PREDMNT1_PRINTF("\tError on FullScale Setting(BSP_ERROR = %d)\r\n", BSP_Error);
    ret= 0;
  }
  else
  {
    // Get Sensitivity
    IDP005_MOTION_SENSOR_GetSensitivity(ACCELERO_INSTANCE,
                                        MOTION_ACCELERO,
                                        &MotionSP_Sensitivity );
 //   PREDMNT1_PRINTF("\tOk FullScale Setting\r\n");
  } 
  
  /* Set ODR value */
  if ((BSP_Error = IDP005_MOTION_SENSOR_SetOutputDataRate(ACCELERO_INSTANCE, 
                                                          MOTION_ACCELERO,
                                                          Accelerometer_Parameters.AccOdr)) != BSP_ERROR_NONE)
  {
  //  PREDMNT1_PRINTF("\tError Set Output Data Rate (BSP_ERROR = %d)\r\n", BSP_Error);
    ret= 0;
  }
  else
  {
 //   PREDMNT1_PRINTF("\tOk Set Output Data Rate\r\n");
  }  

  /* Turn-on time delay */
  HAL_Delay(40);

    /* Measure and calculate ODR */
  if (MotionSP_AccMeasInit() == 1)
  {
  //  PREDMNT1_PRINTF("\tError measure and calculate ODR\r\n");
    ret= 0;
  }
  else
  {
 //   PREDMNT1_PRINTF("\tOk measure and calculate ODR\r\n");
    /* Send the parameters to terminal */
 //   PREDMNT1_PRINTF("\tODR = %.2f Hz\r\n", AcceleroODR.Frequency);
  }
  
  return ret;
}

/**
  * @brief  Vibration Analysis Data processing
  * @param  None
  * @retval None
  */
void MotionSP_VibrationAnalysis(void)
{
#define FFTSIZEDELTA  (MotionSP_Parameters.size*((100.0-MotionSP_Parameters.ovl)/100.0))
  static uint8_t accCircBuffIndexForFftOvf = 0;
  static uint16_t accCircBuffIndexPre = (uint16_t)(-1);
  uint32_t ActualTick;
  uint16_t accCircBuffIndexTmp = 0;
  uint16_t accCircBuffIndexForFftTmp = 0;
  
  
  if ( (AccCircBuffer.IdPos != accCircBuffIndexPre) && (AccCircBuffer.IdPos != (uint16_t)(-1)) )
  {
    accCircBuffIndexPre = AccCircBuffer.IdPos;
    
    accCircBuffIndexTmp = AccCircBuffer.IdPos + (AccCircBuffer.Ovf * AccCircBuffer.Size);
    accCircBuffIndexForFftTmp = accCircBuffIndexForFft + (accCircBuffIndexForFftOvf * AccCircBuffer.Size);
    
    if (accCircBuffIndexTmp >= accCircBuffIndexForFftTmp)
    {
      /* Check the Tick value */
      ActualTick = HAL_GetTick(); 
      if ((ActualTick - StartTick) > MotionSP_Parameters.tacq)
      {
        FinishAvgFlag = 1;
        disable_FIFO();
      }
      MotionSP_FrequencyDomainProcess();
      
      accCircBuffIndexForFftOvf = 0;
      accCircBuffIndexForFft += FFTSIZEDELTA;
      if (accCircBuffIndexForFft >= AccCircBuffer.Size)
      {
        accCircBuffIndexForFft -= AccCircBuffer.Size;
        
        if (!AccCircBuffer.Ovf)
          accCircBuffIndexForFftOvf = 1;
      }
      
      AccCircBuffer.Ovf = 0;
    }
  } 
}

/* Private function ----------------------------------------------------------*/

/**
  * @brief Read 3-axes acceleration raw data from FIFO
  * @param pSensorAxesRaw Pointer to be filled with the new data
  */
static void AcceleroFifoRead(IDP005_MOTION_SENSOR_AxesRaw_t *pSensorAxesRaw)
{
  static uint16_t fifoId = 0;
  int16_t data_out;
  uint16_t *p_u16;
  
  p_u16 = (uint16_t *)pSensorAxesRaw;
  for (uint8_t axis=0; axis<3; axis++)
  { 
    IDP005_MOTION_SENSOR_FIFO_Get_Data_Word(ACCELERO_INSTANCE,
                                            MOTION_ACCELERO, &data_out );
    *p_u16++ = data_out;
  }
  
  fifoId++;
  if (fifoId == Accelerometer_Parameters.AccFifoSize)
  {
    fifoId = 0;
    IsAcceleroFifoToRead = false;
    BSP_LED_Toggle(USER_LED);
  }
}

static void FillCircBuffFromFifo(sCircBuffer_t *pAccCircBuff, float AccSensitivity)
{
  IDP005_MOTION_SENSOR_AxesRaw_t rawAcc;
  SensorVal_f_t mgAcc;
  SensorVal_f_t mgAccNoDC;

  // Get a complete acceleration from FIFO
  AcceleroFifoRead(&rawAcc);
  
  // Convert raw acceleration in float [mg]
  mgAcc.AXIS_X = (float)(rawAcc.x*AccSensitivity);
  mgAcc.AXIS_Y = (float)(rawAcc.y*AccSensitivity);
  mgAcc.AXIS_Z = (float)(rawAcc.z*AccSensitivity);
  
//  // High Pass Filter to delete Accelerometer Offset
  MotionSP_accDelOffset(&mgAccNoDC, &mgAcc, DC_SMOOTH, RestartFlag);
  
  // Fill the circular buffer with the accelerations without DC component
  MotionSP_CreateAccCircBuffer(pAccCircBuff, mgAcc);
}


void FuncOn_DRDY_XL(void)
{
  Accelero_Drdy = 1;
}

void FuncOn_FifoFull(void)
{
  BSP_LED_Toggle(USER_LED);
  
  IsAcceleroFifoToRead = true;
  
  while(IsAcceleroFifoToRead)
  {
    if (EXTI->PR & ISM330DLC_INT2_GPIO_PIN)
      while(1);
    
    FillCircBuffFromFifo(&AccCircBuffer, MotionSP_Sensitivity);
    
    // Time Domain Processing 
    MotionSP_TimeDomainProcess(&sTimeDomain, (Td_Type_t)MotionSP_Parameters.td_type, RestartFlag);
    
    // Clear the restart flag
    if (RestartFlag)
      RestartFlag = 0;
  }
}

/**
  * @brief 	Measurement initialization for the accelerometer
  * @return 0 in case of success
  * @return 1 in case of failure
  */    
static uint8_t MotionSP_AccMeasInit(void)
{
  uint8_t retValue = 1;
  
  // Set ODR
  IDP005_MOTION_SENSOR_SetOutputDataRate(ACCELERO_INSTANCE,
                                         MOTION_ACCELERO,
                                         Accelerometer_Parameters.AccOdr);
  
  // Set Full-Scale
  IDP005_MOTION_SENSOR_SetFullScale(ACCELERO_INSTANCE,
                                    MOTION_ACCELERO,
                                    Accelerometer_Parameters.fs);
  
  // Get Sensitivity
  IDP005_MOTION_SENSOR_GetSensitivity(ACCELERO_INSTANCE,
                                      MOTION_ACCELERO,
                                      &MotionSP_Sensitivity );
  
  // Set HPF
  IDP005_MOTION_SENSOR_Enable_HP_Filter(ACCELERO_INSTANCE,
                                        Accelerometer_Parameters.hw_hpf_cut);

  
  /* Evaluate the real accelerometer ODR **********************************/
  uint8_t iteration = 0;
  do
  {
    retValue = AccOdrMeas(&AcceleroODR);
    iteration++;
  } while( (retValue != 0) && (iteration < 3) );
  /************************************************************************/
  
  if (retValue != 0)
    return 1;
  
  return 0;
}

/**
  * @brief 	Measurement of the accelerometer output data rate
  * @param 	pAcceleroODR Pointer to be fill with the new value
  * @return 0 in case of success
  * @return 1 in case of failure
  */
static uint8_t AccOdrMeas(sAcceleroODR_t *pAcceleroODR)
{
#define ODRMEASURINGTIME  1000   // in ms
#define TOLERANCE         0.10   // from 0.0 to 1.0
#define INTCNTMIN         (uint16_t)((((Accelerometer_Parameters.AccOdr)*(1.0-TOLERANCE))*ODRMEASURINGTIME)/1000)
#define INTCNTMAX         (uint16_t)((((Accelerometer_Parameters.AccOdr)*(1.0+TOLERANCE))*ODRMEASURINGTIME)/1000)
  
  uint8_t retValue = 1;
  uint32_t tkStart;
  uint16_t IntCnt;
  
  // The data-ready pulses are 75 �s long
  IDP005_MOTION_SENSOR_DRDY_Set_Mode(ACCELERO_INSTANCE,ISM330DLC_DRDY_PULSE_CFG);
  
  /* ISM330DLC INT2_DRDY_XL interrupt enable */
  IDP005_MOTION_SENSOR_Set_INT2_DRDY(ACCELERO_INSTANCE, ENABLE);

  Accelero_Drdy = 0;
  IntCnt = 0;
  tkStart = BSP_GetTick();  
  
  do
  {
    if (Accelero_Drdy)
    {
      Accelero_Drdy = 0;
      IntCnt++;
    }
  } while ( (BSP_GetTick() - tkStart) < ODRMEASURINGTIME);
  
  /* ISM330DLC INT2_DRDY_XL interrupt disable */
  IDP005_MOTION_SENSOR_Set_INT2_DRDY(ACCELERO_INSTANCE, DISABLE);
  
  if ((IntCnt < INTCNTMIN) || (IntCnt > INTCNTMAX))
  {
    /* ODR is out of range */
    retValue = 1;
  }
  else
  {
    /* ODR is valid */
    /* Calculate measured ODR and Exponential parameters*/
    pAcceleroODR->Frequency = (IntCnt * 1000) / ODRMEASURINGTIME;
    pAcceleroODR->Period = 1/(pAcceleroODR->Frequency);
    pAcceleroODR->Tau= exp(-(float)(1000*pAcceleroODR->Period)/MotionSP_Parameters.tau);
    retValue = 0;
  }
  
  return retValue;
}

/**
  * @brief  Enable FIFO measuring
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
uint8_t enable_FIFO(void)
{  
    /* Set FIFO to STREAM Mode (Continuous) */
  if (IDP005_MOTION_SENSOR_FIFO_Set_Mode(ACCELERO_INSTANCE, ACCELERO_STREAM_MODE ) != BSP_ERROR_NONE)
  {
    return 0;
  }
  
  /* Enable FIFO full flag interrupt */
  if (IDP005_MOTION_SENSOR_FIFO_Set_INT2_FIFO_Full(ACCELERO_INSTANCE, ENABLE) != BSP_ERROR_NONE)
  {
    return 0;
  }
  
  FifoEnabled = 1;
  return 1;
}

/**
  * @brief  Disable FIFO measuring
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
uint8_t disable_FIFO(void)
{
  /* Set FIFO to bypass mode */
  if (IDP005_MOTION_SENSOR_FIFO_Set_Mode(ACCELERO_INSTANCE, ACCELERO_BYPASS_MODE) != BSP_ERROR_NONE)
  {
    return 0;
  }
  
  /* Disable FIFO full flag interrupt */
  if (IDP005_MOTION_SENSOR_FIFO_Set_INT2_FIFO_Full(ACCELERO_INSTANCE, DISABLE) != BSP_ERROR_NONE)
  {
    return 0;
  }  
  FifoEnabled = 0;
  return 1;
}

/**
  * @brief  Restart FIFO
  * @param  None
  * @retval 1 in case of success
  * @retval 0 in case of failure
  */
uint8_t restart_FIFO(void)
{
  AccIntReceived = 0;

  /* FIFO bypass */
  if (IDP005_MOTION_SENSOR_FIFO_Set_Mode(ACCELERO_INSTANCE, ACCELERO_BYPASS_MODE) != BSP_ERROR_NONE)
  {
    return 0;
  }
  /* FIFO Mode*/
  if (IDP005_MOTION_SENSOR_FIFO_Set_Mode(ACCELERO_INSTANCE, ACCELERO_STREAM_MODE) != BSP_ERROR_NONE)
  {
    return 0;
  }

  return 1;
}


/**
  * @brief  Configure the FIFO in according with the algorithm setting
  * @param  None
  */
void MotionSP_ConfigFifo(void)
{
    float k = 0.80f;
  
  if (MotionSP_Parameters.size == 1024)
  {
    if (MotionSP_Parameters.ovl < 20)
      k = 0.66f;   
  }
  else
  {
    if (MotionSP_Parameters.ovl < 20)
      k = 0.33f;
    else if (MotionSP_Parameters.ovl < 40)
      k = 0.40f;
    else if (MotionSP_Parameters.ovl < 60)
      k = 0.50f;
  }
  
  Accelerometer_Parameters.AccFifoSize=(uint16_t)(((float)MotionSP_Parameters.size*(1.0f-((float)MotionSP_Parameters.ovl/100.0f)))*k);
  
  int8_t BSP_Error= 0;
  /* Enable AXL data to FIFO with no decimation */
  if ((BSP_Error = IDP005_MOTION_SENSOR_FIFO_Set_Decimation(ACCELERO_INSTANCE,
                                                            MOTION_ACCELERO,
                                                            (uint8_t)ISM330DLC_FIFO_XL_NO_DEC)) != BSP_ERROR_NONE)
  {
    //PREDMNT1_PRINTF("\tError Set FIFO Decimation (BSP_ERROR = %d)\r\n", BSP_Error);
  }
  else
  {
  //  PREDMNT1_PRINTF("\tOk Set FIFO Decimation\r\n");
  }  

  /* Set FIFO ODR value */
  if ((BSP_Error = IDP005_MOTION_SENSOR_FIFO_Set_ODR_Value(ACCELERO_INSTANCE, 
                                                      Accelerometer_Parameters.FifoOdr)) != BSP_ERROR_NONE)
  {
 //   PREDMNT1_PRINTF("\tError Set FIFO ODR Value (BSP_ERROR = %d)\r\n", BSP_Error);
  }
  else
  {
  //  PREDMNT1_PRINTF("\tOk Set FIFO ODR Value\r\n");
  } 
  
  /* Set FIFO watermark */
  if ((BSP_Error = IDP005_MOTION_SENSOR_FIFO_Set_Watermark_Level(ACCELERO_INSTANCE, Accelerometer_Parameters.AccFifoSize*3)) != BSP_ERROR_NONE)
  {
//    PREDMNT1_PRINTF("\tError Set FIFO Threshold Level (BSP_ERROR = %d)\r\n", BSP_Error);
  }
  else
  {
 //   PREDMNT1_PRINTF("\tOk Set FIFO Threshold Level\r\n");
  } 

  /* Set FIFO depth to be limited to watermark threshold level  */
  if ((BSP_Error = IDP005_MOTION_SENSOR_FIFO_Set_Stop_On_Fth(ACCELERO_INSTANCE, ENABLE)) != BSP_ERROR_NONE)
  {
 //   PREDMNT1_PRINTF("\tError Set FIFO Stop On Fth (BSP_ERROR = %d)\r\n", BSP_Error);
  }
  else
  {
 //   PREDMNT1_PRINTF("\tOk Set FIFO Stop On Fth\r\n");
  } 

   
  if ( (uint16_t)((Accelerometer_Parameters.AccFifoSize*3*2) > (1024*4)) )
  {
 //   PREDMNT1_PRINTF("\r\n\tFIFO size will be %i byte than exceed its maximum value, 4 kbyte.\r\n",
      //              (uint16_t)(Accelerometer_Parameters.AccFifoSize*3*2));
 //   PREDMNT1_PRINTF("\tPlease, reduce the SIZE_DEFAULT or the OVL_DEFAULT.\r\n");
    Error_Handler();
  }
  else
  {
  //  PREDMNT1_PRINTF("\tFIFO size will be configured to store %i acceleration samples\r\n",
    //                (uint16_t)(Accelerometer_Parameters.AccFifoSize));
  }
  
    /* Set FIFO to STREAM Mode (Continuous) */
  if (IDP005_MOTION_SENSOR_FIFO_Set_Mode(ACCELERO_INSTANCE, ACCELERO_STREAM_MODE ) != BSP_ERROR_NONE)
  {
 //   PREDMNT1_PRINTF("\tError Set FIFO in Continuous Mode (BSP_ERROR = %d)\r\n", BSP_Error);
  }
  else
  {
 //   PREDMNT1_PRINTF("\tOk Set FIFO in Continuous Mode\r\n");
  }

    /* Disable FIFO full flag interrupt */
  if (IDP005_MOTION_SENSOR_FIFO_Set_INT2_FIFO_Full(ACCELERO_INSTANCE, ENABLE) != BSP_ERROR_NONE)
  {
//    PREDMNT1_PRINTF("\tError Set FIFO FULL INTP on INT2 path (BSP_ERROR = %d)\r\n", BSP_Error);
  }
  else
  {
    FifoEnabled = 1;
  //  PREDMNT1_PRINTF("\tOk Set FIFO FULL INTP on INT2 path\r\n");
    /* Start of the Time Window */
    StartTick = HAL_GetTick();
  }
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


/************************ (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
