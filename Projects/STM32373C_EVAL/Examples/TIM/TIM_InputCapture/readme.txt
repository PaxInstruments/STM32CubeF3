/**
  @page TIM_InputCapture Input Capture example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    TIM/TIM_InputCapture/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the TIM_InputCapture example.
  ******************************************************************************
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
  @endverbatim

@par Example Description

  This example shows how to use the TIM peripheral to measure the frequency of
  an external signal.

  The TIM4CLK frequency is set to SystemCoreClock (Hz), the Prescaler is 0,
  so the TIM4 counter clock is SystemCoreClock (Hz).
  SystemCoreClock is set to 72MHz for STM32F3xx Devices.

  TIM4 is configured in Input Capture Mode: the external signal is connected to 
  TIM4 Channel2 used as input pin.
  To measure the frequency we use the TIM4 CC2 interrupt request, so in the 
  TIM4_CC_IRQHandler routine, the frequency of the external signal is computed.

  The "uwFrequency" variable contains the external signal frequency:
  uwFrequency = TIM4 counter clock / uwDiffCapture (Hz),
  where "uwDiffCapture" is the difference between two consecutive TIM4 captures.


  The minimum frequency value to measure is TIM4 counter clock / CCR MAX
                                              = 72MHz / 65535
                                              = 1099 Hz
  Due to TIM4_CC_IRQHandler processing time (arround 3.50us), the maximum
  frequency value to measure is arround 300kHz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - TIM/TIM_InputCapture/Src/main.c                 Main program
  - TIM/TIM_InputCapture/Src/system_stm32f3xx.c     STM32F3xx system clock configuration file
  - TIM/TIM_InputCapture/Src/stm32f3xx_it.c         Interrupt handlers 
  - TIM/TIM_InputCapture/Src/stm32f3xx_hal_msp.c    HAL MSP module
  - TIM/TIM_InputCapture/Inc/main.h                 Main program header file  
  - TIM/TIM_InputCapture/Inc/stm32f3xx_hal_conf.h   HAL Configuration file
  - TIM/TIM_InputCapture/Inc/stm32f3xx_it.h         Interrupt handlers header file

        
@par Hardware and Software environment  

  - This example runs on STM32F373xC devices.
    
  - This example has been tested with STMicroelectronics STM32373C-EVAL RevB
    boards and can be easily tailored to any other supported device 
    and development board.

  - STM32373C-EVAL RevB Set-up
    - Connect the external signal to measure to the TIM4 CH2 pin (PB.07).

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
