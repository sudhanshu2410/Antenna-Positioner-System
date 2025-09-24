/*
 * stepper_functions.c
 *
 *  Created on: 16-Jun-2025
 *      Author: P K Verma
 */

#include "stepper_gpio.h"

/*****Bipolar Full-step sequence********
 *          A1  A2  B1  B2
 * Step1:   1   0   0   1
 * Step2:   1   1   0   0
 * Step3:   0   1   1   0
 * Step4:   0   0   1   1
 */

/*****Bipolar Half-step sequence********
 *          A1  A2  B1  B2
 * Step1:   1   0   0   1
 * Step2:   1   0   0   0
 * Step3:   1   1   0   0
 * Step4:   0   1   0   0
 * Step5:   0   1   1   0
 * Step6:   0   0   1   0
 * Step7:   0   0   1   1
 * Step8:   0   0   0   1
 */

/*****Unipolar Full-step sequence********
 *          A1  A2  B1  B2
 * Step1:   1   0   0   0
 * Step2:   0   1   0   0
 * Step3:   0   0   1   0
 * Step4:   0   0   0   1
 */

/*****Unipolar Half-step sequence********
 *          A1  A2  B1  B2
 * Step1:   1   0   0   0
 * Step2:   1   1   0   0
 * Step3:   0   1   0   0
 * Step4:   0   1   1   0
 * Step5:   0   0   1   0
 * Step6:   0   0   1   1
 * Step7:   0   0   0   1
 * Step8:   1   0   0   1
 */

/*****Note: Below Code is written for Unipolar Half-step sequence********/

static unsigned int sm1_nibble;
static unsigned int sm2_nibble;

static void StepDelay(void)
{
    unsigned int count= 0x5FFF;
    while(count--);
}

void InitStepperMotors(unsigned int sm1_init_val, unsigned int sm2_init_val)
{
    sm1_nibble= sm1_init_val;
    sm2_nibble= sm2_init_val;
    SM1GPIOWrite(sm1_nibble);
    SM2GPIOWrite(sm2_nibble);
}
/***** Function for moving motor Clock-wise in full step sequence**********/
void StepCW(unsigned int motor_num, unsigned int num_of_steps)
{
    switch(motor_num)
    {
        case SM1:
            while(num_of_steps--)
            {

                if(sm1_nibble & 0x8)
                    sm1_nibble= (((sm1_nibble<<1)|0x1)&0xF);
                else
                    sm1_nibble= ((sm1_nibble<<1)&0xF);
                SM1GPIOWrite(sm1_nibble);
                StepDelay();
            }
            break;
        case SM2:
            while(num_of_steps--)
            {

                if(sm2_nibble & 0x8)
                    sm2_nibble= (((sm2_nibble<<1)|0x1)&0xF);
                else
                    sm2_nibble= ((sm2_nibble<<1)&0xF);
                SM2GPIOWrite(sm2_nibble);
                StepDelay();
            }
        default: break;
    }

}
/***** Function for moving motor Counter Clock-wise in full step sequence**********/
void StepCCW(unsigned int motor_num, unsigned int num_of_steps)
{
    switch(motor_num)
    {
        case SM1:
            while(num_of_steps--)
            {

                if(sm1_nibble & 0x1)
                    sm1_nibble= (((sm1_nibble>>1)|0x8)&0xF);
                else
                    sm1_nibble= ((sm1_nibble>>1)&0xF);
                SM1GPIOWrite(sm1_nibble);
                StepDelay();
            }
            break;
        case SM2:
            while(num_of_steps--)
            {

                if(sm2_nibble & 0x1)
                    sm2_nibble= (((sm2_nibble>>1)|0x8)&0xF);
                else
                    sm2_nibble= ((sm2_nibble>>1)&0xF);
                SM2GPIOWrite(sm2_nibble);
                StepDelay();
            }
        default: break;
    }

}

/*********** This function is specific to 28BJY-48 Stepper Motor ********************/
unsigned int DegreesToSteps(float Deg)
{
    return ((Deg*32)/5.625); //assuming full-stepping sequence
    //Note: conversion factor will be 64/5.625 in half-stepping sequence
}
