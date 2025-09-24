/*
 * APS_uart.c
 *
 *  Created on: 16-Jun-2025
 *      Author: P K Verma
 */


#include "uart_irda_cir.h"
#include "soc_AM335x.h"
#include "interrupt.h"
#include "beaglebone.h"
#include "hw_types.h"
#include "consoleUtils.h"

/******************************************************************************
**              INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define GPS_UART                  SOC_UART_1_REGS
#define GPS_BAUD_RATE             (38400)
#define UART_MODULE_INPUT_CLK     (48000000)

/******************************************************************************
**              INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
//static void UartInterruptEnable(void);
//static void UART0AINTCConfigure(void);
static void UartFIFOConfigure(void);
static void UartBaudRateSet(void);
//static void UARTIsr(void);

/*
** A wrapper function performing FIFO configurations.
*/

static void UartFIFOConfigure(void)
{
    unsigned int fifoConfig = 0;

    /*
    ** - Transmit Trigger Level Granularity is 4
    ** - Receiver Trigger Level Granularity is 1
    ** - Transmit FIFO Space Setting is 56. Hence TX Trigger level
    **   is 8 (64 - 56). The TX FIFO size is 64 bytes.
    ** - The Receiver Trigger Level is 1.
    ** - Clear the Transmit FIFO.
    ** - Clear the Receiver FIFO.
    ** - DMA Mode enabling shall happen through SCR register.
    ** - DMA Mode 0 is enabled. DMA Mode 0 corresponds to No
    **   DMA Mode. Effectively DMA Mode is disabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_4,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  UART_FCR_TX_TRIG_LVL_56,
                                  1,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_0_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(GPS_UART, fifoConfig);
}

/*
** A wrapper function performing Baud Rate settings.
*/

static void UartBaudRateSet(void)
{
    unsigned int divisorValue = 0;

    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         GPS_BAUD_RATE,
                                         UART16x_OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);

    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(GPS_UART, divisorValue);
}

void ConfigGPSUart(void)
{
    /* Configuring the system clocks for UART1 instance. */
    UART1ModuleClkConfig();

    /* Performing the Pin Multiplexing for UART1 instance. */
    UARTPinMuxSetup(1);

    /* Performing a module reset. */
    UARTModuleReset(GPS_UART);

    /* Performing FIFO configurations. */
    UartFIFOConfigure();

    /* Performing Baud Rate settings. */
    UartBaudRateSet();

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(GPS_UART, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(GPS_UART,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                         UART_PARITY_NONE);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(GPS_UART);

    /* Disabling Break Control. */
    UARTBreakCtl(GPS_UART, UART_BREAK_COND_DISABLE);

    /* Switching to UART16x operating mode. */
    UARTOperatingModeSelect(GPS_UART, UART16x_OPER_MODE);

    /* Performing Interrupt configurations. */
    //UartInterruptEnable();
}

void ConfigConsoleUart(void)
{
    /* Initialize the UART console */
    ConsoleUtilsInit();

    /* Select the console type based on compile time check */
    ConsoleUtilsSetType(CONSOLE_UART);
}

void UARTStringPut(unsigned int uart_instance, char* ptr)
{
    while(*ptr)
    {
        UARTCharPut(uart_instance, *ptr);
        ptr++;
    }
    UARTCharPut(uart_instance,'\n');
    UARTCharPut(uart_instance,'\r');
}

void UARTGetString(unsigned int uart_instance, char* ptr)
{
    char* p;
    p= ptr;
    *p=UARTCharGetNonBlocking(uart_instance);
    while(1)
    {
        *p= UARTCharGet(uart_instance);
        if(*p==0x0D)
            break;
        UARTCharPut(uart_instance, *p);
        p++;
    }
    *p=0;
    UARTStringPut(uart_instance,"\r");
}

void ConsoleUARTStringPut(char* ptr)
{
    while(*ptr)
    {
        UARTCharPut(SOC_UART_0_REGS, *ptr);
        ptr++;
    }
    UARTCharPut(SOC_UART_0_REGS,'\n');
    UARTCharPut(SOC_UART_0_REGS,'\r');
}

void ConsoleUARTGetString(char* ptr)
{
    char* p;
    p= ptr;
    *p=UARTCharGetNonBlocking(SOC_UART_0_REGS);
    while(1)
    {
        *p= UARTCharGet(SOC_UART_0_REGS);
        if(*p==0x0D)
            break;
        UARTCharPut(SOC_UART_0_REGS, *p);
        p++;
    }
    *p=0;
    ConsoleUARTStringPut("\r");
}



/*
** A wrapper function performing Interrupt configurations.
*/

//static void UartInterruptEnable(void)
//{
//    /* Enabling IRQ in CPSR of ARM processor. */
//    IntMasterIRQEnable();
//
//    /* Configuring AINTC to receive UART0 interrupts. */
//    UART0AINTCConfigure();
//
//    /* Enabling the specified UART interrupts. */
//    UARTIntEnable(SOC_UART_0_REGS,UART_INT_RHR_CTI);
//}

/*
** Interrupt Service Routine for UART.
*/

//static void UARTIsr(void)
//{
//    unsigned char rxByte = 0;
//            /* Read the byte received */
//            rxByte = UARTCharGetNonBlocking(SOC_UART_0_REGS);
//            /* transmit the byte just read */
//            UARTCharPutNonBlocking(SOC_UART_0_REGS, rxByte);
//}

/*
** This function configures the AINTC to receive UART interrupts.
*/

//static void UART0AINTCConfigure(void)
//{
//    /* Initializing the ARM Interrupt Controller. */
//    IntAINTCInit();
//
//    /* Registering the Interrupt Service Routine(ISR). */
//    IntRegister(SYS_INT_UART0INT, UARTIsr);
//
//    /* Setting the priority for the system interrupt in AINTC. */
//    IntPrioritySet(SYS_INT_UART0INT, 0, AINTC_HOSTINT_ROUTE_IRQ);
//
//    /* Enabling the system interrupt in AINTC. */
//    IntSystemEnable(SYS_INT_UART0INT);
//}

/******************************* End of file *********************************/

