/**
  ******************************************************************************
  * @file    SPI/SPI_FullDuplex_ComDMA/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_nucleo.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor SPIx instance used and associated 
   resources */
/* Definition for SPIx clock resources */
#define SPIx                             SPI3
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI3_CLK_ENABLE()
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE() 
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE() 

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI3_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI3_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_10
#define SPIx_SCK_GPIO_PORT               GPIOC
#define SPIx_SCK_AF                      GPIO_AF6_SPI3
#define SPIx_MISO_PIN                    GPIO_PIN_11
#define SPIx_MISO_GPIO_PORT              GPIOC
#define SPIx_MISO_AF                     GPIO_AF6_SPI3
#define SPIx_MOSI_PIN                    GPIO_PIN_12
#define SPIx_MOSI_GPIO_PORT              GPIOC
#define SPIx_MOSI_AF                     GPIO_AF6_SPI3

/* Definition for SPIx's DMA */
#define SPIx_TX_DMA_CHANNEL              DMA1_Channel3
#define SPIx_DMA_TX_IRQn                 DMA1_Channel3_IRQn
#define SPIx_RX_DMA_CHANNEL              DMA1_Channel2
#define SPIx_DMA_RX_IRQn                 DMA1_Channel2_IRQn

/* Definition for SPIx's NVIC */
#define SPIx_DMA_TX_IRQHandler           DMA1_Channel3_IRQHandler
#define SPIx_DMA_RX_IRQHandler           DMA1_Channel2_IRQHandler

/* Size of buffer */
#define BUFFERSIZE                       (COUNTOF(aTxBuffer) - 1)

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
