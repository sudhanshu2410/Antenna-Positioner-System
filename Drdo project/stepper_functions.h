/*
 * stepper_functions.h
 *
 *  Created on: 17-Jun-2025
 *      Author: P K Verma
 */

#ifndef STEPPER_FUNCTIONS_H_
#define STEPPER_FUNCTIONS_H_

void InitStepperMotors(unsigned int, unsigned int);
void StepCW(unsigned int, unsigned int);
void StepCCW(unsigned int, unsigned int);
unsigned int DegreesToSteps(float);

#endif /* STEPPER_FUNCTIONS_H_ */
