/**
  ******************************************************************************
  * @file    HRTIM\HRTIM_Multiphase/Inc/main.h 
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
#include "stm32f3xx_hal.h"
#include "stm32f3348_discovery.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants ---------------------------------------------------------*/
#define MULTIPHASE_PERIOD ((uint16_t)0xA000) // 
#define PHASE_SHIFT_INIT ((uint16_t)MULTIPHASE_PERIOD / 5 )
#define DUTY_CYCLE_INIT ((uint16_t)PHASE_SHIFT_INIT / 2)

#define ADC_CONVERSION_TIME     ((uint16_t)0x480)
typedef enum {
  FIVE_PHASE_INIT, FOUR_PHASE_INIT, THREE_PHASE_INIT, TWO_PHASE_INIT, ONE_PHASE_INIT, BURST_INIT,
  FIVE_PHASE, FOUR_PHASE, THREE_PHASE, TWO_PHASE, ONE_PHASE, BURST, FAULT} DemoModeTypeDef;
        

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------- */

extern DemoModeTypeDef DemoState;
extern HRTIM_HandleTypeDef hhrtim;


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
