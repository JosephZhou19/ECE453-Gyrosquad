/*
 *      Author: Joseph Zhou
 */

#ifndef STEPPER_H__
#define STEPPER_H__

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

// Pin definitions for the ECE453 Staff Dev board
#define STEPPER_ENABLEN 		P0_0
#define STEPPER_SLEEPN			P0_1
#define STEPPER_STEP			P0_4
#define STEPPER_DIR				P0_5
#define STEPPER_USM0			P5_0
#define STEPPER_USM1			P5_1
#define STEPPER_RESETN			P5_2
#define STEPPER_SRN				P5_3
#define STEPPER_HOMEN			P5_4

#define INT_PRIORITY_PUSH_BUTTON	3

// Exported Global Variables
extern volatile bool ALERT_STEPPER_HOMEN;

/* Public Function API */
void stepper_homen_handler(void* handler_arg, cyhal_gpio_event_t event);
void stepper_homen_init(void);

/* Initializes the IO functions */
void stepper_init(void);

#endif
