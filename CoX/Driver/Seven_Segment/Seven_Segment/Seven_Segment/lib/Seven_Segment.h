//*****************************************************************************
//
//! \file Seven_Segment.h
//! \brief Prototypes for the seven segment digital tubes Driver.
//! \version V2.1.1.0
//! \date 7/16/2012
//! \author CooCox
//! \copy
//!
//! Copyright (c)  2011, CooCox 
//! All rights reserved.
//! 
//! Redistribution and use in source and binary forms, with or without 
//! modification, are permitted provided that the following conditions 
//! are met: 
//! 
//!     * Redistributions of source code must retain the above copyright 
//! notice, this list of conditions and the following disclaimer. 
//!     * Redistributions in binary form must reproduce the above copyright
//! notice, this list of conditions and the following disclaimer in the
//! documentation and/or other materials provided with the distribution. 
//!     * Neither the name of the <ORGANIZATION> nor the names of its 
//! contributors may be used to endorse or promote products derived 
//! from this software without specific prior written permission. 
//! 
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//! ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
//! LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//! INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//! CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//! ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
//! THE POSSIBILITY OF SUCH DAMAGE.
//!
//*****************************************************************************
#ifndef __IO_seven_segment_H
#define __IO_seven_segment_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//         +-----------------------------------------------------------+  \n
//	        +   A  B     C  D
//	        +  _|__|__|__|__|_    _________   _________   ________ 
//pin_a A       +   |  _______    |  |        |  |        |  |	      |
//pin_b B       +   | |	  A   |   |  |        |  |	  |  |	      |
//pin_c C       +   | |F      |B  |  |        |  |	  |  |	      |
//pin_d D	+   | |_______|   |  |        |  |	  |  |	      |
//pin_e E	+   | |   G   |   |  |        |  |        |  |	      |
//pin_f F	+   | |E      |C  |  |        |  |	  |  |	      |
//pin_g G	+   | |_______|.H |  |        |  |        |  |	      |
//pin_h H	+   |	   D      |  |        |  |        |  |        |
//pin_com0 Com0 +   |_____________|  |________|  |________|  |________|
//pin_com1 Com1 +    |  |  |   |  |  |           | 	     |
//pin_com2 Com2 +    E  F COM3 G  H  COM2        COM1	     COM0		
//pin_com3 Com3 +
//	   +-----------------------------------------------------------+  \n
//					\n			 
//
// -A-H 	: 	 The seven_segment working pins
// 
// -COM0-COM3 :	Pins control seven_segment to be work 	 
//*****************************************************************************


#define SEVEN_SEGMENT_OPEN      1
#define SEVEN_SEGMENT_CLOSE     0

#define HEXADECIMAL             1
#define DECIMAL                 0

#define LED_ONE                 0
#define LED_TWO                 1
#define LED_THREE               2
#define LED_FOUR                3
#define LED_ALL                 4           

#define LEDn                    8
#define CHIP_SEL_NUM            4 
//
// Seven_Segment 
//
#define LED_A_GPIO_PIN          xGPIO_PIN_8
#define LED_A_GPIO_PORT         GPIOE_BASE 
#define LED_B_GPIO_PIN          xGPIO_PIN_9
#define LED_B_GPIO_PORT         GPIOE_BASE
#define LED_C_GPIO_PIN          xGPIO_PIN_10
#define LED_C_GPIO_PORT         GPIOE_BASE
#define LED_D_GPIO_PIN          xGPIO_PIN_11
#define LED_D_GPIO_PORT         GPIOE_BASE
#define LED_E_GPIO_PIN          xGPIO_PIN_12
#define LED_E_GPIO_PORT         GPIOE_BASE
#define LED_F_GPIO_PIN          xGPIO_PIN_13
#define LED_F_GPIO_PORT         GPIOE_BASE
#define LED_G_GPIO_PIN          xGPIO_PIN_14
#define LED_G_GPIO_PORT         GPIOE_BASE
#define LED_DP_GPIO_PIN         xGPIO_PIN_15
#define LED_DP_GPIO_PORT        GPIOE_BASE
  
#define CHIP_SEL_1_GPIO_PIN     xGPIO_PIN_2
#define CHIP_SEL_1_GPIO_PORT    GPIOC_BASE
#define CHIP_SEL_2_GPIO_PIN     xGPIO_PIN_3
#define CHIP_SEL_2_GPIO_PORT    GPIOC_BASE
#define CHIP_SEL_3_GPIO_PIN     xGPIO_PIN_5
#define CHIP_SEL_3_GPIO_PORT    GPIOC_BASE
#define CHIP_SEL_4_GPIO_PIN     xGPIO_PIN_7
#define CHIP_SEL_4_GPIO_PORT    GPIOC_BASE
  
extern void SevenSegmentInit (void);
extern void SevenSegmentClear (void);
extern void SevenLEDOff(void);
extern void LEDChipSel(unsigned short usLED);
extern xtBoolean SevenSegmentShow (unsigned short usLED, unsigned char ucData);
extern xtBoolean SevenSegmentScan(unsigned long ulData, unsigned char ucForm);
 
#endif //__IO_seven_segment_H