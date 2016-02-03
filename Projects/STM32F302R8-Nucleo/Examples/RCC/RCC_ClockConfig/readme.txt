/**
  @page RCC_ClockConfig RCC Clock Config example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    RCC/RCC_ClockConfig/readme.txt 
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

This example describes how to use the RCC HAL API to configure the system clock (SYSCLK) 
and modify the clock settings in run mode.

In this example, after startup SYSCLK is configured to the max frequency using the PLL with
HSI as clock source, the User push-button (connected to EXTI_Line15_10) will be 
used to change the PLL source: 
- from HSI to HSE bypass
- from HSE bypass to HSI

 @note In HSE bypass mode, input clock will come from the MCO from
       ST_LINK MCU. This frequency cannot be changed, and it is fixed
       at 8 MHz. To use MCO from ST_LINK you need to check the Board
       User Manual to know how to connect the MCO pin to the STM32 device.
        
Each time the User push-button is pressed; EXTI_Line15_10 interrupt is generated and in the ISR
the PLL oscillator source is checked using __HAL_RCC_GET_PLL_OSCSOURCE() macro:

- If the HSE bypass oscillator is selected as PLL source, the following steps will be followed to switch 
   the PLL source to HSI oscillator:
     a- Switch the system clock source to HSE bypass to allow modification of the PLL configuration
     b- Enable HSI Oscillator, select it as PLL source and finally activate the PLL
     c- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
     d- Disable the HSE bypass oscillator (optional, if the HSE bypass is no more needed by the application)


- If the HSI oscillator is selected as PLL source, the following steps will be followed to switch 
   the PLL source to HSE bypass oscillator:
     a- Switch the system clock source to HSI to allow modification of the PLL configuration
     b- Enable HSE bypass Oscillator, select it as PLL source and finally activate the PLL
     c- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
     d- Disable the HSI oscillator (optional, if the HSI is no more needed by the application)

In this example the SYSCLK  is outputted on the MCO1 pin(PA.08).
 => PA.08 connected to pin 23 on CN10 connector


LED2 is toggled with a timing defined by the HAL_Delay() API.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - RCC/RCC_ClockConfig/Inc/stm32f3xx_hal_conf.h    HAL configuration file
  - RCC/RCC_ClockConfig/Inc/stm32f3xx_it.h          Interrupt handlers header file
  - RCC/RCC_ClockConfig/Inc/main.h                  Header for main.c module  
  - RCC/RCC_ClockConfig/Src/stm32f3xx_it.c          Interrupt handlers
  - RCC/RCC_ClockConfig/Src/main.c                  Main program
  - RCC/RCC_ClockConfig/Src/system_stm32f3xx.c      STM32F3xx system source file

@par Hardware and Software environment

  - This example runs on STM32F3xx devices.
    
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
