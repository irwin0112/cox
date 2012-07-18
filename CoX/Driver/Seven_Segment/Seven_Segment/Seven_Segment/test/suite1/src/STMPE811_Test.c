//*****************************************************************************
//
//! @page STMPE811_testcase STMPE811 function test
//!
//! File: @ref STMPE811Test.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the STMPE811 sub component.<br><br>
//! - \p Board: STM32F107 <br><br>
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
//! - \subpage test_M24Cxx_Function
//! .
//! \file M24CxxTest.c
//! \brief M24Cxx test source file
//! \brief M24Cxx test header file <br>
//
//*****************************************************************************

#include "test.h"
#include "Seven_Segment.h"

//*****************************************************************************
//
//! \brief Get the Test description of STMPE811 Function test.
//!
//! \return the desccription of the STMPE811 test.
//
//*****************************************************************************
static char* STMPE811GetTest(void)
{

    return "STMPE811 Function test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of M24Cxx test.
//!
//! \return None.
//
//*****************************************************************************
static void STMPE811Setup(void)
{
    SevenSegmentInit();
}

//*****************************************************************************
//
//! \brief something should do after the test execute of STMPE811 test.
//!
//! \return None.
//
//*****************************************************************************
static void STMPE811TearDown(void)
{
}

//*****************************************************************************
//
//! \brief STMPE811 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void STMPE811Execute(void)
{
    unsigned long i;
    while(1)
    {
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(1234,DECIMAL);
      }
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(5678,DECIMAL);
      }
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(0x90aab,HEXADECIMAL);
      }
      for(i = 200; i > 0; i--)
      {
        SevenSegmentScan(0xcdef,HEXADECIMAL);
      }
    }
}

//
// STMPE811 Function test case struct.
//
const tTestCase sTestSTMPE811Function = {
    STMPE811GetTest,	
    STMPE811Setup,
    STMPE811TearDown,
    STMPE811Execute
};

//
// STMPE811 test suits.
//
const tTestCase * const psPatternSTMPE811Test[] =
{
    &sTestSTMPE811Function,
    0
};

