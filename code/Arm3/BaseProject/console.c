/*
 * console.c
 *
 *  Created on: Jan 21, 2022
 *      Author: Joe Krachey
 */

#include "console.h"

/** Initializes the SCB used to send/receive data from the PC
 *
 * @param
 *
 */
void console_init(void)
{
#if ENABLE_SERIAL_DEBUG
 // Initialize the console using cy_retarget_io_init();
	cy_retarget_io_init(PIN_CONSOLE_TX, PIN_CONSOLE_RX, CY_RETARGET_IO_BAUDRATE);
#endif
}






