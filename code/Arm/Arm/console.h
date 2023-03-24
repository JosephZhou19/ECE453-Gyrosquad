/*
 * console.h
 *
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

#define ENABLE_SERIAL_DEBUG 1

#if ENABLE_SERIAL_DEBUG
#include "cy_retarget_io.h"
#endif

#define PIN_CONSOLE_TX 	P5_1 // TODO: Update
#define PIN_CONSOLE_RX	P5_0 // TODO: Update


/* Public Function API */
void console_init(void);


#endif /* CONSOLE_H_ */
