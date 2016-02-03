/**
  @page UART_TwoBoards_ComPolling UART TwoBoards Communication Polling example

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    UART/UART_TwoBoards_ComPolling/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the UART Two Boards Communication Polling example.
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

This example describes a UART transmission (transmit/receive) in polling mode
between two boards.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 72 MHz.

Then 1st board is waiting for user button key to be pressed. Once done, data 
are transmitted through USART1 in polling mode. 2nd board has configured USART1 
to receive data in polling mode. Once data received is completed, 2nd board also 
transmit same characters on USART1 which will be received by 1st board.
Both boards compare transmitted datas to received ones. If they are same, LED3
 is turn on, else LED6 is turn On

Warning: As both boards do not behave same way, "TRANSMITTER_BOARD" switch 
compilation exists to determine either software is for 1st transmitter board or 
2nd receiver (then transmitter) board. In other words, 1st board has to be 
flashed with software compiled with switch enable, 2nd board has to be flashed 
with software compiled with switch disable.

STM32 discovery board's LEDs can be used to monitor the transfer status:
 - LED3 is ON when the transmission process is complete.
 - LED4 is ON when the reception process is complete.
 - LED5 is ON when there's UART error callback.   
 - LED6 is ON when there is an error in transmission/reception process.  

The UART is configured as follows:
    - BaudRate = 9600 baud  
    - Word Length = 8 Bits (7 data bit + 1 parity bit)
    - One Stop Bit
    - None parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Reception and transmission are enabled in the time

@note USARTx/UARTx instance used and associated resources can be updated in "main.h"
file depending hardware configuration used.

@note When the parity is enabled, the computed parity is inserted at the MSB
position of the transmitted data.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - UART/UART_TwoBoards_ComPolling/Inc/stm32f3xx_hal_conf.h    HAL configuration file
  - UART/UART_TwoBoards_ComPolling/Inc/stm32f3xx_it.h          interrupt handlers header file
  - UART/UART_TwoBoards_ComPolling/Inc/main.h                  Header for main.c module  
  - UART/UART_TwoBoards_ComPolling/Src/stm32f3xx_it.c          interrupt handlers
  - UART/UART_TwoBoards_ComPolling/Src/main.c                  Main program
  - UART/UART_TwoBoards_ComPolling/Src/stm32f3xx_hal_msp.c     HAL MSP module
  - UART/UART_TwoBoards_ComPolling/Src/system_stm32f3xx      STM32F3xx system source file


@par Hardware and Software environment 

  - This example runs on STM32F303xC devices.    
  - This example has been tested with STM32F3-Discovery 
    boards and can be easily tailored to any other supported device 
    and development board.
    
  - STM32F3-Discovery set-up
    - Connect a wire between 1st board PC.04 pin (Uart Tx) to 2nd board PC.05 pin (Uart Rx)
    - Connect a wire between 1st board PC.05 pin (Uart Rx) to 2nd board PC.04 pin (Uart Tx)
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
