/**
  ******************************************************************************
  * @file    CEC/CEC_MultiAddress/Src/main.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   This example describes how to configure and use the CEC through 
  *          the STM32F3xx HAL API.
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

/** @addtogroup CEC_MultiAddress
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t  Tab_Rx[CEC_MAX_PAYLOAD];   /* Received data buffer. Max size = 16 bytes
                                     * header + opcode followed by up to 14 operands */
uint8_t  Tab_Tx[CEC_MAX_PAYLOAD-1]; /* Transmitted data buffer. 
                                     * header is not included in Tab_Tx.
                                     *  Max size = 15 bytes.                                   
                                     *  one opcode followed by up to 14 operands.
                                     *  When payload size = 0, only the header is sent
                                     *  (ping operation) */                                   
uint8_t ReceivedFrame       = 0x0;  /* Set when a reception occurs */
uint16_t NbOfReceivedBytes  = 0x0;  /* Number of received bytes in addition to the header. 
                                     * when a ping message has been received (header 
                                     * only), NbOfReceivedBytes = 0 */
uint8_t StartSending        = 0x0;  /* Set when a transmission is triggered by the user */
uint32_t TxSize             = 0x0;  /* Number of bytes to transmit in addition to the header. 
                                     * In case of ping operation (only the header sent),
                                     * TxSize = 0 */
uint8_t MyLogicalAddress1   = 0x0;  /* Transmitter logical address 1 */
uint8_t MyLogicalAddress2   = 0x0;  /* Transmitter logical address 2 (if applicable) */ 
uint8_t MyFollowerAddress1  = 0x0;  /* Destination logical address 1 */
uint8_t MyFollowerAddress2  = 0x0;  /* Destination logical address 2 (if applicable) */
uint8_t DestinationAddress  = 0x0;  /* Destination logical address, set on the
                                     * fly based on the button pushed by the user */
                           
CEC_HandleTypeDef hcec;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void CEC_Config(CEC_HandleTypeDef *hcec);
static void CEC_FlushRxBuffer(void);
static void EXTILine0_Config(void);
static void EXTILine2_TSC_Config(void);
static void EXTILine9_5_Config(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
 /* This sample code shows how to use STM32F3xx CEC HAL API to transmit and 
  * receive data. The device is set in waiting to receive mode and sends
  * messages when the evaluation board buttons are pushed by the user */
  
  /* STM32F3xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();
  /* Configure the system clock to 72 MHz */
  SystemClock_Config();

  /* LED and button-triggered interruptions initialization */

  /* -1- Initialize LEDs mounted on EVAL board */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  
  /* -2- Configure EXTI Line0 (connected to PA0 pin) in Interrupt mode */
  /* Do basically the same as BSP_PB_Init(BUTTON_TAMPER, BUTTON_MODE_EXTI); */
  EXTILine0_Config();
  
  /* -3- Configure EXTI Line2 (connected to PA2 pin) in interrupt mode */
  /* Do basically the same as BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI); */
  EXTILine2_TSC_Config();

  /* -4- Configure EXTI Line9-5 (connected to PE6 pin) in interrupt mode */
  /* Do basically the same as BSP_PB_Init(BUTTON_SEL, BUTTON_MODE_EXTI); */
  EXTILine9_5_Config();

  
  /* CEC device initialization */
    
  /* -5- CEC configuration (transfer will take place in Interrupt mode) */
  
#if defined (DEVICE_1)
  /* Device 1: 
   * a single logical address ... */
  MyLogicalAddress1 = DEVICE_ADDRESS_1;
  /* ... and two different follower addresses */
  MyFollowerAddress1 = DEVICE_ADDRESS_2;
  MyFollowerAddress2 = DEVICE_ADDRESS_3;
#elif defined (DEVICE_2)
  /* Device 2: 
   * two different logical addresses ... */
  MyLogicalAddress1 = DEVICE_ADDRESS_2;
  MyLogicalAddress2 = DEVICE_ADDRESS_3;  
  /* ... and a single follower address */
  MyFollowerAddress1 = DEVICE_ADDRESS_1;
#endif /* DEVICE_1 */  
  
  hcec.Instance = CEC;
  /* Deinitialize CEC to reinitialize from scratch */
  HAL_CEC_DeInit(&hcec);
  /* IP configuration */ 
  CEC_Config(&hcec);


  /* -6- CEC transfer general variables initialization */
  ReceivedFrame = 0;
  StartSending = 0;
  NbOfReceivedBytes = 0;
  CEC_FlushRxBuffer();
  
  
  /* Test start */
  
  /* Enter infinite reception loop: the CEC device is set in
   * waiting to receive mode. 
   * The CEC "background" state is HAL_CEC_STATE_STANDBY_RX.
   * Upon any message reception or transmission, the CEC 
   * comes back to that state.
   * It is up to the user to define exit conditions in modifying
   * accordingly the RX, TX or Error callback functions. */
  HAL_CEC_Receive_IT(&hcec, (uint8_t *)&Tab_Rx); 
  while (HAL_CEC_GetState(&hcec) != HAL_CEC_STATE_READY)
  {
    
    /* if no reception has occurred and no error has been detected,
     * transmit a message if the user has pushed a button */
    if( (StartSending == 1) && (ReceivedFrame == 0))
    { 
      HAL_CEC_Transmit_IT(&hcec, DestinationAddress, (uint8_t *)&Tab_Tx, TxSize);
      /* loop until TX ends or TX error reported */
        while (HAL_CEC_GetState(&hcec) != HAL_CEC_STATE_STANDBY_RX);
      StartSending = 0;
    }  
    
    /* if a frame has been received without error */
    if (ReceivedFrame == 1)
    { 
      /* Test on the Destination Logical Address
       * (code applicable whatever the device):
       * if Receiver has address 0x01 */ 
      if ((Tab_Rx[0]&0x0F) == 0x01) 
      {
        /* Turn on LED1 */
        BSP_LED_On(LED1);
        /* Turn on LED4 */
        BSP_LED_On(LED4);
        /* Turn off LED3 */
        BSP_LED_Off(LED3);
      }
      /* if Receiver has address 0x03 */ 
      else if ((Tab_Rx[0]&0x0F) == 0x03) 
      {
        /* Turn on LED1 */
        BSP_LED_On(LED1);
        /* Turn off LED4 */
        BSP_LED_Off(LED4);
        /* Turn off LED3 */
        BSP_LED_Off(LED3);
      }
      /* if Receiver has address 0x05 */
      else if ((Tab_Rx[0]&0x0F) == 0x05) 
      {
        /* Turn on LED4 */
        BSP_LED_On(LED4);
        /* Turn off LED1 */
        BSP_LED_Off(LED1);
         /* Turn off LED3 */
        BSP_LED_Off(LED3);
      }
      /* if Broadcast message */
      else if ((Tab_Rx[0]&0x0F) == 0x0F) 
      {
        /* Turn off all LEDs */
        BSP_LED_Off(LED1);
        BSP_LED_Off(LED2);
        BSP_LED_Off(LED3);
        BSP_LED_Off(LED4);        
      }
      ReceivedFrame = 0;
    }
    else if (ReceivedFrame == 2) /* means CEC error detected */
    { 
      /* Turn on LED3 */
      BSP_LED_On(LED3);
      ReceivedFrame = 0;
    }
  }  /*  while (HAL_CEC_GetState(&hcec) != HAL_CEC_STATE_READY) */
  
  return 0;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV                     = 1
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
#ifdef USE_FULL_ASSERT
  uint32_t ret = HAL_OK;
#endif /* USE_FULL_ASSERT */
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  
#ifdef USE_FULL_ASSERT
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    assert_failed((uint8_t *)__FILE__, __LINE__);
  }
#else
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
#endif /* USE_FULL_ASSERT */
    	
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

#ifdef USE_FULL_ASSERT
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
  if(ret != HAL_OK)
  {
    assert_failed((uint8_t *)__FILE__, __LINE__);
  }
#else
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
#endif /* USE_FULL_ASSERT */
}



/**
  * @brief  Configures the CEC peripheral.
  * @param  None
  * @retval None
  */
static void CEC_Config(CEC_HandleTypeDef *hcec)
{
  /* CEC configuration parameters */ 
  
  /* Whatever the device, set MyLogicalAddress1 as Initiator address */    
  hcec->Init.InitiatorAddress          = MyLogicalAddress1;

  hcec->Init.SignalFreeTime            = CEC_DEFAULT_SFT;
  hcec->Init.Tolerance                 = CEC_STANDARD_TOLERANCE;
  hcec->Init.BRERxStop                 = CEC_NO_RX_STOP_ON_BRE;
  hcec->Init.BREErrorBitGen            = CEC_BRE_ERRORBIT_NO_GENERATION;
  hcec->Init.LBPEErrorBitGen           = CEC_LBPE_ERRORBIT_NO_GENERATION;
  hcec->Init.BroadcastMsgNoErrorBitGen = CEC_BROADCASTERROR_NO_ERRORBIT_GENERATION;
  hcec->Init.SignalFreeTimeOption      = CEC_SFT_START_ON_TXSOM;
#if defined (DEVICE_1)
  hcec->Init.OwnAddress                = (0x1<<MyLogicalAddress1);
#elif defined (DEVICE_2)
  hcec->Init.OwnAddress                = (0x1<<MyLogicalAddress1) | (0x1<<MyLogicalAddress2);
#endif    
  hcec->Init.ListenMode                =  CEC_FULL_LISTENING_MODE;
  
  HAL_CEC_Init(hcec);
}



/**
  * @brief Tx Transfer completed callback
  * @param hcec: CEC handle
  * @retval None
  */
void HAL_CEC_TxCpltCallback(CEC_HandleTypeDef *hcec)
{
  /* after transmission, return to stand-by mode */
  hcec->State = HAL_CEC_STATE_STANDBY_RX;
}


/**
  * @brief Rx Transfer completed callback
  * @param hcec: CEC handle
  * @retval None
  */
void HAL_CEC_RxCpltCallback(CEC_HandleTypeDef *hcec)
{
    ReceivedFrame = 1;
    /* Reminder: hcec->RxXferSize is the sum of opcodes + operands 
     * (0 to 14 operands max).
     * If only a header is received, hcec->RxXferSize = 0 */   
    NbOfReceivedBytes = hcec->RxXferSize;
    hcec->RxXferSize = 0;
    hcec->pRxBuffPtr = Tab_Rx;
    hcec->ErrorCode = HAL_CEC_ERROR_NONE;
    /* return to stand-by mode */
    hcec->State = HAL_CEC_STATE_STANDBY_RX;
}

/**
  * @brief CEC error callbacks
  * @param hcec: CEC handle
  * @retval None
  */
void HAL_CEC_ErrorCallback(CEC_HandleTypeDef *hcec)
{
  ReceivedFrame = 2;

  hcec->RxXferSize = 0;
  hcec->pRxBuffPtr = Tab_Rx;
  hcec->ErrorCode = HAL_CEC_ERROR_NONE;
  hcec->State = HAL_CEC_STATE_STANDBY_RX;
}




/**
  * @brief  Reset CEC reception buffer
  * @param  None
  * @retval None
  */
static void CEC_FlushRxBuffer(void)
{
  uint32_t cpt;
  
  for (cpt = CEC_MAX_PAYLOAD; cpt > 0; cpt--)
  {
    Tab_Rx[cpt-1] = 0;
  }
}


/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  /* Configure User Button, connected to PA0 IOs in External Interrupt Mode with Falling edge trigger detection. */
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line2_TS Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
  * @brief  Configures EXTI Line2_TS (connected to PA2 pin) in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine2_TSC_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  /* Configure User Button, connected to PA2 IOs in External Interrupt Mode with Falling edge trigger detection. */
  GPIO_InitStructure.Pin = GPIO_PIN_2;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line2_TSC Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);
}

/**
  * @brief  Configures EXTI Line9_5 (connected to PE6 pin) in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine9_5_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOE clock */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  
 /* Configure Joystick SEL Button, connected to PE6 IOs in External Interrupt Mode with Rising edge trigger detection. */
  GPIO_InitStructure.Pin = GPIO_PIN_6;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* Enable and set EXTI15_10 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}


/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == TAMPER_BUTTON_PIN)
  {
    /* Toggle Green LED1 */
    BSP_LED_Toggle(LED1);
    DestinationAddress = MyFollowerAddress1;
    TxSize    = 0x0; /* no payload, ping only */
    StartSending = 1;
  }
  if(GPIO_Pin == KEY_BUTTON_PIN)
  {
    /* Toggle Green LED4 */
    BSP_LED_Toggle(LED4);
#if defined (DEVICE_1)
  DestinationAddress = MyFollowerAddress2;
#elif defined (DEVICE_2)
    DestinationAddress = MyFollowerAddress1;
#endif /* DEVICE_1 */     
    TxSize    = 0x0; /* no payload, ping only */
    StartSending = 1;
  }
  if(GPIO_Pin == SEL_JOY_PIN)
  {
    /* Toggle Green LED2 */
    BSP_LED_Toggle(LED2);
    DestinationAddress = 0xF;  /* broadcast message indicator */
    TxSize    = 0x0;           /* no payload, ping only */
    StartSending = 1;
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
