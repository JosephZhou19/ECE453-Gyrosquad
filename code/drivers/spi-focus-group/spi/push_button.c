/*
 * push_button.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Joe Krachey
 */

#include "push_button.h"

volatile bool ALERT_PUSH_BUTTON = false;

/* IO Pin Handler Struct */
cyhal_gpio_callback_data_t push_button_cb_data =
{
    .callback     = push_button_handler,
    .callback_arg = (void*)NULL
};


/** IRQ handler for SW401
 *
 * @param
 *
 */
void push_button_handler(void* handler_arg, cyhal_gpio_event_t event)
{
	ALERT_PUSH_BUTTON = true;

    /* Toggle LED401 when an interrupt has been detected */
    //CY_UNUSED_PARAMETER(event);
    // Increment global_count (passed as handler_arg) using a pointer
    /*uint32_t* count = (uint32_t*)handler_arg;
    *count = *count + 1;*/

    // Toggle pin LED on every interrupt
//    cyhal_gpio_toggle(PIN_USER_LED);
//    cyhal_gpio_write(PIN_USER_LED, 0);

}

/** Configure SW401 to generate an interrupt when the push button
 * has been pressed
 *
 * @param
 *
 */
static void push_button_irq_init(void)
{
	/* You will need to examine the HAL API to determine how to
	 * register a callback function when an interrupt has been detected
	 */

	/* You will need to examine the HAL API to enable falling edge event to
	 * generate an interrupt
	 */


        // Register callback function - gpio_interrupt_handler and pass the value global_count
        cyhal_gpio_register_callback(PIN_PUSH_BUTTON, &push_button_cb_data);

        // Enable falling edge interrupt event with interrupt priority set to 3
        cyhal_gpio_enable_event(PIN_PUSH_BUTTON, CYHAL_GPIO_IRQ_FALL, INT_PRIORITY_PUSH_BUTTON, true);
    return;
}

/** Initialize the pin connected to SW401 to be an input pin
 *
 * @param
 *
 */
static void push_button_io_init(void)
{
	/* Initialize SW401.  You will need to examine the HAL API to determine how to
	 * initialize an IO pin an input
	 */
    //cy_rslt_t rslt;
    //bool      read_val;

    // Initialize pin P5_6 as an input
    cyhal_gpio_init(PIN_PUSH_BUTTON, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);

    // Read the logic level on the input pin
    //read_val = cyhal_gpio_read(PIN_PUSH_BUTTON);

}


/** Initialize the push button on the ECE453 MCU Dev Board
 *  to generate interrupts
 *
 * @param
 *
 */
void push_button_init(void)
{
	push_button_io_init();
	push_button_irq_init();
}
