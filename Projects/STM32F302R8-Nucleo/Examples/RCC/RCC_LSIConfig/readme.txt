/**
  @page RCC_LSIConfig RCC Clock Config example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    RCC/RCC_LSIConfig/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the RCC Clock Config example.
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

This example describes how to use the RCC HAL API to enable or disable the
low-speed internal (LSI) RC oscillator (about 40 KHz) at run time.

Board: STM32F302R8-Nucleo Rev C (embeds a STM32F302R8T6 device)
Microcontroller Clock Output MCO Pin:PA.08

   _________________________                   _______________________ 
  |           ______________|                 |  _______________      |
  |          |RCC           |                 | |               | O   |
  |          |              |                 | |   _   _   _   | O   |
  |          |          MCO |_________________| | _| |_| |_| |_ | --  |
  |          |              |                 | |_______________| --  |    
  |          |              |                 |                       |
  |          |              |                 |_oscilloscope__________|
  |          |              |                    
  |          |              | 
  |          |______________|  
  |                         |
  |                         |
  |_STM32_Board ____________|



In this example, after startup SYSCLK is configured to the max frequency using the PLL with
HSI as clock source, the User push-button (connected to EXTI_Line15_10)
is used to enable/disable LSI:
each time the User push-button is pressed, EXTI_Line15_10 interrupt is generated and the ISR
enables the LSI when it is off, disables it when it is on.

LED_GREEN is toggling as follows according to LSI activation:
- when LSI is on, LED_GREEN is emitting a double flash every half-second
- when LSI is off, LED_GREEN is fast-toggling (every 100 ms) 

LSI clock waveform is available on the MCO pin PA.08 and can be captured
on an oscilloscope.

In case of configuration error, LED_GREEN is slowly toggling (1 sec. period).

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - RCC/RCC_LSIConfig/Inc/stm32f3xx_hal_conf.h    HAL configuration file
  - RCC/RCC_LSIConfig/Inc/stm32f3xx_it.h          Interrupt handlers header file
  - RCC/RCC_LSIConfig/Inc/main.h                  Header for main.c module  
  - RCC/RCC_LSIConfig/Src/stm32f3xx_it.c          Interrupt handlers
  - RCC/RCC_LSIConfig/Src/main.c                  Main program
  - RCC/RCC_LSIConfig/Src/system_stm32f3xx.c      STM32F3xx system source file

@par Hardware and Software environment

  - This example runs on STM32F302x8 device.
    
  - This example has been tested with STM32F302R8-Nucleo Rev C 
    board and can be easily tailored to any other supported device
    and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
