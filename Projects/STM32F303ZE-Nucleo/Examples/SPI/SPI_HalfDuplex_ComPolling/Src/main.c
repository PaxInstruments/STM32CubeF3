/**
  ******************************************************************************
  * @file    SPI/SPI_HalfDuplex_ComPolling/Src/main.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   This sample code shows how to use STM32F3xx SPI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          Polling transfer.
  *          The communication is done using 2 Boards.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/** @addtogroup STM32F3xx_HAL_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_ComPolling
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define SYNCHRO_WAIT(NB)       for(int i=0; i<NB; i++){__asm("dsb\n");}

#define READ_REGISTER       0x80
#define COMMAND_COUNTER     0x0F
#define COMMAND_COUNTER_ADD 0x01
#define COMMAND_COUNTER_SUB 0x02

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[2];

/* Buffer used for reception */
uint8_t aRxBuffer[2];

#ifdef MASTER_BOARD
uint8_t counter_local = 20, counter_remote;
#else
uint8_t counter_val = 0xFF, cmd;
#endif

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void SPI_Write(uint8_t val);
static void SPI_Read(uint8_t *val);
#ifdef MASTER_BOARD
static void Command_write(uint8_t command, uint8_t val);
static void Command_read(uint8_t command, uint8_t *val);
#endif
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F3xx HAL library initialization:
       - Configure the Flash prefetch
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 64 MHz */
  SystemClock_Config();
  
  /* Configure LED1, LED2 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  /*##-1- Configure the SPI peripheral #######################################*/
  /* Set the SPI parameters */
  SpiHandle.Instance               = SPIx;
  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  SpiHandle.Init.Direction         = SPI_DIRECTION_1LINE;
  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle.Init.CRCPolynomial     = 7;
  SpiHandle.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
  SpiHandle.Init.NSS               = SPI_NSS_SOFT;
  SpiHandle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;

#ifdef MASTER_BOARD
  SpiHandle.Init.Mode = SPI_MODE_MASTER;
#else
  SpiHandle.Init.Mode = SPI_MODE_SLAVE;
#endif /* MASTER_BOARD */

  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /* set the line direction to prepare the send of the first command*/
  SPI_1LINE_TX(&SpiHandle);

#ifdef MASTER_BOARD
  /* Configure User push-button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  /* Wait for User push-button press before starting the Communication */
  while (BSP_PB_GetState(BUTTON_USER) != GPIO_PIN_SET)
  {
    BSP_LED_Toggle(LED1);
    HAL_Delay(100);
  }
  BSP_LED_Off(LED1);
  
  SPI_1LINE_TX(&SpiHandle);
  __HAL_SPI_ENABLE(&SpiHandle);
  
  /* Initialize the remote counter */
  Command_write(COMMAND_COUNTER, counter_local);

  /*## Read the remote counter value */
  Command_read(COMMAND_COUNTER, &counter_remote);
  
  if(counter_local != counter_remote)
  {
    Error_Handler();
  }
    
  do {
    
    /*## Execute the command counter add */
    counter_local += 7;
    Command_write(COMMAND_COUNTER_ADD, 7);
    Command_read(COMMAND_COUNTER, &counter_remote);
    
    if(counter_local != counter_remote)
    {
      Error_Handler();
    }
    
    /*## Execute the command counter sub */
    counter_local -= 2;
    Command_write(COMMAND_COUNTER_SUB, 2);
    Command_read(COMMAND_COUNTER, &counter_remote);
    
    if(counter_local != counter_remote)
    {
      Error_Handler();
    }

    /* Infinite loop */
    HAL_Delay(50);
    BSP_LED_Toggle(LED2);
  } while(1);

#else /* SLAVE_BOARD */

  /* Enable the SPI to allow communication */
  SPI_1LINE_RX(&SpiHandle);
  __HAL_SPI_ENABLE(&SpiHandle);
  
  /* Infinite loop for the slave, to get command from the master */
  do{
    uint8_t val;
    
    /*## Get the command */
    SPI_Read(&cmd);
    
    /*## execute the command */
    switch(cmd)
    {
    case (COMMAND_COUNTER | READ_REGISTER) :
      __HAL_SPI_DISABLE(&SpiHandle);
      SPI_1LINE_TX(&SpiHandle);
      __HAL_SPI_ENABLE(&SpiHandle);
      
      SPI_Write(counter_val);
      
      __HAL_SPI_DISABLE(&SpiHandle);
      SPI_1LINE_RX(&SpiHandle);
      __HAL_SPI_ENABLE(&SpiHandle);
      
    break;
    case COMMAND_COUNTER :
      SPI_Read(&counter_val);
    break;
    case COMMAND_COUNTER_ADD :
      SPI_Read(&val);
      counter_val += val;
    break;
    case COMMAND_COUNTER_SUB :
      SPI_Read(&val);
      counter_val -= val;
    break;
    default :
      Error_Handler();
      break;
    } 
  }while(1);

#endif /* MASTER_BOARD */
}

/**
  * @brief  This function send a command through SPI bus.
  * @param  command : command id.
  * @param  val : value.
  * @retval None
  */
void SPI_Write(uint8_t val)
{
  /* check TXE flag */
  while((SpiHandle.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE);
  
  /* Write the data */
  *((__IO uint8_t*)&SpiHandle.Instance->DR) = val;
  
  /* Wait BSY flag */
  while((SpiHandle.Instance->SR & SPI_FLAG_FTLVL) != SPI_FTLVL_EMPTY);
  while((SpiHandle.Instance->SR & SPI_FLAG_BSY) == SPI_FLAG_BSY);
}

/**
  * @brief  This function send a command through SPI bus.
  * @param  command : command id.
  * @param  val : value.
  * @retval None
  */
void SPI_Read(uint8_t *val)
{
#ifdef MASTER_BOARD
   /* In master RX mode the clock is automaticaly generated on the SPI enable. 
      So to guarantee the clock generation for only one data, the clock must be 
      disabled after the first bit and before the latest bit */
  __HAL_SPI_ENABLE(&SpiHandle);
  __asm("dsb\n");
  __asm("dsb\n");
  __asm("dsb\n");
  __asm("dsb\n");
  __HAL_SPI_DISABLE(&SpiHandle);
#endif
  
  while((SpiHandle.Instance->SR & SPI_FLAG_RXNE) != SPI_FLAG_RXNE);
  /* read the received data */
  *val = *(__IO uint8_t *)&SpiHandle.Instance->DR;
  while((SpiHandle.Instance->SR & SPI_FLAG_BSY) == SPI_FLAG_BSY);
}



#ifdef MASTER_BOARD
/**
  * @brief  This function send a command through SPI bus.
  * @param  command : command id.
  * @param  val : value.
  * @retval None
  */
void Command_write(uint8_t command, uint8_t val)
{
  SPI_Write(command);
  SPI_Write(val);
}

/**
  * @brief  This function send a command through SPI bus.
  * @param  command : command id.
  * @param  val : value.
  * @retval None
  */
void Command_read(uint8_t command, uint8_t *val)
{
  SPI_Write(command | READ_REGISTER);
  SYNCHRO_WAIT(300);
  __HAL_SPI_DISABLE(&SpiHandle);
  SPI_1LINE_RX(&SpiHandle);
  SYNCHRO_WAIT(300);
  SPI_Read(val);
  SYNCHRO_WAIT(300);
  SPI_1LINE_TX(&SpiHandle);
  __HAL_SPI_ENABLE(&SpiHandle);
  SYNCHRO_WAIT(300);
}
#endif

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while(1);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = RCC_PREDIV_DIV2 (2)
  *            PLLMUL                         = RCC_PLL_MUL16 (16)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* HSI Oscillator already ON after system reset, activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
