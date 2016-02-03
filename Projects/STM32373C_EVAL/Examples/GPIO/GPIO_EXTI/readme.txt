/**
  @page GPIO_EXTI GPIO EXTI example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    GPIO/GPIO_EXTI/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the GPIO EXTI example.
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

This example shows how to configure external interrupt lines.

In this example, 4 EXTI lines (EXTI0, EXTI2, EXTI6 and EXTI10) when using the STM32373C-EVAL 
are configured  to generate an interrupt on each falling edge. 
In the interrupt routine a led connected to a specific GPIO pin is toggled.

In this example on STM32373C-EVAL:
    - EXTI0  is mapped to PA0
    - EXTI2  is mapped to PA2 
    - EXTI6  is mapped to PE6  
    - EXTI10 is mapped to PF10

After EXTI configuration,
  when rising edge is detected on EXTI0, LED1 toggles
  when falling edge is detected on EXTI2, LED4 toggles
  when rising edge is detected on EXTI6, LED2 toggles
  when rising edge is detected on EXTI10, LED3 toggles

If STM32373C-EVAL is used,
  when Tamper pushbutton is pressed, LED1 toggles
  when Joystick Sel pushbutton is pressed, LED2 toggles
  when Joystick Up pushbutton is pressed, LED3 toggles
  when Key pushbutton is pressed, LED4 toggles

In this example, EXTI0_Config() function can be substituted by 
BSP_PB_Init(BUTTON_TAMPER, Mode_EXTI) provided in the STM32373C-EVAL driver.

In this example, HCLK is configured at 72 MHz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - GPIO/GPIO_EXTI/Inc/stm32f3xx_hal_conf.h    HAL configuration file
  - GPIO/GPIO_EXTI/Inc/stm32f3xx_it.h          Interrupt handlers header file
  - GPIO/GPIO_EXTI/Inc/main.h                  Header for main.c module  
  - GPIO/GPIO_EXTI/Src/stm32f3xx_it.c          Interrupt handlers
  - GPIO/GPIO_EXTI/Src/main.c                  Main program
  - GPIO/GPIO_EXTI/Src/system_stm32f3xx.c      STM32F3xx system source file

@par Hardware and Software environment

  - This example runs on STM32F373xx devices.
    
  - This example has been tested with STM32373C-EVAL RevB board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
