/**
  @page FLASH_EraseProgram FLASH Erase and Program example
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    FLASH/FLASH_EraseProgram/readme.txt
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the FLASH Erase and Program example.
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

This example describes how to configure and use the FLASH HAL API to erase and program 
the internal FLASH memory.
  
At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock (SYSCLK) 
to run at 72 MHz. 

After Reset, the Flash memory Program/Erase Controller is locked. A dedicated function
is used to enable the FLASH control register access.
Before programming the desired addresses, an erase operation is performed using 
the flash erase page feature. The erase procedure is done by filling the erase init 
structure giving the starting erase page and the number of pages to erase.
At this stage, all these pages will be erased one by one separately.

@note: if problem occurs on a page, erase will be stopped and faulty page will 
be returned to user (through variable 'pageError').

Once this operation is finished, page word programming operation will be performed 
in the FLASH memory. The written data is then read back and checked.

The STM32303C-EVAL RevC board LEDs can be used to monitor the transfer status:
 - LED1 is ON when there are no errors detected after data programing 
 - LED2 is ON when there are errors detected after data programing 
 - LED3 is ON when there is an issue during erase or program procedure

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - FLASH/FLASH_EraseProgram/Inc/stm32f3xx_hal_conf.h        Library Configuration file  
  - FLASH/FLASH_EraseProgram/Inc/stm32f3xx_it.h              Header for stm32f3xx_it.c
  - FLASH/FLASH_EraseProgram/Inc/main.h                      Header for main.c module 
  - FLASH/FLASH_EraseProgram/Src/stm32f3xx_it.c              Interrupt handlers
  - FLASH/FLASH_EraseProgram/Src/main.c                      Main program
  - FLASH/FLASH_EraseProgram/Src/system_stm32f3xx.c          STM32F3xx system clock configuration file

@par Hardware and Software environment

  - This example runs on STM32F303xC devices.
    
  - This example has been tested with STM32303C-EVAL RevC board and can be
    easily tailored to any other supported device and development board.
      
@par How to use it ? 

In order to make the program work, you must do the following:
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
