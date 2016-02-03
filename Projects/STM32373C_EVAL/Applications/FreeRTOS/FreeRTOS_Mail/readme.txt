/**
  @page FreeRTOS_Queues FreeRTOS Mail example
 
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    FreeRTOS/FreeRTOS_Mail/readme.txt
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    13-November-2015
  * @brief   Description of the FreeRTOS Mail example.
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Description

This application shows how to use mail queues with CMSIS RTOS API.

This example creates two threads that send and receive mail
the mail to send/receive is a structure that holds three variables (var1 and var2 are uint32, var3 is a uint8)

One thread acts as a producer and the other as the consumer.  
The consumer is a higher priority than the producer and is set to block on mail receiving.

The Mail queue has space for one item. The producer allocates the mail and put it on the mail queue. 
As soon as the producer posts a mail on the queue the consumer will unblock, preempt the producer, 
get the mail and free it.  

Add the following variables to LiveWatch, the three producer values must respectively remain equals to the three consumer values all the time:
 - ConsumerValue1 must remain equal to ProducerValue1
 - ConsumerValue2 must remain equal to ProducerValue2
 - ConsumerValue3 must remain equal to ProducerValue3
  
LEDs can be used to monitor the example status:
  - LED1 should toggle when the example runs successfully.
  - LED3 is ON when any error occurs.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications 
on STM32Cube with RTOS".


@par Directory contents
    - FreeRTOS/FreeRTOS_Mail/Src/main.c                Main program
    - FreeRTOS/FreeRTOS_Mail/Src/stm32f3xx_it.c        Interrupt handlers
    - FreeRTOS/FreeRTOS_Mail/Src/system_stm32f3xx.c    STM32F3xx system clock configuration file
    - FreeRTOS/FreeRTOS_Mail/Inc/main.h                Main program header file
    - FreeRTOS/FreeRTOS_Mail/Inc/stm32f3xx_hal_conf.h  HAL Library Configuration file
    - FreeRTOS/FreeRTOS_Mail/Inc/stm32f3xx_it.h        Interrupt handlers header file
    - FreeRTOS/FreeRTOS_Mail/Inc/FreeRTOSConfig.h      FreeRTOS Configuration file

@par Hardware and Software environment

  - This example runs on STM32F373xC devices.
    
  - This example has been tested with STM32373C-EVAL RevB board and can be
    easily tailored to any other supported device and development board. 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
