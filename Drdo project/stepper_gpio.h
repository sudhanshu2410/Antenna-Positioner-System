/*
 * stepper_gpio.h
 *
 *  Created on: Jun 11, 2025
 *      Author: P K Verma
 */

#ifndef STEPPER_GPIO_H_
#define STEPPER_GPIO_H_

#define SM1                         1
#define SM2                         2

#define SM1_GPIO                    (SOC_GPIO_2_REGS)
#define SM1_PIN_A1                  (10)    //GPIO_2_10    P8 pin41
#define SM1_PIN_A2                  (11)    //GPIO_2_11    P8 pin42
#define SM1_PIN_B1                  (12)    //GPIO_2_12    P8 pin39
#define SM1_PIN_B2                  (13)    //GPIO_2_13    P8 pin40
#define SM1_GPIO_MASK               ((1<<SM1_PIN_A1)|(1<<SM1_PIN_A2)|(1<<SM1_PIN_B1)|(1<<SM1_PIN_B2))
#define SM1_GPIO_SHIFT(x)           (x<<SM1_PIN_A1)

#define SM2_GPIO                    (SOC_GPIO_2_REGS)
#define SM2_PIN_A1                  (6)    //GPIO_2_6    P8 pin45
#define SM2_PIN_A2                  (7)    //GPIO_2_7    P8 pin46
#define SM2_PIN_B1                  (8)    //GPIO_2_8    P8 pin43
#define SM2_PIN_B2                  (9)    //GPIO_2_9    P8 pin44
#define SM2_GPIO_MASK               ((1<<SM2_PIN_A1)|(1<<SM2_PIN_A2)|(1<<SM2_PIN_B1)|(1<<SM2_PIN_B2))
#define SM2_GPIO_SHIFT(x)           (x<<SM2_PIN_A1)

#define SM1_PIN_A1_PAD_CTRL_OFFSET          GPIO_2_10
#define SM1_PIN_A2_PAD_CTRL_OFFSET          GPIO_2_11
#define SM1_PIN_B1_PAD_CTRL_OFFSET          GPIO_2_12
#define SM1_PIN_B2_PAD_CTRL_OFFSET          GPIO_2_13
#define SM1_PIN_A1_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7) /* Slow Slew Rate - Receiver Disabled - NA - PU/PD feature Disabled. Mux-mode=7 */
#define SM1_PIN_A2_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7)
#define SM1_PIN_B1_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7)
#define SM1_PIN_B2_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7)

#define SM2_PIN_A1_PAD_CTRL_OFFSET          GPIO_2_6
#define SM2_PIN_A2_PAD_CTRL_OFFSET          GPIO_2_7
#define SM2_PIN_B1_PAD_CTRL_OFFSET          GPIO_2_8
#define SM2_PIN_B2_PAD_CTRL_OFFSET          GPIO_2_9
#define SM2_PIN_A1_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7)
#define SM2_PIN_A2_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7)
#define SM2_PIN_B1_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7)
#define SM2_PIN_B2_PAD_CTRL_VALUE           PAD_SL_RXD_NA_PUPDD(7)

extern void SM1PinMuxSetup(void);
extern void SM2PinMuxSetup(void);
extern void ConfigSMGPIOs(void);
extern void SM1GPIOWrite(unsigned int);
extern void SM2GPIOWrite(unsigned int);

#endif /* STEPPER_GPIO_H_ */
