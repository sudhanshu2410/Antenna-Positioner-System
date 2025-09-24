/*
 * APS_uart.h
 *
 *  Created on: 17-Jun-2025
 *      Author: P K Verma
 */

#ifndef APS_UART_H_
#define APS_UART_H_

extern void ConfigGPSUart(void);
extern void UARTStringPut(unsigned int, char*);
extern void UARTGetString(unsigned int, char*);
extern void ConsoleUARTStringPut(char*);
extern void ConsoleUARTGetString(char*);
extern void ConfigConsoleUart(void);

#endif /* APS_UART_H_ */
