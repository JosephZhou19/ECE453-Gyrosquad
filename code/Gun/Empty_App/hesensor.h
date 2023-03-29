/*
 *      Author: Joseph Zhou
 */

#ifndef HESENSOR_H__
#define HESENSOR_H__

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

// Pin definitions for the ECE453 Staff Dev board
#define HESENSOR_SIG 		P10_6
extern volatile bool ALERT_HESENSOR_SIG;

/* Public Function API */
void hesensor_sig_handler(void* handler_arg, cyhal_gpio_event_t event);
void hesensor_sig_init(void);
/* Initializes the IO functions */
void hesensor_init(void);
#endif
