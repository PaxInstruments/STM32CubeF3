/**
  @page STM32F3_Discovery Demo STM32F3_Discovery Demo
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    Demonstration/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description STM32F3 Discovery Demo description.
  ******************************************************************************
  *
 <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

- Connect the STM32F3-DISCOVERY board to a PC with a 'USB type A to Mini-B' cable
through USB connector CN2 or CN1 to power the board. Then red led LD1 (PWR) and
LD2 (COM) light up.
- All 8 leds between B1 and B2 are blinking as chenillard.
- At reset when the Button B1 is Pressed more than 1 second the USB Test is executed, Othersiwse
the demo is launched.
- The USB test consist on moving the cursor in square path. The led is On corresponding to such direction.

- The following sequence describes the demo application:
	- Press User Button B1 (Button left corner of the board) then gyroscope MEMS sensor is
      enabled, move the board horizontally and observe the four Leds blinking according to the motion
      direction.
	- Then if the you Press User Button B1 (Button left corner of the board) then Accelerometer MEMS 
	  sensor is enabled, move the board and observe the four Leds blinking according to the acceleration.
	- Finally Pressing the User Button B1, enables the USB USER and convert the STM32F3-Discovery 
	  board as a standard mouse (LD3, LD6, LED7 and LED10 are ON). Connect a second USB type A/mini-B cable 
	  through the USB User connector and the PC, then move the board (horizontally and vertically)and see 
	  the mouse cursor moves according to the motion direction.
	- Pressing the Press User Button B1, to re launch the demo application.

	@par Directory contents 

  - Demonstration/stm32f3xx_hal_conf.h HAL Configuration file
  - Demonstration/stm32f3xx_it.c       		Interrupt handlers
  - Demonstration/stm32f3xx_it.h       		Header for stm32f3xx_it.c
  - Demonstration/usbd_conf.c             	General low level driver configuration
  - Demonstration/usbd_conf.h             	USB device driver Configuration file
  - Demonstration/usbd_desc.c             	USB device HID descriptor
  - Demonstration/usbd_desc.h             	USB device HID descriptor header file
  - Demonstration/main.c               		Main program
  - Demonstration/main.h               		Header for main.c
  - Demonstration/selftest.c           		MEMS feature program
  - Demonstration/selftest.c .h        		Header for selftest.c 
  - Demonstration/system_stm32f3xx.c  		STM32F3xx system source file
  - Demonstration/stm32f3xx_hal_conf.h      HAL configuration file
           
@note The "system_stm32f3xx.c" file contains the system clock configuration after reset.

@par Hardware and Software environment

  - This Demo runs on STM32F303xC devices.
  
  - This example has been tested with STMicroelectronics STM32F3-Discovery (MB1035) 
    and can be easily tailored to any other supported device and development board.

  - STM32F3-Discovery Set-up
    - None.
      
@par How to use it ? 

In order to make the program work, you must do the following :
- Open your preferred toolchain 
- Rebuild all files and load your image into target memory
- Run the example
  
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
