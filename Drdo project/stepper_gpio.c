/*
 * stepper_gpio.c
 *
 *  Created on: Jun 11, 2025
 *      Author: P K Verma
 */

#include "soc_AM335x.h"
#include "beaglebone.h"
#include "gpio_v2.h"
#include "pin_mux.h"
#include "hw_types.h"
#include "stepper_gpio.h"

void SM1PinMuxSetup(void)
{
    GpioPinMuxSetup(SM1_PIN_A1_PAD_CTRL_OFFSET,SM1_PIN_A1_PAD_CTRL_VALUE);
    GpioPinMuxSetup(SM1_PIN_A2_PAD_CTRL_OFFSET,SM1_PIN_A2_PAD_CTRL_VALUE);
    GpioPinMuxSetup(SM1_PIN_B1_PAD_CTRL_OFFSET,SM1_PIN_B1_PAD_CTRL_VALUE);
    GpioPinMuxSetup(SM1_PIN_B2_PAD_CTRL_OFFSET,SM1_PIN_B2_PAD_CTRL_VALUE);
}

void SM2PinMuxSetup(void)
{
    GpioPinMuxSetup(SM2_PIN_A1_PAD_CTRL_OFFSET,SM2_PIN_A1_PAD_CTRL_VALUE);
    GpioPinMuxSetup(SM2_PIN_A2_PAD_CTRL_OFFSET,SM2_PIN_A2_PAD_CTRL_VALUE);
    GpioPinMuxSetup(SM2_PIN_B1_PAD_CTRL_OFFSET,SM2_PIN_B1_PAD_CTRL_VALUE);
    GpioPinMuxSetup(SM2_PIN_B2_PAD_CTRL_OFFSET,SM2_PIN_B2_PAD_CTRL_VALUE);
}

void ConfigSMGPIOs(void)
{
    /* Enabling functional clocks for GPIO1 instance. */
    GPIO2ModuleClkConfig();

    /* Selecting SM1 GPIO pins for use. */
    SM1PinMuxSetup();

    /* Selecting SM2 GPIO pins for use. */
    SM2PinMuxSetup();

    /* Enabling the SM1 GPIO module. */
    GPIOModuleEnable(SM1_GPIO);

//    /* Enabling the SM2 GPIO module. */
//    GPIOModuleEnable(SM2_GPIO);

    /* Resetting the SM1 GPIO module. */
    GPIOModuleReset(SM1_GPIO);

//    /* Resetting the SM2 GPIO module. */
//    GPIOModuleReset(SM2_GPIO);

    /* Setting SM1 GPIO pins as an output pin. */
    GPIODirModeSet(SM1_GPIO,SM1_PIN_A1,GPIO_DIR_OUTPUT);
    GPIODirModeSet(SM1_GPIO,SM1_PIN_A2,GPIO_DIR_OUTPUT);
    GPIODirModeSet(SM1_GPIO,SM1_PIN_B1,GPIO_DIR_OUTPUT);
    GPIODirModeSet(SM1_GPIO,SM1_PIN_B2,GPIO_DIR_OUTPUT);

    /* Setting SM2 GPIO pins as an output pin. */
    GPIODirModeSet(SM2_GPIO,SM2_PIN_A1,GPIO_DIR_OUTPUT);
    GPIODirModeSet(SM2_GPIO,SM2_PIN_A2,GPIO_DIR_OUTPUT);
    GPIODirModeSet(SM2_GPIO,SM2_PIN_B1,GPIO_DIR_OUTPUT);
    GPIODirModeSet(SM2_GPIO,SM2_PIN_B2,GPIO_DIR_OUTPUT);
}

void SM1GPIOWrite(unsigned int val)
{
    HWREG(SM1_GPIO + GPIO_SETDATAOUT) = SM1_GPIO_SHIFT(val);   //Set ones in their place
    HWREG(SM1_GPIO + GPIO_CLEARDATAOUT) = (~(SM1_GPIO_SHIFT(val))) & SM1_GPIO_MASK;   //Set zeros in their place
}

void SM2GPIOWrite(unsigned int val)
{
    HWREG(SM2_GPIO + GPIO_SETDATAOUT) = SM2_GPIO_SHIFT(val);   //Set ones in their place
    HWREG(SM2_GPIO + GPIO_CLEARDATAOUT) = (~(SM2_GPIO_SHIFT(val))) & SM2_GPIO_MASK;   //Set zeros in their place
}
