/*
 *      Author: Joseph Zhou
 */

#ifndef SERVO_H__
#define SERVO_H__

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

// Pin definitions for the ECE453 Staff Dev board
#define SERVO_SIG 		P6_2

/* Initializes the IO functions */
void servo_init(void);
void servo_run(uint32_t freq, uint32_t time);
#endif
