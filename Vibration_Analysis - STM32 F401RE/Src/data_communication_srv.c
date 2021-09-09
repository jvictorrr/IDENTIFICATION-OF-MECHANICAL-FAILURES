/**
  ******************************************************************************
  * @file    data_communication_srv.c
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief   
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
#include "data_communication_srv.h"
#include "stm32f4xx_hal.h"
#include "idp005_uart.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stm32f4xx.h"

#define MESSAGE_MAX_LEN 256
//----------------------------------------------------------------------




UART_HandleTypeDef huart2;

MX_USART2_UART_Init(void);





//----------------------------------------------------------------
/** @addtogroup Projects
  * @{
  */

/** @addtogroup APPLICATIONS Applications
  * @{
  */

/** @addtogroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @defgroup DATA_COMMUNICATION Data Communication
  * @{
  */

/** @defgroup DATA_COMM_PRIVATE_CONSTANTS Data Communication Private Constants
  * @brief    This file includes Signal Processing interface functions 
  * @{
  */

static const char *pAccelerometer_ParameterNames[ACCELEROMETER_PARAMETER_NRMAX] = {
  "HpfCut =",
  "Acc_Odr=",
  "FifoOdr=",
  "Acc_Fs =",
};

static const char *pMotionSP_ParameterNames[MOTIONSP_PARAMETER_NRMAX] = {
  "size=",
  "tau=",
  "wind=",
  "tdtype=",
  "tacq=",
  "ovl=",
  "subrng=",
};

/**
  * @}
  */

/** @defgroup DATA_COMM_PRIVATE_VARIABLES Data Communication Private Variables
  * @{
  */

DMA_HandleTypeDef hdma_SrvUart_rx;
DMA_HandleTypeDef hdma_SrvUart_tx;
uint8_t SrvUartTxBuffer[SRV_UART_BUFFER_SIZE];
uint8_t SrvUartRxBuffer[SRV_UART_BUFFER_SIZE];
uint8_t TimeDomainHeaderIsSent = 0;
uint8_t SrvUartRxFilled;

/**
  * @}
  */

/** @defgroup DATA_COMM_PRIVATE_FUNCTIONS Data Communication Private Functions
  * @{
  */
static void UartGetVibrationParamValues(void);
static void FFT_Result_DataSend(sAxesMagResults_t* FftResult);
static void FFT_Array_DataSend(sAxesMagBuff_t *ArrayToSend, uint16_t ActualMagSize);
static void SensorPk_DataSend(sAcceleroParam_t *sTimeDomain);

/** @defgroup DATA_COMM_IMPORTED_VARIABLES Data Communication Imported Variables
  * @{
  */


extern sAxesMagBuff_t AccAxesAvgMagBuff;        /* Array Acc magnitude average values */
extern sAccelerometer_Parameter_t Accelerometer_Parameters;

/**
  * @}
  */

/** @addtogroup DATA_COMM_EXPORTED_FUNCTIONS Data Communication Exported Functions
  * @{
  */

/**
  * @brief  Send MCU info to the terminal via UART
  * @param  None
  * @return None
  */
void TerminalScreenAppInfo(void)
{
  /* Structure to store MCU info */
  sMcuId_t McuId; 
  
  /* Get MCU Identifiers */
  Get_McuId(&McuId);
  
  while((HAL_UART_GetState(&UartHandle) & HAL_UART_STATE_BUSY_TX ) == HAL_UART_STATE_BUSY_TX);
  
  //PREDMNT1_PRINTF("\33[%dm", FG_CYAN);
  
  //PREDMNT1_PRINTF("STMicroelectronics\r\n");
  
 // PREDMNT1_PRINTF("\t%s:\r\n"
   //               "\t%s\r\n"
     //               "\tVersion %c.%c.%c\r\n"
       //               "\r\n",
         //             PACKAGENAME,
//                      CONFIG_NAME,
  //                    PREDMNT1_VERSION_MAJOR,PREDMNT1_VERSION_MINOR,PREDMNT1_VERSION_PATCH);
  
//  PREDMNT1_PRINTF("\r\nSTM32F4xx Libraries & IDE informations\r\n");
  //PREDMNT1_PRINTF("\t(HAL %lu.%lu.%lu_%lu)\r\n"
    //              "\tCompiled %s %s"
                    
//#if defined (__IAR_SYSTEMS_ICC__)
//                    " (IAR)\r\n"
//                    " (IAR)\r\n"
//#elif defined (__CC_ARM)
                  //    " (KEIL)\r\n"
//#elif defined (__GNUC__)
  //                      " (openstm32)\r\n"
//#endif
  //                      "\r\n",
    //                    HAL_GetHalVersion() >>24,
      //                  (HAL_GetHalVersion() >>16)&0xFF,
      //                  (HAL_GetHalVersion() >>16)&0xFF,
//                         (HAL_GetHalVersion() >> 8)&0xFF,
  //                       HAL_GetHalVersion()      &0xFF,
    //                   __DATE__,__TIME__);

//  PREDMNT1_PRINTF("\tBoard           \t%s\r\n\r\n"
//                  "\tSTM32 MCU ID    \t0x%08lX%08lX%08lX\r\n"
  //                  "\tSTM32 MCU SYSCLK\t%.2f MHz\r\n"
    //                  "\tSTM32 MCU HCLK  \t%.2f MHz\r\n"
      //                  "\tSTM32 MCU PCLK1 \t%.2f MHz\r\n"
        //                  "\tSTM32 MCU PCLK2 \t%.2f MHz\r\n"
          //                  "\r\n",
            //                HWUSED,
              //              McuId.u_id_95_64, McuId.u_id_63_32, McuId.u_id_31_0,
               //             (float)(HAL_RCC_GetSysClockFreq()/1.0e6),
                 //           (float)(HAL_RCC_GetHCLKFreq()/1.0e6),
//                            (float)(HAL_RCC_GetPCLK1Freq()/1.0e6),
  //                          (float)(HAL_RCC_GetPCLK2Freq()/1.0e6));

  PREDMNT1_PRINTF("\33[%dm", FG_MAGENTA);
}

/**
  * @brief Set Vibration Param Values
  * @param None
  * @return 1 if the vibration param values are changed.
  */    
uint8_t SetVibrationParam(void)
{
  char UserAnswer;
  uint8_t SaveVibrationParam = 0;
  
  //PREDMNT1_PRINTF("\r\n\t****************************************************\r\n");
//  PREDMNT1_PRINTF("\t*   Accelerometer & Vibration DEFAULT parameters   *\r\n");
 // PREDMNT1_PRINTF("\t****************************************************\r\n");
  
//  do
//  {
   // PREDMNT1_PRINTF("\r\n\tAccelerometer parameters are:\r\n");
  //  PREDMNT1_PRINTF("\t%s%d\t", pAccelerometer_ParameterNames[0], Accelerometer_Parameters.hw_hpf_cut);
//    PREDMNT1_PRINTF("%s%d\t", pAccelerometer_ParameterNames[1], Accelerometer_Parameters.AccOdr);
//    PREDMNT1_PRINTF("%s%d\t", pAccelerometer_ParameterNames[2], Accelerometer_Parameters.FifoOdr);
  //  PREDMNT1_PRINTF("%s%d\t", pAccelerometer_ParameterNames[3], Accelerometer_Parameters.fs);
    //PREDMNT1_PRINTF("\r\n");

//    PREDMNT1_PRINTF("\r\n\tMotionSP parameters are:\r\n");
//    PREDMNT1_PRINTF("\t%s%d\t", pMotionSP_ParameterNames[0], MotionSP_Parameters.size);
 //   PREDMNT1_PRINTF("%s%d\t", pMotionSP_ParameterNames[1], MotionSP_Parameters.tau);
 //   PREDMNT1_PRINTF("%s%d\t", pMotionSP_ParameterNames[2], MotionSP_Parameters.window);
 //  PREDMNT1_PRINTF("%s%d\t", pMotionSP_ParameterNames[3], MotionSP_Parameters.td_type);
 //   PREDMNT1_PRINTF("%s%d\t", pMotionSP_ParameterNames[4], MotionSP_Parameters.tacq);
 //   PREDMNT1_PRINTF("\r\n\r\n");



	  /*
  *  PREDMNT1_PRINTF("Change the parameters? [y/n]\r\n");
*    do
*    {
    *  scanf("%c",&UserAnswer);
 *   } while((UserAnswer!='y') && (UserAnswer!='Y') && (UserAnswer!='n') && (UserAnswer!='N'));
 *   PREDMNT1_PRINTF("\r\n");
*
  *  if((UserAnswer == 'y') || (UserAnswer == 'Y'))
   * {
    *   Get new vibration parameters from user keyboard
   *   UartGetVibrationParamValues();
    *  SaveVibrationParam= 1;
   *
  *    PREDMNT1_PRINTF("\r\nNew vibration parameters are: \r\n");
 *   }
*  } while((UserAnswer!='n') && (UserAnswer!='N'));
  */
  return SaveVibrationParam;
}

/**
  * @brief Send by UART of vibration results
  * @param  None
  * @return None
  */    
void SendVibrationResult(void) 
{
  //PREDMNT1_PRINTF("\33[%dm", FG_YELLOW);
//  PREDMNT1_PRINTF("\r\n");
  
  /* Send Accelerometer ARRAYs FFT average values */ 
//  PREDMNT1_PRINTF("\n\r*** FFT Spectral Analysis ***\n\r|bin Freq|     Amplitude [m/s2]     |\n\r|  [Hz]  |    X   |    Y   |    Z   |\r\n");

 // FFT_Array_DataSend(&AccAxesAvgMagBuff, (MotionSP_Parameters.size)/2);
	  FFT_Array_DataSend(&AccAxesAvgMagBuff, (MotionSP_Parameters.size));
  // Send Accelerometer FFT Result values 
  //PREDMNT1_PRINTF("\r\n\r\n*** FFT Results ***\r\n");
  FFT_Result_DataSend(&AccAxesMagResults);
  
  // Send Max Peak Time Domain Result values 
  while((HAL_UART_GetState(&UartHandle) & HAL_UART_STATE_BUSY_TX ) == HAL_UART_STATE_BUSY_TX);
  //PREDMNT1_PRINTF("\r\n*** Acceleration Time Domain Max Peak ***\r\n");
  SensorPk_DataSend(&sTimeDomain);
}


/**
  * @brief  Get the vibration parameter values to uart console
  * @param  None
  * @return None
  */
static void UartGetVibrationParamValues()
{
  uint32_t newValue = 0;
  
//  PREDMNT1_PRINTF("\tEnter new vibration parameters ...\r\n");
  
  for(int p=1; p < (ACCELEROMETER_PARAMETER_NRMAX); p++)
  {
    switch (p)
    {
     /* HpfCutOff ( High Pass Filter Cutoff frequency setting) */
    case 0:
      //PREDMNT1_PRINTF("\r\nHpfCutoff= ");
      //PREDMNT1_PRINTF("(0, 1, 2, 3)\r\n");
     // PREDMNT1_SCANF("%lu",&newValue);
      switch (newValue)
      {
      case 0:
      case 1:
      case 2:
      case 3:
        break;
      default:
        newValue = Accelerometer_Parameters.hw_hpf_cut;
        break;
      }
      Accelerometer_Parameters.hw_hpf_cut = newValue;
      break;
      
    /* AccOdr ( Accelerometer Output Data Rate in Hz) */
    case 1:
    //  PREDMNT1_PRINTF("\r\n\tAccOdr= ");
   //   PREDMNT1_PRINTF("(13, 26, 52, 104, 208, 416, 833, 1660, 3330, 6660)\r\n");
     // PREDMNT1_SCANF("%lu",&newValue);
      switch (newValue)
      {
      case 13:
      case 26:
      case 52:
      case 104:
      case 208:
      case 416:
      case 833:
      case 1660:
      case 3330:
      case 6660:
        break;
      default:
        newValue = Accelerometer_Parameters.AccOdr;
        break;
      }
      Accelerometer_Parameters.AccOdr = newValue;
      break;

    /* AccOdr ( Accelerometer Output Data Rate in Hz) */
    case 2:
  //    PREDMNT1_PRINTF("\r\n\tFifoOdr= ");
    //  PREDMNT1_PRINTF("(13, 26, 52, 104, 208, 416, 833, 1660, 3330, 6660)\r\n");
   //   PREDMNT1_SCANF("%lu",&newValue);
      switch (newValue)
      {
      case 13:
      case 26:
      case 52:
      case 104:
      case 208:
      case 416:
      case 833:
      case 1660:
      case 3330:
      case 6660:
        break;
      default:
        newValue = Accelerometer_Parameters.FifoOdr;
        break;
      }
      Accelerometer_Parameters.FifoOdr = newValue;
      break;
      
    /* fs (Full Scale in g) */
    case 3:
  //    PREDMNT1_PRINTF("\r\n\tfs= ");
  //    PREDMNT1_PRINTF("(2, 4, 8, 16)\r\n");
  //    PREDMNT1_SCANF("%lu",&newValue);
      switch (newValue)
      {
      case 2:
      case 4:
      case 8:
      case 16:
        break;
      default:
        newValue = Accelerometer_Parameters.fs;
        break;
      }
      Accelerometer_Parameters.fs = newValue;
      break;
    }
  }
  
  for(int p=0; p < (MOTIONSP_PARAMETER_NRMAX-2); p++)
  {
    if( (p != 1) && (p != 3))
   
    switch (p)
    {
    /* size (FFT SIZE) */
    case 0:
  //    PREDMNT1_PRINTF("\r\n\tsize= ");
   //   PREDMNT1_PRINTF("(256, 512, 1024, 2048)\r\n");
    //  PREDMNT1_SCANF("%lu",&newValue);
      switch (newValue)
      {
      case 256:
      case 512:
      case 1024:
      case 2048:
        break;
      default:
        newValue = MotionSP_Parameters.size;
        break;
      }
      MotionSP_Parameters.size= newValue;
      break;
    
    /* tau (RMS FILTER in ms) */
    case 1:
      break;
      
    /*   wind (PRE-FFT WINDOWING Method) */
    case 2:
 //     PREDMNT1_PRINTF("\r\n\twind= ");
  //    PREDMNT1_PRINTF("(RECTANGULAR= 0, HANNING= 1, HAMMING= 2, FLAT_TOP= 3)\r\n");
  //    PREDMNT1_SCANF("%lu",&newValue);
      switch(newValue)
      {
      case 0:
      case 1:
      case 2:
      case 3:
        break;
      default:
        newValue = MotionSP_Parameters.window;
        break;
      }
      MotionSP_Parameters.window= newValue;
      break;

    /*   tdtype (Time Domain Feature to Show */
    case 3:
      break;

    /* tacq (TIME ACQUISITION WINDOW in ms) */
    case 4:
 //     PREDMNT1_PRINTF("\r\n\tTacquisition= ");
  //    PREDMNT1_PRINTF("[500 - 60000]\r\n");
    //  PREDMNT1_SCANF("%lu",&newValue);
      if ((newValue < 500) || (newValue > 60000))
        newValue = MotionSP_Parameters.tacq;
      MotionSP_Parameters.tacq= newValue;
      break;
      
    /* ovl (FFT OVERLAPPING in %) */
    case 5:
  //    PREDMNT1_PRINTF("[5 - 95]\r\n");
  //    PREDMNT1_SCANF("%lu",&newValue);
//      if ((newValue < 5) || (newValue > 95))
//        newValue = pMotionSP_Parameters->ovl;
      break;
    }
  }
}

static void FFT_Result_DataSend(sAxesMagResults_t* FftResult)
{
  float BinFreqStep;
  
  uint32_t X_IntPart, Y_IntPart, Z_IntPart;
  uint32_t X_DecPart, Y_DecPart, Z_DecPart;
  
//  BinFreqStep = (AcceleroODR.Frequency/2)/magSize;
  BinFreqStep = (AcceleroODR.Frequency)/magSize;

  //PREDMNT1_PRINTF("\r\n FFT AVERAGE Number = %d \r\n\r\n",AccAxesMagResults.X_FFT_AVG);
  
  MCR_F2I_3D(FftResult->X_Value, X_IntPart, X_DecPart);
  MCR_F2I_3D(FftResult->Y_Value, Y_IntPart, Y_DecPart);
  MCR_F2I_3D(FftResult->Z_Value, Z_IntPart, Z_DecPart);
  
 // PREDMNT1_PRINTF("Max_Amplitudes  -> Xa:%.3lu.%3lu| Ya:%.3lu.%3lu| Za:%.3lu.%3lu|\r\n", X_IntPart, X_DecPart, Y_IntPart, Y_DecPart, Z_IntPart, Z_DecPart);

  MCR_F2I_3D((FftResult->X_Index*BinFreqStep), X_IntPart, X_DecPart);
  MCR_F2I_3D((FftResult->Y_Index*BinFreqStep), Y_IntPart, Y_DecPart);
  MCR_F2I_3D((FftResult->Z_Index*BinFreqStep), Z_IntPart, Z_DecPart);
  
  //PREDMNT1_PRINTF("Bin_Frequencies -> Xf:%.3lu.%3lu| Yf:%.3lu.%3lu| Zf:%.3lu.%3lu|\r\n", X_IntPart, X_DecPart, Y_IntPart, Y_DecPart, Z_IntPart, Z_DecPart);
}

/**
  *  @brief  Send by UART the FFT array result
  *  @param  ArrayToSend Final FFT array result
  *  @param  ActualMagSize Actual size of the FFT magnitude elements
  *  @return None
  */
static void FFT_Array_DataSend(sAxesMagBuff_t *ArrayToSend, uint16_t ActualMagSize)
{
  static uint32_t userTick = 0;
  float BinFreqStep;
  
  uint32_t BinFreqStep_IntPart;
  uint32_t BinFreqStep_DecPart;
  
  uint32_t X_IntPart, Y_IntPart, Z_IntPart;
  uint32_t X_DecPart, Y_DecPart, Z_DecPart;

//  const char *JSON_STRING ="{\"Frequencia\":%.4lu.%.2lu, \"Eixo X\":%.1lu.%.3lu, \"Eixo Y\":%.1lu.%.3lu, \"Z\":%.1lu.%.3lu}\n";
  const char *JSON_STRING ="{\"Frequencia\":%.lu.%.lu, \"X\":%.lu, \"Y\":%.lu, \"Z\":%.lu}\r\n";

      char json_message[MESSAGE_MAX_LEN];

 BinFreqStep= ((AcceleroODR.Frequency / 2) / (ActualMagSize));

  //    BinFreqStep = (AcceleroODR.Frequency)/ActualMagSize;

  if ( (BSP_GetTick() - userTick) >=5)
  {
    userTick = BSP_GetTick();
  //  for(int i=0; i<ActualMagSize; i++)
    for(int i=0; i<ActualMagSize; i++)
    {
      MCR_F2I_2D((i*BinFreqStep), BinFreqStep_IntPart, BinFreqStep_DecPart);

      MCR_F2I_3D(ArrayToSend->AXIS_X[i], X_IntPart, X_DecPart);
      MCR_F2I_3D(ArrayToSend->AXIS_Y[i], Y_IntPart, Y_DecPart);
      MCR_F2I_3D(ArrayToSend->AXIS_Z[i], Z_IntPart, Z_DecPart);

      snprintf(json_message,MESSAGE_MAX_LEN, JSON_STRING, BinFreqStep_IntPart, BinFreqStep_DecPart, X_DecPart, Y_DecPart,Z_DecPart);

            PREDMNT1_PRINTF(json_message);


            HAL_Delay(20);
    }

  } 
  HAL_Delay(2000);
  //HAL_Delay(1000);
}

/**
  * @brief Send by UART the accelero peak values
  * @param sTimeDomain Time domain values
  * @return None
  */
static void SensorPk_DataSend(sAcceleroParam_t *sTimeDomain)
{


  uint32_t X_IntPart, Y_IntPart, Z_IntPart;
  uint32_t X_DecPart, Y_DecPart, Z_DecPart;
  
  MCR_F2I_3D(sTimeDomain->AccPeak.AXIS_X, X_IntPart, X_DecPart);
  MCR_F2I_3D(sTimeDomain->AccPeak.AXIS_Y, Y_IntPart, Y_DecPart);
  MCR_F2I_3D(sTimeDomain->AccPeak.AXIS_Z, Z_IntPart, Z_DecPart);

        
 // PREDMNT1_PRINTF("\r\n| Xpk:%.3lu.%.3lu| Ypk:%.3lu.%.3lu| Zpk:%.3lu.%.3lu|\r\n",
       //           X_IntPart,X_DecPart,Y_IntPart,Y_DecPart,Z_IntPart, Z_DecPart);
}


/**
  * @brief Send by UART the Time Domain results inside the callback
  * @param sTimeDomain Time domain values
  * @return None
  */
void TimeDomain_UartDataSend(sAcceleroParam_t *sTimeDomain)
{
  static uint32_t TdTick = 0;
  uint32_t deltaTick;
  
  deltaTick = BSP_GetTick() - TdTick;
  
  if ( deltaTick >= UART_TD_TIME_SENDING )
  {
    TdTick = BSP_GetTick();
    
    // Send data via uart if possible
    if((HAL_UART_GetState(&UartHandle) & HAL_UART_STATE_BUSY_TX ) != HAL_UART_STATE_BUSY_TX) {
      
      if(TimeDomainHeaderIsSent == 0) 
      {
        switch (MotionSP_Parameters.td_type) {
        case TD_SPEED:
          // print to screen the TimeDomain header
         // strcpy((char *)SrvUartTxBuffer, "\r\n|     *** Time Domain Data ***     |\r\n|   Time   |   Speed RMS [mm/s]    |\r\n|   [ms]   |   X   |   Y   |   Z   |\r\n");
          //HAL_UART_Transmit_DMA(&UartHandle, SrvUartTxBuffer, strlen((char *)SrvUartTxBuffer));
          TimeDomainHeaderIsSent = 1;
          break;
        case TD_ACCELERO:
          // print to screen the TimeDomain header
         // strcpy((char *)SrvUartTxBuffer, "\r\n|     *** Time Domain Data ***     |\r\n|   Time   |  Accelero RMS [m/s2]  |\r\n|   [ms]   |   X   |   Y   |   Z   |\r\n");
          // HAL_UART_Transmit_DMA(&UartHandle, SrvUartTxBuffer, strlen((char *)SrvUartTxBuffer));
          TimeDomainHeaderIsSent = 1;
          break;
        case TD_BOTH_TAU:
          // print to screen the TimeDomain header
         // strcpy((char *)SrvUartTxBuffer, "\r\n|\t\t***  Time Domain Data ***\t\t|\r\n|   Time   |  Accelero RMS [m/s2]  |    Speed RMS [mm/s]   |\r\n|   [ms]   |   X   |   Y   |   Z   |   X   |   Y   |   Z   |\r\n");
        //  HAL_UART_Transmit_DMA(&UartHandle, SrvUartTxBuffer, strlen((char *)SrvUartTxBuffer));
          TimeDomainHeaderIsSent = 1;
          break;
        default:
          break;
        }
      }
      else {
        
        switch (MotionSP_Parameters.td_type) {
        case TD_SPEED:
          //sprintf((char *)SrvUartTxBuffer, "|%10lu|%7.3f|%7.3f|%7.3f|\r\n",\
            TdTick,\
              sTimeDomain->SpeedRms.AXIS_X*1000,\
                sTimeDomain->SpeedRms.AXIS_Y*1000,\
                  sTimeDomain->SpeedRms.AXIS_Z*1000);    
          break;
        case TD_ACCELERO:
        //  sprintf((char *)SrvUartTxBuffer, "|%10lu|%7.3f|%7.3f|%7.3f|\r\n",\
            TdTick,\
              sTimeDomain->AccRms.AXIS_X,\
                sTimeDomain->AccRms.AXIS_Y,\
                  sTimeDomain->AccRms.AXIS_Z);    
          break;
        case TD_BOTH_TAU:
       //   sprintf((char *)SrvUartTxBuffer, "|%10lu|%7.3f|%7.3f|%7.3f|%7.3f|%7.3f|%7.3f|\r\n",\
            TdTick,\
              sTimeDomain->AccRms.AXIS_X,\
                sTimeDomain->AccRms.AXIS_Y,\
                  sTimeDomain->AccRms.AXIS_Z,\
                    sTimeDomain->SpeedRms.AXIS_X*1000,\
                      sTimeDomain->SpeedRms.AXIS_Y*1000,\
                        sTimeDomain->SpeedRms.AXIS_Z*1000);    
          break;
        default:
          break;
        }
        HAL_UART_Transmit_DMA(&UartHandle, SrvUartTxBuffer, strlen((char *)SrvUartTxBuffer));
      }
    }
  }
}

/**
  * @}
  */

/** @defgroup DATA_COMM_CALLBACK_FUNCTIONS Data Communication CallBack Functions
  * @{
  */

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @return None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  uint8_t *pLastChar = NULL;
  uint8_t StrOvf = 0;
  
  if(huart->Instance==SRV_UART)
  {
    pLastChar = (huart->pRxBuffPtr)-1;
    
    if (pLastChar == SrvUartRxBuffer+SRV_UART_BUFFER_SIZE-2)
      StrOvf = 1;
    
    /* Send UART echo */
    HAL_UART_Transmit(huart, pLastChar, 1, SRV_UART_TIMEOUT_MAX);
    
    /* Carriage return or the last character has been entered */
    if ((*pLastChar == '\r') || StrOvf) {
      
      if (!StrOvf) {
      
        /* replace \r with string terminator */
        *pLastChar = '\0';
      }
      else {
        
        /* complete the string with its terminator */
        *(pLastChar+1) = '\0';
        
        StrOvf = '\r';
        HAL_UART_Transmit(huart, &StrOvf, 1, SRV_UART_TIMEOUT_MAX);
      }
      
      StrOvf = '\n';
      HAL_UART_Transmit(huart, &StrOvf, 1, SRV_UART_TIMEOUT_MAX);
      SrvUartRxFilled = 1;
      __NOP(); /* String Management */
//      HAL_UART_Receive_IT(huart, SrvUartRxBuffer, 1);
    }
    else {
      
      /* Delete */
      if (*pLastChar == 0x7F) {
        
        /* check if one character has been received at least */
        if (pLastChar > SrvUartRxBuffer) {
          
          /* replace last received characters with string terminator */
          *pLastChar = '\0';
          *(pLastChar-1)= '\0';
          HAL_UART_Receive_IT(huart, pLastChar-1, 1);
        }
        else {
          
          /* replace 'Del' character with string terminator */
          *pLastChar = '\0';
          HAL_UART_Receive_IT(huart, pLastChar, 1);
        }      
      }
      else {
        
        /* wait for next character */
        HAL_UART_Receive_IT(huart, pLastChar+1, 1);
      }
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------






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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
