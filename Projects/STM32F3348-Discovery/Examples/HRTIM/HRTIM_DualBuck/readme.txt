/**
  @page HRTIM HRTIM_DualBuck

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    HRTIM/HRTIM_DualBuck/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of HRTIM_DualBuck example.
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
  This example shows how to configure the HRTIM to have 2 buck converters 
  controlled by a single timer unit.
  This is done using a single timer unit (Timer D), with the TD1 and TD2 outputs
  (resp. PB14 and PB15).
  The duty cycle on TD1 is continuously varied in an interrupt service routine 
  generated on repetition event, to mimic a real converter management. A low-pass 
  filtered signal reflecting the PWM duty cycle can be monitored on TP3.
  The FAULT1 input is enabled on PA12 (active low) to demonstrate PWM shut down 
  (low level sensitive).
  When the fault is triggered (PA12 input connected to GND, TD1 signal only is
  stopped. The system can be re-armed by pressing the user button.
  LEDs are indicating the following:
  Blue LED: blinks during normal operation
  Red LED: blinks when FAULT is triggered
  Orange LED: indicates the occurrence and duration of the PWM refresh ISR

  The ADC is configured to have conversions triggered in the middle of the
  ON time of each converter (non-overlapping PWM signals), on PA4 input.
  The RC filtered PWM can be connected to PA4 for monitoring ADC conversions.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - HRTIM/HRTIM_DualBuck/Inc/stm32f3xx_hal_conf.h    HAL configuration file
  - HRTIM/HRTIM_DualBuck/Inc/stm32f3xx_it.h          PPP interrupt handlers header file
  - HRTIM/HRTIM_DualBuck/Inc/main.h                  Header for main.c module  
  - HRTIM/HRTIM_DualBuck/Src/stm32f3xx_it.c          PPP interrupt handlers
  - HRTIM/HRTIM_DualBuck/Src/main.c                  Main program
  - HRTIM/HRTIM_DualBuck/Src/stm32f3xx_hal_msp.c     HAL MSP file

@par Hardware and Software environment 

  - This example runs on STM32F334x4/STM32F334x6/STM32F334x8 devices.
    
  - This example has been tested with STM32F3348-DISCO
    board and can be easily tailored to any other supported device and development board.
  
  - STM32F3348-DISCO Set-up: PA12 must be briefly tied to ground to simulate a fault event

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
