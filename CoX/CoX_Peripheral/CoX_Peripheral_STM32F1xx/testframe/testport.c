#include "test.h"

//*****************************************************************************
//
//! \brief Init uart to print.
//!
//! \param None
//!
//! \details uart config as (115200, 8 data bit, 1 stop bit , no partiy)
//!
//! \return None.
//
//*****************************************************************************

void 
TestIOInit(void)
{
    xSysCtlClockSet(72000000, xSYSCTL_OSC_MAIN | SYSCTL_XTAL_25MHZ);

    SysCtlDelay(10000);

    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_GPIOD);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);

    //xSPinTypeUART(UART2RX,PD6);
    xSPinTypeUART(UART2TX,PD5);
    

    xSysCtlPeripheralReset(xSYSCTL_PERIPH_UART2);
    xSysCtlPeripheralEnable(xSYSCTL_PERIPH_UART2);
    //SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_UART_S_EXT12M);

    xUARTConfigSet(USART2_BASE, 115200, (UART_CONFIG_WLEN_8 |
                                         UART_CONFIG_STOP_ONE | 
                                         UART_CONFIG_PAR_NONE));

    xUARTEnable(USART2_BASE, (UART_BLOCK_UART | UART_BLOCK_TX | UART_BLOCK_RX));
}

//*****************************************************************************
//
//! \brief print a char.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void 
TestIOPut(char ch)
{
    uint8_t c;
    c = ch;
    while((xHWREG(USART2_BASE + USART_SR) & (0x80))==0x00);
    
    //
    // Write this character to the transmit data register.
    //
    xHWREG(USART2_BASE + USART_DR) = c;

}

//*****************************************************************************
//
//! \brief Enable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestEnableIRQ(void)
{
    xCPUcpsie();
}

//*****************************************************************************
//
//! \brief Disable IRQ.
//!
//! \param None
//!
//! \return None.
//
//*****************************************************************************
void TestDisableIRQ(void)
{
    xCPUcpsid();
}

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.(COX)
//
//*****************************************************************************
#ifdef xDEBUG
void
__xerror__(char *pcFilename, unsigned long ulLine)
{
    while(1);
}
#endif

