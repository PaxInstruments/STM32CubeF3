/**
  @page ADC_DifferentialMode ADC conversion of 2 channels in differential mode, voltage input from DAC, user control by push button and LED

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    ADC/ADC_DifferentialMode/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the ADC conversion example
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

This example provides a short description of how to use ADC peripherals to
perform a conversion in differential mode, between 2 ADC channels.


ADC settings:
  Continuous mode to have conversions kept running after 1st conversion trig.
  Software start to trig the 1st conversion manually, without external event.
  Channel in differential mode.

ADC conversion results:
  ADC conversions results are transfered automatically by ADC IRQ handler, through
  function HAL_ADC_ConvCpltCallback(), into variable "uhADCxConvertedValue".

  ADC Differential conversion result calculation:                       
   - An offset of half of full range is added to keep the full dynamic range of differential voltage.                                     
   - Channels voltage is divided by 2, resolution is lowered of 1 bit.  
   => Diff conversion result = mid-range + (channel_high-channel_low)/2                

Board settings:
  The voltage input on ADC channels is provided from DAC channels.
  ADC and DAC channels have been chosen to have the same pads shared at device level: PA4 and PA5.
  Therefore, there is no external connection needed to run this example.

  Voltage on ADC channels input is changed by pressing on push button:
  Voltage is increasing at each click on push button, from 0 to maximum range in 4 steps.
  Click on push button are circular cycles: At counter maximum value reached, counter is set back to 0.

  ADC differential high input is kept at a constant voltage level.


STM32 board's LEDs are be used to monitor the transfer status:
 - Normal operation: LED2 is turned-on/off in function of ADC conversion result.
    - Turned-on if differential voltage is positive
    - Turned-off if differential voltage is negative

 - Error: In case of error, LED3 is toggling at a frequency of 1Hz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - ADC/ADC_DifferentialMode/Inc/stm32f3xx_hal_conf.h    HAL configuration file
  - ADC/ADC_DifferentialMode/Inc/stm32f3xx_it.h          DMA interrupt handlers header file
  - ADC/ADC_DifferentialMode/Inc/main.h                  Header for main.c module  
  - ADC/ADC_DifferentialMode/Src/stm32f3xx_it.c          DMA interrupt handlers
  - ADC/ADC_DifferentialMode/Src/main.c                  Main program
  - ADC/ADC_DifferentialMode/Src/stm32f3xx_hal_msp.c     HAL MSP file
  - ADC/ADC_DifferentialMode/Src/system_stm32f3xx.c      stm32f3xx system source file

@par Hardware and Software environment 
  - This example runs on STM32F303xE devices.
    
  - This example has been tested with STM32303E-EVAL RevC board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
