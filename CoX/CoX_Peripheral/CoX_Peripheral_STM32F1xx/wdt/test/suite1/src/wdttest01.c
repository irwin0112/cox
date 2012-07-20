//*****************************************************************************
//
//! @page xwdt_testcase xwdt register test
//!
//! File: @ref wdttest01.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xwdt sub component.<br><br>
//! - \p Board: HT32F175x <br><br>
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
//! - \subpage test_xgpio_register
//! .
//! \file wdttest01.c
//! \brief xwdt test source file
//! \brief xwdt test header file <br>
//
//*****************************************************************************
#include "xhw_memmap.h"
#include "test.h"
#include "xhw_wdt.h"
#include "xwdt.h"


//*****************************************************************************
//
//!\page test_xwdt_register test_xwdt_register
//!
//!<h2>Description</h2>
//!Test xwdt register. <br>
//!
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Get the Test description of xwdt002 register test.
//!
//! \return the desccription of the xwdt002 test.
//
//*****************************************************************************
static char* xwdt002GetTest(void)
{
    return "xwdt, 002, wdt interrupt test";
}


//*****************************************************************************
//
//! \breif Wdt interrupt handler.
//!
//! \return None
//
//*****************************************************************************
unsigned long WDTCallback(void *pvCBData, unsigned long ulEvent, 
                                      unsigned long ulMsgParam, void *pvMsgData)                                        
{
    TestEmitToken('a');

    //
    // clear WDT counter
    //
//    WDTimerRestart();
        
    return 0;
}

//*****************************************************************************
//
//! \brief  Wdt api wdt interrupt test.
//!
//! \return None.
//
//*****************************************************************************
static void wdt_WDTInterrupt_test(void)
{
    //
    // Set WatchDog Timer(WDT)'s Timer Interval.
    //  
    WDTimerInit(2022);
    
    //
    // Enable the WDT Interrupt
    //
    WDTimerFunctionEnable(WDT_INT_FUNCTION);

//    xIntEnable(INT_WDT);

//    WDTimerRestart();
    //
    // Install the callback function
    //
    WDTimerIntCallbackInit(WDTCallback);
    
    TestAssertQBreak("a", "WDT Interrupy fialed!", 5000000);
}
//*****************************************************************************
//
//! \brief xwdt002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt002Execute(void)
{
    wdt_WDTInterrupt_test();
}



//*****************************************************************************
//
//! \brief something should do before the test execute of xwdt002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt002Setup(void)
{
    //
    // Enable WDT
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WWDG);

    //
    // Set WDT clock source
    //
//    xSysCtlPeripheralClockSourceSet(xSYSCTL_WDT0_EXTSL, 32);
}

//*****************************************************************************
//
//! \brief something should do after the test execute of xwdt002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xwdt002TearDown(void)
{
    SysCtlPeripheralReset(SYSCTL_PERIPH_WWDG);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WWDG);
}

//
// xwdt002 register test case struct.
//
const tTestCase sTestXWdt002Register = {
    xwdt002GetTest,		
    xwdt002Setup,
    xwdt002Execute,
    xwdt002TearDown

};

//
// Xwdt test suits.
//
const tTestCase * const psPatternXwdt01[] =
{
    &sTestXWdt002Register,
    0
};

