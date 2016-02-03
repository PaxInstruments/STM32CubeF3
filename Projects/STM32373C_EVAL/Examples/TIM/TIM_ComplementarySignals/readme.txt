/**
  @page TIM_ComplementarySignals TIM Complementary Signals example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    TIM/TIM_ComplementarySignals/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the TIM Complementary Signals example.
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

This example shows how to configure the TIM peripheral to generate three 
complementary TIM signals, to insert a defined dead time value, to use the break 
feature and to lock the desired parameters.

This is done using TIM15 peripheral.

TIM15CLK is fixed to SystemCoreClock, the TIM15 Prescaler is set to have
TIM15 counter clock = 18MHz.

The objective is to generate PWM signal at 10 KHz:
  - TIM15_Period = (SystemCoreClock / 10000) - 1

Duty cycle is computed as the following description: 
The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
The Timer pulse is calculated as follows:
  - Channel1Pulse = DutyCycle * (TIM15_Period - 1) / 100

A dead time equal to 100/SystemCoreClock (arround 1.4us) is inserted between 
the different complementary signals, and the Lock level 1 is selected.
The break Polarity is used at High level.

The TIM15 waveforms can be displayed using an oscilloscope.



@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - TIM/TIM_ComplementarySignals/Src/main.c                 Main program
  - TIM/TIM_ComplementarySignals/Src/system_stm32f3xx.c     STM32F3xx system clock configuration file
  - TIM/TIM_ComplementarySignals/Src/stm32f3xx_it.c         Interrupt handlers 
  - TIM/TIM_ComplementarySignals/Src/stm32f3xx_hal_msp.c    HAL MSP module
  - TIM/TIM_ComplementarySignals/Inc/main.h                 Main program header file  
  - TIM/TIM_ComplementarySignals/Inc/stm32f3xx_hal_conf.h   HAL Configuration file
  - TIM/TIM_ComplementarySignals/Inc/stm32f3xx_it.h         Interrupt handlers header file

        
@par Hardware and Software environment  

  - This example runs on STM32F373xC devices.
    
  - This example has been tested with STMicroelectronics STM32373C-EVAL RevB
    boards and can be easily tailored to any other supported device 
    and development board.

  - STM32373C-EVAL RevB Set-up
    - Connect the TIM15 pins to an oscilloscope to monitor the different waveforms:
      - TIM15_CH1  pin (PA.02)  
      - TIM15_CH1N pin (PA.01)  

    - Connect the TIM15 break pin TIM15_BKIN pin (PA.09) to the GND. To generate a 
      break event, switch this pin level from 0V to 3.3V.  


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
