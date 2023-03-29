/*
 * usr_btn.c
 *
 *  Created on: Sep 9, 2022
 *      Author: Joe Krachey
 */

#include "usr_btn.h"


/*****************************************************************************/
/* Interrupt Service Routine for Timer used to Debounce the USR_BTN          */
/*****************************************************************************/
static void isr_usr_btn_timer(void* callback_arg, cyhal_timer_event_t event)
{
	/* ADD Code to debounce the USR_BTN */
	BTN_COUNT++;
}


/*****************************************************************************
/* This function should accomplish the following:
 *
 *		USR_BTN
 *     	- Configure the USR_BTN as an INPUT pin
 *
 *     	TIMER
 * 		- Configure an Timer resource to run at a rate of 10KHz
 * 		- Configure the same timer to generate an interrupt every 10mS.
 *
 * 		TIMER ISR
 * 		-Debounce the USR_BTN so that you only detect the falling edge of the
 * 		push button.
 * 		- A falling edge will occur if the ISR detects the IO pin
 * 		is a value of 1 followed by seven consecutive calls to the ISR where
 * 		the IO pins is a value of 0.
 * 		- When a button press is detected, increment BTN_COUNT
 *
 */
/*****************************************************************************/
cy_rslt_t usr_btn_init(void)
{
	cy_rslt_t rslt;

	/* Configure USER_BTN */
	cy_rslt_t   rslt;
	rslt = cyhal_gpio_init(USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	// Initialize the timer object. */

	// Set the frequency of timer to 100 Hz

	// Coinfigure the timer to generate an interrupt

	return rslt;
}

