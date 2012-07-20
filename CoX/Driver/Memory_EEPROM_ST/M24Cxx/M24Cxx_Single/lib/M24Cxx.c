//*****************************************************************************
//
//! \file M24Cxx.c
//! \brief the M24Cxx Driver.
//! \version V2.1.1.0
//! \date 6/1/2012
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
//*****************************************************************************
#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xi2c.h"
#include "xhw_i2c.h"
#include "xgpio.h"
#include "M24Cxx.h"
#include "hw_M24Cxx.h"

#if (M24Cxx_Device == M24C01)
#define M24Cxx_PAGESIZE         M24C01_PAGE_SIZE 
#define M24Cxx_SIZE             M24C01_SIZE

#elif (M24Cxx_Device == M24C02)
#define M24Cxx_PAGESIZE         M24C02_PAGE_SIZE 
#define M24Cxx_SIZE             M24C02_SIZE

#elif (M24Cxx_Device == M24C04)
#define M24Cxx_PAGESIZE         M24C04_PAGE_SIZE 
#define M24Cxx_SIZE             M24C04_SIZE

#elif (M24Cxx_Device == M24C08)
#define M24Cxx_PAGESIZE         M24C08_PAGE_SIZE 
#define M24Cxx_SIZE             M24C08_SIZE

#elif (M24Cxx_Device == M24C16)
#define M24Cxx_PAGESIZE         M24C16_PAGE_SIZE 
#define M24Cxx_SIZE             M24C16_SIZE

#elif (M24Cxx_Device == M24C32)
#define M24Cxx_PAGESIZE         M24C32_PAGE_SIZE 
#define M24Cxx_SIZE             M24C32_SIZE

#elif (M24Cxx_Device == M24C64)
#define M24Cxx_PAGESIZE         M24C64_PAGE_SIZE
#define M24Cxx_SIZE             M24C64_SIZE

#endif

#define I2C_Speed               400000

                                           
//*****************************************************************************
//
//! \brief Initialize M24Cxx and I2C  
//!
//! \param None
//!
//! This function initialize the mcu I2C as master and specified I2C port.the 
//! master block will be set up to transfer data at 400 kbps.
//! 
//! \return None.
//
//*****************************************************************************
void M24CxxInit(void)
{
    //
    // Enable GPIO Periph clock and Alternate Fuction I/O clock.
    //  
    xSysCtlPeripheralEnable(M24Cxx_I2C_GPIO);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    //
    // Enable the I2C which is connected with M24Cxx
    //
    xSysCtlPeripheralEnable2(M24Cxx_PIN_I2C_PORT);   
    //
    // Set M24Cxx_PIN_I2C_SCK as IICx.SCK
    //
    xSPinTypeI2C(M24Cxx_I2C_SCK, M24Cxx_PIN_I2C_SCK);   
    //
    // Set M24Cxx_PIN_I2C_SDA as I2Cx.SDA
    //
    xSPinTypeI2C(M24Cxx_I2C_SDA, M24Cxx_PIN_I2C_SDA);  
    //
    // I2C enable
    //
    xI2CMasterEnable(M24Cxx_PIN_I2C_PORT);
    //
    // Initializes the I2C Master block.
    //
    xI2CMasterInit(M24Cxx_PIN_I2C_PORT, I2C_Speed);
}

//*****************************************************************************
//
//! \brief Write one byte to M24Cxx. 
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr specifies the address which data will be written.
//! 
//!  This function is to write one byte to M24Cxx,one byte will be writen in 
//!  appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24CxxByteWrite(unsigned char* pucBuffer, unsigned short usWriteAddr)
{
    xASSERT((usWriteAddr >= 0) && (usWriteAddr <= M24Cxx_SIZE));
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the M24Cxxs internal address.
    //
    xI2CMasterWriteS1(M24Cxx_PIN_I2C_PORT, M24Cxx_ADDRESS, 
                     (unsigned char)((usWriteAddr & 0xFF00) >> 8), 
                     xfalse);
    //
    // Transmit the LSB of the M24Cxxs internal address.
    //  
    xI2CMasterWriteS2(M24Cxx_PIN_I2C_PORT, 
                     (unsigned char)(usWriteAddr & 0x00FF),
                     xfalse);
    
    //
    // Send the byte to be written.
    //
    xI2CMasterWriteS2(M24Cxx_PIN_I2C_PORT, *pucBuffer, xtrue);
}

//*****************************************************************************
//
//! \brief Writes buffer of data to the M24Cxx.  
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr M24Cxx's internal address to write to.
//! \param usNumByteToWrite Number of bytes to write to the M24Cxx.
//! 
//!  This function is to Writes more then one byte to the M24Cxx,the appointed 
//!  byte length data will be writen in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24CxxBufferWrite(unsigned char* pucBuffer, 
                       unsigned short usWriteAddr, 
                       unsigned short usNumByteToWrite)
{
    unsigned char ucNumOfPage = 0, ucNumOfSingle = 0, ucCount = 0;
    unsigned short usAddr = 0;
    
    usAddr = usWriteAddr % M24Cxx_PAGESIZE;
    ucCount = M24Cxx_PAGESIZE -usAddr;
    ucNumOfPage = usNumByteToWrite / M24Cxx_PAGESIZE;
    ucNumOfSingle = usNumByteToWrite % M24Cxx_PAGESIZE;
    
    //
    // if usWriteAddr is M24Cxx_FLASH_PAGESIZE aligned.
    //
    if(usAddr == 0)
    { 
        //
        // If ucNumByteToWrite < M24Cxx_FLASH_PAGESIZE.
        //
        if(ucNumOfPage == 0)
        {
          M24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
          M24CxxWaitEepromStandbyState();
        }
        //
        // If ucNumByteToWrite > M24Cxx_FLASH_PAGESIZE.
        //
        else
        {
          while(ucNumOfPage--)
          {
            M24CxxPageWrite(pucBuffer, usWriteAddr, 
                            (unsigned char)M24Cxx_PAGESIZE);
            M24CxxWaitEepromStandbyState();
            usWriteAddr += M24Cxx_PAGESIZE;
            pucBuffer +=M24Cxx_PAGESIZE;
          }
          if(ucNumOfSingle !=0)
          {
            M24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            M24CxxWaitEepromStandbyState();
          }
        }
    }
    //
    // if usWriteAddr is not M24Cxx_FLASH_PAGESIZE aligned.
    //
    else
    {
      //
      // If ucNumByteToWrite < M24Cxx_FLASH_PAGESIZE.
      //
      if(ucNumOfPage == 0)
      {
        if(usNumByteToWrite > ucCount)
        {
            //
            // Write the data conained in same page.
            //
            M24CxxPageWrite(pucBuffer, usWriteAddr, ucCount);
            M24CxxWaitEepromStandbyState();
            //
            // Write the remaining data in the following page.
            //
            M24CxxPageWrite((unsigned char*)(pucBuffer + ucCount), 
                            (usWriteAddr + ucCount), 
                            (usNumByteToWrite - ucCount));
            M24CxxWaitEepromStandbyState();
        }
        else
        {
            M24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            M24CxxWaitEepromStandbyState();
        }
      }
      //
      // If ucNumByteToWrite > M24Cxx_FLASH_PAGESIZE.
      //
      else
      {
          usNumByteToWrite -= ucCount;
          ucNumOfPage = usNumByteToWrite / M24Cxx_PAGESIZE;
          ucNumOfSingle = usNumByteToWrite % M24Cxx_PAGESIZE;
          
          if(ucCount !=0)
          {
            M24CxxPageWrite(pucBuffer, usWriteAddr, ucCount);
            M24CxxWaitEepromStandbyState();
            usWriteAddr += ucCount;
            pucBuffer += ucCount;
          }
          while(ucNumOfPage --)
          {
            M24CxxPageWrite(pucBuffer, usWriteAddr, 
                            (unsigned char)M24Cxx_PAGESIZE);
            M24CxxWaitEepromStandbyState();
            usWriteAddr += M24Cxx_PAGESIZE;
            pucBuffer += M24Cxx_PAGESIZE;
          }
          if(ucNumOfSingle != 0)
          {
            M24CxxPageWrite(pucBuffer, usWriteAddr, ucNumOfSingle);
            M24CxxWaitEepromStandbyState();
          }
      }
    }
}

//*****************************************************************************
//
//! \brief Writes more than one byte to the M24Cxx with a single WRITE cycle.  
//!
//! \param pucBuffer specifies the location data which will be written.
//! \param usWriteAddr M24Cxx's internal address to write to.
//! \param ucNumByteToWrite number of byte to write to the M24Cxx
//!
//! This function is to write a page data to M24Cxx, The appointed byte length 
//! data will be written in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24CxxPageWrite(unsigned char* pucBuffer, 
                     unsigned short usWriteAddr, 
                     unsigned char ucNumByteToWrite)
{ 
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the M24Cxxs internal address.
    //
    xI2CMasterWriteS1(M24Cxx_PIN_I2C_PORT, M24Cxx_ADDRESS, 
                     (unsigned char)((usWriteAddr & 0xFF00) >> 8), 
                     xfalse);
    //
    // Transmit the LSB of the M24Cxxs internal address.
    //    
    xI2CMasterWriteS2(M24Cxx_PIN_I2C_PORT, 
                      (unsigned char)(usWriteAddr & 0x00FF),
                      xfalse);
	  
    //
    // While there is data to be written.
    //
    while(ucNumByteToWrite--)  
    {     
      if(ucNumByteToWrite == 0)
      {
        //
        // Send the byte to be written and STOP condition.
        //
        xI2CMasterWriteS2(M24Cxx_PIN_I2C_PORT, *pucBuffer, xtrue);
      }	
      else
      {
        //
        // Send the byte to be written.
        //
    	xI2CMasterWriteS2(M24Cxx_PIN_I2C_PORT, *pucBuffer, xfalse);
        //
        // point to the next byte to be written.
        //
        pucBuffer++;
      } 
    }
}
    
//*****************************************************************************
//
//! \brief Reads a block of data from the M24Cxx.  
//!
//! \param pucBuffer specifies the location data which will be store
//! \param usReadAddr M24Cxx internal address to read from.
//! \param usNumByteToRead number of bytes to read from the M24Cxx.
//!
//! This function is to read data from M24Cxx, the appointed byte length data 
//! will be read in appointed address.
//!
//! \return None.
//
//*****************************************************************************
void M24CxxBufferRead(unsigned char* pucBuffer, 
                      unsigned short usReadAddr,
                      unsigned short usNumByteToRead)
{
    //
    // Transmit the START condition, the slave address and the MSB of 
    // the M24Cxxs internal address.
    //
    xI2CMasterWriteS1(M24Cxx_PIN_I2C_PORT, M24Cxx_ADDRESS, 
                     (unsigned char)((usReadAddr & 0xFF00) >> 8), xfalse);
    //
    // Transmit the LSB of the M24Cxxs internal address.
    // 
    xI2CMasterWriteS2(M24Cxx_PIN_I2C_PORT,
                     (unsigned char)(usReadAddr & 0x00FF),xfalse);
    //
    // Only read one byte,after read,send STOP condition.
    //
    if(usNumByteToRead == 1)
    {
      xI2CMasterReadS1(M24Cxx_PIN_I2C_PORT, M24Cxx_ADDRESS, pucBuffer, xtrue);     
    } 
    else
    {
      xI2CMasterReadS1(M24Cxx_PIN_I2C_PORT, M24Cxx_ADDRESS, pucBuffer, xfalse);
    } 
    
    usNumByteToRead--;
    //
    // While there is data to be read.
    //
    while(usNumByteToRead)
    {
    	if(usNumByteToRead == 1)
    	{
          //
          // Disable ACK,read data,and then send STOP condition.
          //
      	  xI2CMasterReadS2(M24Cxx_PIN_I2C_PORT, pucBuffer, xtrue);
    	}	
    	else
        {
          //
          // Point to the next location where the byte read will saved.
          //
          pucBuffer++;
          //
          // read data.
          //
    	  xI2CMasterReadS2(M24Cxx_PIN_I2C_PORT, pucBuffer, xfalse);       
        }  
        usNumByteToRead--;        
    }
}   
//*****************************************************************************
//
//! \brief Wait for M24Cxx Standby state.  
//!
//! A Stop condition at the end of a Write command triggers the internal
//! Write cycle.
//!
//! \return None.
//
//*****************************************************************************
void M24CxxWaitEepromStandbyState(void)
{
    volatile unsigned short usSR1Tmp = 0; 
    do
    {
      //
      // Send START condition.
      //
      //I2CStartSend(M24Cxx_PIN_I2C_PORT);
      xHWREG(M24Cxx_PIN_I2C_PORT + I2C_CR1) |= I2C_CR1_START;
      //
      // Read I2C SR1 register to clear pending flags.
      //
      usSR1Tmp = xHWREG(M24Cxx_PIN_I2C_PORT + I2C_SR1);
      //
      // Send M24Cxx address for write.
      //
      xI2CMasterDataPut(M24Cxx_PIN_I2C_PORT, (M24Cxx_ADDRESS << 1) | 0);
    }while(!((xHWREG(M24Cxx_PIN_I2C_PORT + I2C_SR1)) & I2C_SR1_ADDR));   
    //
    // Clear Af flag.
    // 
    I2CFlagStatusClear(M24Cxx_PIN_I2C_PORT, I2C_SR1_AF);
    //
    // Send STOP condition.
    //
    xI2CMasterStop(M24Cxx_PIN_I2C_PORT);
}
