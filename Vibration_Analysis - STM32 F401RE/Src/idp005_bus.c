/**
  ******************************************************************************
  * @file  : idp005_bus.c
  * @author  System Research & Applications Team - Catania Lab.
  * @version $Version$
  * @date    $Date$
  * @brief : source file for the BSP BUS IO driver
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
#include "stm32f4xx_hal.h"
#include "idp005_bus.h"
#include "idp005_errno.h"
#include "idp005_periph_conf.h"

#define TIMEOUT_DURATION 1000

__weak HAL_StatusTypeDef MX_I2C1_Init(I2C_HandleTypeDef *hi2c);
__weak HAL_StatusTypeDef MX_SPI1_Init(SPI_HandleTypeDef* hspi);

/** @addtogroup Projects
  * @{
  */

/** @addtogroup APPLICATIONS Applications
  * @{
  */

/** @addtogroup VIBRATION_ANALYSIS Vibration Analysis
  * @{
  */

/** @defgroup IDP005_BUS
  * @{
  */

/** @defgroup IDP005V1_BUS_Private_Variables BUS Private Variables
  * @{
  */
I2C_HandleTypeDef hbusi2c1;
SPI_HandleTypeDef hbusspi1;						

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
static uint32_t IsI2C1MspCbValid = 0;
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)						
static uint32_t IsSPI1MspCbValid = 0;	
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */	

/**
  * @}
  */

/** @defgroup IDP005V1_BUS_Private_FunctionPrototypes BUS Private Function Prototypes
  * @{
  */

static void I2C1_MspInit(I2C_HandleTypeDef *i2cHandle);
static void I2C1_MspDeInit(I2C_HandleTypeDef *i2cHandle);
static void SPI1_MspInit(SPI_HandleTypeDef* spiHandle); 
static void SPI1_MspDeInit(SPI_HandleTypeDef* spiHandle);
/**
  * @}
  */

  
/** @defgroup IDP005V1_BUS_Exported_Functions STEVAL-IDP005V1_BUS Exported Functions
  * @{
  */   
/* BUS IO driver over I2C Peripheral */
/*******************************************************************************
                            BUS OPERATIONS OVER I2C
*******************************************************************************/
/**
  * @brief  Initialize a bus
  * @param None
  * @retval BSP status
  */
int32_t BSP_I2C1_Init(void)
{
  int32_t ret = BSP_ERROR_NONE;

  hbusi2c1.Instance  = I2C1;

  if (HAL_I2C_GetState(&hbusi2c1) == HAL_I2C_STATE_RESET)
  {
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
    /* Init the I2C Msp */
    I2C1_MspInit(&hbusi2c1);
#else
    if (IsI2C1MspCbValid == 0U)
    {
      if (BSP_I2C1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif

    /* Init the I2C */
    if (MX_I2C1_Init(&hbusi2c1) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    else if (HAL_I2CEx_ConfigAnalogFilter(&hbusi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
  * @brief  DeInitialize a bus
  * @param None
  * @retval BSP status
  */
int32_t BSP_I2C1_DeInit(void)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 0)
  /* DeInit the I2C */
  I2C1_MspDeInit(&hbusi2c1);
#endif

  if (HAL_I2C_DeInit(&hbusi2c1) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }
  return ret;
}


/**
  * @brief Return the status of the Bus
  * @retval bool
  */
int32_t BSP_I2C1_IsReady(void)
{
  return (HAL_I2C_GetState(&hbusi2c1) == HAL_I2C_STATE_READY);
}

/**
  * @brief  Write registers through bus (8 bits)
  * @param  Addr: Device address on Bus.
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written
  * @retval BSP status
  */
int32_t BSP_I2C1_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Mem_Write(&hbusi2c1, (uint8_t)DevAddr,
                        (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,
                        (uint8_t *)pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Read registers through a bus (8 bits)
  * @param  DevAddr: Device address on BUS
  * @param  Reg: The target register address to read
  * @retval BSP status
  */
int32_t  BSP_I2C1_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Mem_Read(&hbusi2c1, DevAddr, (uint16_t)Reg,
                       I2C_MEMADD_SIZE_8BIT, pData,
                       len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = HAL_OK;
  }

  return ret;
}

/**
  * @brief  Write registers through bus (16 bits)
  * @param  Addr: Device address on Bus.
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written
  * @retval BSP status
  */
int32_t BSP_I2C1_WriteReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Mem_Write(&hbusi2c1, (uint8_t)DevAddr,
                        (uint16_t)Reg, I2C_MEMADD_SIZE_16BIT,
                        (uint8_t *)pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Read registers through a bus (16 bits)
  * @param  DevAddr: Device address on BUS
  * @param  Reg: The target register address to read
  * @retval BSP status
  */
int32_t  BSP_I2C1_ReadReg16(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Mem_Read(&hbusi2c1, DevAddr, (uint16_t)Reg,
                       I2C_MEMADD_SIZE_16BIT, pData,
                       len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Send an amount width data through bus (Simplex)
  * @param  DevAddr: Device address on Bus.
  * @param  pData: Data pointer
  * @param  Length: Data length
  * @retval BSP status
  */
int32_t BSP_I2C1_Send(uint16_t DevAddr, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Master_Transmit(&hbusi2c1, DevAddr, pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = len;
  }

  return ret;
}

/**
  * @brief  Receive an amount of data through a bus (Simplex)
  * @param  DevAddr: Device address on Bus.
  * @param  pData: Data pointer
  * @param  Length: Data length
  * @retval BSP status
  */
int32_t BSP_I2C1_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  if (HAL_I2C_Master_Receive(&hbusi2c1, DevAddr, pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
    ret = len;
  }

  return ret;
}

/**
  * @brief  Send and receive an amount of data through bus (Full duplex)
  * @param  DevAddr: Device address on Bus.
  * @param  pTxdata: Transmit data pointer
  * @param  pRxdata: Receive data pointer
  * @param  Length: Data length
  * @retval BSP status
  */
int32_t BSP_I2C1_SendRecv(uint16_t DevAddr, uint8_t *pTxdata, uint8_t *pRxdata, uint16_t len)
{
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  /*
   * Send and receive an amount of data through bus (Full duplex)
   * I2C is Half-Duplex protocol
   */
  if ((BSP_I2C1_Send(DevAddr, pTxdata, len) == len) && \
      (BSP_I2C1_Recv(DevAddr, pRxdata, len) == len))
  {
    ret = len;
  }

  return ret;
}

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
/**
  * @brief Register Default BSP I2C1 Bus Msp Callbacks
  * @retval BSP status
  */
int32_t BSP_I2C1_RegisterDefaultMspCallbacks(void)
{

  __HAL_I2C_RESET_HANDLE_STATE(&hbusi2c1);

  /* Register MspInit Callback */
  if (HAL_I2C_RegisterCallback(&hbusi2c1, HAL_I2C_MSPINIT_CB_ID, I2C1_MspInit)  != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if (HAL_I2C_RegisterCallback(&hbusi2c1, HAL_I2C_MSPDEINIT_CB_ID, I2C1_MspDeInit) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }
  IsI2C1MspCbValid = 1;

  return BSP_ERROR_NONE;
}

/**
  * @brief BSP I2C1 Bus Msp Callback registering
  * @param Callbacks     pointer to I2C1 MspInit/MspDeInit callback functions
  * @retval BSP status
  */
int32_t BSP_I2C1_RegisterMspCallbacks(BSP_I2C_Cb_t *Callbacks)
{
  /* Prevent unused argument(s) compilation warning */
  __HAL_I2C_RESET_HANDLE_STATE(&hbusi2c1);

  /* Register MspInit Callback */
  if (HAL_I2C_RegisterCallback(&hbusi2c1, HAL_I2C_MSPINIT_CB_ID, Callbacks->pMspI2cInitCb)  != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  /* Register MspDeInit Callback */
  if (HAL_I2C_RegisterCallback(&hbusi2c1, HAL_I2C_MSPDEINIT_CB_ID, Callbacks->pMspI2cDeInitCb) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }

  IsI2C1MspCbValid = 1;

  return BSP_ERROR_NONE;
}
#endif /* USE_HAL_I2C_REGISTER_CALLBACKS */

/* I2C1 init function */

__weak HAL_StatusTypeDef MX_I2C1_Init(I2C_HandleTypeDef *hi2c)
{
  HAL_StatusTypeDef ret = HAL_OK;
  hi2c->Instance = I2C1;
  hi2c->Init.ClockSpeed = 400000;
  hi2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c->Init.OwnAddress1 = 0;
  hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c->Init.OwnAddress2 = 0;
  hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(hi2c) != HAL_OK)
  {
    ret = HAL_ERROR;
  }
  return ret;
}

static void I2C1_MspInit(I2C_HandleTypeDef *i2cHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /* I2C1 GPIO Configuration
      PB7     ------> I2C1_SDA
      PB8     ------> I2C1_SCL  */
  
  /* Enable I2C GPIO clocks */
  ENV_I2C_SDA_GPIO_CLK_ENABLE();

  GPIO_InitStruct.Pin = ENV_I2C_SDA_PIN | ENV_I2C_SCL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = ENV_I2C_SDA_AF;
  HAL_GPIO_Init(ENV_I2C_SDA_GPIO_PORT, &GPIO_InitStruct);

  /* Peripheral clock enable */
  ENV_I2C_CLK_ENABLE();
  
  /* Force the I2C peripheral clock reset */
  ENV_I2C_FORCE_RESET();
  
  /* Release the I2C peripheral clock reset */
  ENV_I2C_RELEASE_RESET();
}

/**
 * @brief  I2C MSP De-Initialization
 * @param hi2c: I2C handle pointer
 * @retval None
 */
static void I2C1_MspDeInit(I2C_HandleTypeDef *i2cHandle)
{
  /* Peripheral clock disable */
  ENV_I2C_CLK_DISABLE();

  HAL_GPIO_DeInit(ENV_I2C_SCL_GPIO_PORT, ENV_I2C_SDA_PIN | ENV_I2C_SCL_PIN);
}


/* BUS IO driver over SPI Peripheral */
/*******************************************************************************
                            BUS OPERATIONS OVER SPI
*******************************************************************************/

/**
  * @brief  Initializes SPI HAL.
  * @retval None
  * @retval BSP status
  */
int32_t BSP_SPI1_Init(void) 
{
  int32_t ret = BSP_ERROR_NONE;
  
  hbusspi1.Instance  = SPI1;
  if (HAL_SPI_GetState(&hbusspi1) == HAL_SPI_STATE_RESET) 
  { 
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
    /* Init the SPI Msp */
    SPI1_MspInit(&hbusspi1);
#else
    if(IsSPI1MspCbValid == 0U)
    {
      if(BSP_SPI1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif   
    
    /* Init the SPI */
    if (MX_SPI1_Init(&hbusspi1) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    __HAL_SPI_ENABLE(&hbusspi1);
  } 
  return ret;
}

/**
  * @brief  DeInitializes SPI HAL.
  * @retval None
  * @retval BSP status
  */
int32_t BSP_SPI1_DeInit(void) {
  int32_t ret = BSP_ERROR_BUS_FAILURE;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
  SPI1_MspDeInit(&hbusspi1);
#endif  
  
  if (HAL_SPI_DeInit(&hbusspi1) == HAL_OK) {
    ret = BSP_ERROR_NONE;
  }
  
  return ret;
}

/**
  * @brief  Write Data through SPI BUS.
  * @param  pData: Data
  * @param  len: Length of data in byte
  * @retval BSP status
  */
int32_t BSP_SPI1_Send(uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;
  
  if(HAL_SPI_Transmit(&hbusspi1, pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
      ret = len;
  }
  return ret;
}

/**
  * @brief  Receive Data from SPI BUS
  * @param  pData: Data
  * @param  len: Length of data in byte
  * @retval BSP status
  */
int32_t  BSP_SPI1_Recv(uint8_t *pData, uint16_t len)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;
  
  if(HAL_SPI_Receive(&hbusspi1, pData, len, TIMEOUT_DURATION) == HAL_OK)
  {
      ret = len;
  }
  return ret;
}

/**
  * @brief  Send and Receive data to/from SPI BUS (Full duplex)
  * @param  pData: Data
  * @param  len: Length of data in byte
  * @retval BSP status
  */
int32_t BSP_SPI1_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t len)
{
  int32_t ret = BSP_ERROR_UNKNOWN_FAILURE;
  
  if(HAL_SPI_TransmitReceive(&hbusspi1, pTxData, pRxData, len, TIMEOUT_DURATION) == HAL_OK)
  {
      ret = len;
  }
  return ret;
}


/* SPI1 init function */ 
__weak HAL_StatusTypeDef MX_SPI1_Init(SPI_HandleTypeDef* hspi)
{
  HAL_StatusTypeDef ret = HAL_OK;
  hspi->Instance = SPI1;
  hspi->Init.Mode = SPI_MODE_MASTER;
  hspi->Init.Direction = SPI_DIRECTION_2LINES;
  hspi->Init.DataSize = SPI_DATASIZE_8BIT;
  hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi->Init.NSS = SPI_NSS_SOFT;
  hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi->Init.TIMode = SPI_TIMODE_DISABLE;
  hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi->Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(hspi) != HAL_OK)
  {
    ret = HAL_ERROR;
  }
 return ret;
}


static void SPI1_MspInit(SPI_HandleTypeDef* spiHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable Peripheral clock */
  MOTION_SPI_CLK_ENABLE();
  
  MOTION_SPI_MISO_CLK_ENABLE();
  MOTION_SPI_MOSI_CLK_ENABLE();
  MOTION_SPI_SCLK_CLK_ENABLE();
  
  /**SPI1 GPIO Configuration    
  PB3     ------> SPI1_SCK
  PB4     ------> SPI1_MISO
  PB5     ------> SPI1_MOSI */
  
  GPIO_InitStruct.Pin = MOTION_SPI_SCLK_PIN;
  GPIO_InitStruct.Mode = MOTION_SPI_SCLK_MODE;
  GPIO_InitStruct.Pull = MOTION_SPI_SCLK_PULL;
  GPIO_InitStruct.Speed = MOTION_SPI_SCLK_SPEED;
  GPIO_InitStruct.Alternate = MOTION_SPI_SCLK_ALTERNATE;
  HAL_GPIO_Init(MOTION_SPI_SCLK_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = MOTION_SPI_MISO_PIN;
  GPIO_InitStruct.Mode = MOTION_SPI_MISO_MODE;
  GPIO_InitStruct.Pull = MOTION_SPI_MISO_PULL;
  GPIO_InitStruct.Speed = MOTION_SPI_MISO_SPEED;
  GPIO_InitStruct.Alternate = MOTION_SPI_MISO_ALTERNATE;
  HAL_GPIO_Init(MOTION_SPI_MISO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = MOTION_SPI_MOSI_PIN;
  GPIO_InitStruct.Mode = MOTION_SPI_MOSI_MODE;
  GPIO_InitStruct.Pull = MOTION_SPI_MOSI_PULL;
  GPIO_InitStruct.Speed = MOTION_SPI_MOSI_SPEED;
  GPIO_InitStruct.Alternate = MOTION_SPI_MISO_ALTERNATE;
  HAL_GPIO_Init(MOTION_SPI_MOSI_PORT, &GPIO_InitStruct);
}

static void SPI1_MspDeInit(SPI_HandleTypeDef* spiHandle)
{
    /* Peripheral clock disable */
  __HAL_RCC_SPI1_CLK_DISABLE();
  
  /** SPI1 GPIO Configuration    
  PB3     ------> SPI1_SCK
  PB4     ------> SPI1_MISO
  PB5     ------> SPI1_MOSI */
  HAL_GPIO_DeInit(GPIOB, MOTION_SPI_SCLK_PIN|MOTION_SPI_MISO_PIN|MOTION_SPI_MOSI_PIN);
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
