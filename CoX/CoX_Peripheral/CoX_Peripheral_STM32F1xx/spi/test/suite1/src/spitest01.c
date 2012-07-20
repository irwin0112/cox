//*****************************************************************************
//
//! @page xspi_testcase loopback and interrupt test
//!
//! File: @ref spitest03.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: EMST32F1xx <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xspi_register
//! .
//! \file spitest01.c
//! \brief xspi test source file
//! \brief xspi test header file <br>
//
//*****************************************************************************
#include "xhw_memmap.h"
#include "test.h"
#include "xspi.h"
#include "xhw_spi.h"
#include "xsysctl.h"

//*****************************************************************************
//
//!\page test_xspi_register test_xsysctl_register
//!
//!<h2>Description</h2>
//!Test xspi register. <br>
//!
//
//*****************************************************************************
unsigned long ulSourceData[] = {1, 2, 3, 4,
                                5, 6, 7, 8};

unsigned long ulDestData[8];
unsigned long ulDestData1[8];

unsigned long j, i = 0;
unsigned long g_ulSynchronize = 1;

//*****************************************************************************
//! \breif External interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long user_Callback0(void *pvCBData, unsigned long ulEvent, 
                                     unsigned long ulMsgParam, void *pvMsgData)                                        
{ 
	  g_ulSynchronize = 0;
    xIntDisable(xINT_GPIOA);
	  
    return 0;
}

unsigned long SPICallback(void *pvCBData,  unsigned long ulEvent,
                                       unsigned long ulMsgParam,
                                       void *pvMsgData)
{  
	//
	// Write a date to exti the interrupt
	//
	SPIDataGet(xSPI1_BASE, &ulDestData[i]);	
	//SPIIntDisable(SPI1_BASE, SPI_INT_TX);
	
  return 0;
}
//*****************************************************************************
//
//! \brief Get the Test description of xSPI101 register test.
//!
//! \return the desccription of the xSPI101 test.
//
//*****************************************************************************
const char* xSPI01GetTest(void)
{
    return "xspi, 002, xspi loopback and interrupt test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xSPI101 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI01Setup(void)
{    
    //
    // Set SysClk 8MHz using Extern 8M oscillator
    //
    xSysCtlClockSet(16000000, xSYSCTL_OSC_MAIN | xSYSCTL_XTAL_8MHZ);

    //
    // Enable Peripheral SPI1
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SPI1);  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO); 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_IOPA); 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_IOPC);	
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xSPI101 test.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI01TearDown(void)
{   
    SysCtlPeripheralDisable(SYSCTL_PERIPH_SPI1);
}

//*****************************************************************************
//
//! \brief xspi 001 test of SPI1 initialization.
//!
//! \return None.
//
//*****************************************************************************
static void SPIMasterInit(void)
{
    //
    // Configure Some GPIO pins as SPI Mode
    //
	
    /*
	  xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_13, xGPIO_DIR_MODE_OUT);
	
    while(1)
    {		
		    GPIOPinSet(GPIOC_BASE, GPIO_PIN_13);
		    for(i = 0; i < 10000; i++);
			  GPIOPinReset(GPIOC_BASE, GPIO_PIN_13);
		}
    */
	
    xGPIOSDirModeSet(PA5, GPIO_DIR_MODE_HWSTD);
    xGPIOSDirModeSet(PA7, GPIO_DIR_MODE_HWSTD);
    xGPIOSDirModeSet(PA6, GPIO_TYPE_IN_FLOATING);
    xGPIOSDirModeSet(PA4, GPIO_DIR_MODE_HWSTD);	
	
    //
    // Master Mode polarity 0,Rx latched at rising edge Tx changed at rising edge
    // 200000Hz 8Bits Data windth  SPI MSB First
    //
    xSPIConfigSet(SPI1_BASE, 100000, SPI_FORMAT_MODE_3 | SPI_DATA_WIDTH8 | 
                                               SPI_LSB_FIRST | SPI_MODE_MASTER);
		//
    // Software Control Transfer Select SS0
    //
		
    xSPISSSet(SPI1_BASE, xSPI_SS_SOFTWARE, xSPI_SS0);
		//SPISSModeConfig(SPI1_BASE, SPI_SS_HARDWARE);
		//SPISSIConfig(SPI1_BASE, SPI_SSSET);
		//SPISSOutputConfig(SPI1_BASE, SPI_SSOE_ENABLE);

 	//  xSPIIntCallbackInit(SPI1_BASE, SPICallback);
  //		xIntEnable(INT_SPI1);
  //  xIntPrioritySet(INT_SPI1, 1);
  //  xSPIIntEnable(SPI1_BASE, SPI_INT_RX);
		xSPIEnable(SPI1_BASE);

    //
    // Set PA.0 as mode in
    //
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_1, xGPIO_DIR_MODE_IN);
    
    //
    // Set GPIO pin interrupt callback.
    //
    xGPIOPinIntCallbackInit(xGPIO_PORTA_BASE, xGPIO_PIN_0, user_Callback0);
    
    //
    // Enable GPIO pin interrupt.
    //
    xGPIOPinIntEnable(xGPIO_PORTA_BASE, xGPIO_PIN_0, GPIO_RISING_EDGE);
    
    xIntEnable(xINT_GPIOA);	
}

//*****************************************************************************
//
//! \brief xspi 001 test of SPI Loopback between SPI1MISO and SPI1MOSI.
//!
//! \return None.
//
//*****************************************************************************
static void xspi_SpiLoopbackTest_test(void)
{
	  /*
    while(g_ulSynchronize)
		{   
    }	
	  */
    for(i = 0; i < 8; i++)
	  //while(1)
    {
			  ulDestData[i] = xSPISingleDataReadWrite(xSPI1_BASE, ulSourceData[i]);
			  //�SPIDataPut(xSPI1_BASE, ulSourceData[i]);	
			  // SPIDataGet(xSPI1_BASE, &ulDestData[i]);	
			  //SPIDataGet(xSPI1_BASE, &ulDestData[i]);	
				//xSPIDataPutNonBlocking(SPI1_BASE, ulSourceData[i]);
		    //xSPIDataGetNonBlocking(xSPI1_BASE, &ulDestData[i]);
        //TestAssertQBreak("a", "Transfer Over Interrupy fialed!", 0xFFFFFFFF);
    } 

    for(i = 0; i < 8; i++)
    {
        TestAssert((ulSourceData[i] == ulDestData[i]), "xspi API error!");
    }
}

//*****************************************************************************
//
//! \brief xspi 001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xSPI01Execute(void)
{
    SPIMasterInit();
    xspi_SpiLoopbackTest_test();
}


//
// xspi register test case struct.
//
const tTestCase sTestxSPI01Register = {
    xSPI01GetTest,
    xSPI01Setup,
    xSPI01TearDown,
    xSPI01Execute
};

//
// xspi test suits.
//
const tTestCase * const psPatternxSPI01[] =
{
    &sTestxSPI01Register,
    0
};
