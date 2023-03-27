/*
 *
 *  Created on: 3/23/2023
 *      Author: Joseph Zhou
 */

#include <stepper.h>

volatile bool ALERT_STEPPER_HOMEN = false;

/* IO Pin Handler Struct */
cyhal_gpio_callback_data_t stepper_homen_cb_data =
{
    .callback     = stepper_homen_handler,
    .callback_arg = (void*)NULL
};
/**
 * Motor moves one step based on parameters
 *
 * @param
 * bool dir: direction of motor
 * bool usm0, usm1: 00 for full step, 01 for half, 10 for quarter, 11 for 1/8
 */
void stepper_step(bool dir, bool usm0, bool usm1){
	cyhal_gpio_write(STEPPER_DIR, dir);
	cyhal_gpio_write(STEPPER_USM0, usm0);
	cyhal_gpio_write(STEPPER_USM1, usm1);
	cyhal_gpio_write(STEPPER_STEP, true);
	cyhal_gpio_write(STEPPER_STEP, false);
}
/** IRQ handler for Stepper Home state
 *
 * @param
 *
 */
void stepper_homen_handler(void* handler_arg, cyhal_gpio_event_t event)
{
	ALERT_STEPPER_HOMEN= true;
    /* Toggle LED401 when an interrupt has been detected */
	cyhal_gpio_write(STEPPER_RESETN, true);
}

/** Configure STEPPER_HOMEN to generate an interrupt when the homen is low
 *
 * @param
 *
 */
static void stepper_homen_irq_init(void)
{
	/* You will need to examine the HAL API to determine how to
	 * register a callback function when an interrupt has been detected
	 */
	cyhal_gpio_register_callback(STEPPER_HOMEN, &stepper_homen_cb_data);
	/* You will need to examine the HAL API to enable falling edge event to
	 * generate an interrupt
	 */
	cyhal_gpio_enable_event(STEPPER_HOMEN, CYHAL_GPIO_IRQ_FALL, 3, true);
}
/** Resets stepper to home state. Checks to make sure stepper isn't already in home state.
 *
 * @param
 */
void stepper_reset(void){
	bool      read_val;
	read_val = cyhal_gpio_read(STEPPER_HOMEN);
	if(read_val){
		ALERT_STEPPER_HOMEN= false;
		cyhal_gpio_write(STEPPER_RESETN, false);
	}
}
/** Initialize the GPIO pins for the stepper driver
 *
 * @param
 *
 */
void stepper_init(void)
{
	/* Initialize stepper motor driver DRV8811PWP
	 */
	cy_rslt_t rslt;
	bool      write_val = true;

	// Initialize pin PIN_USER_LED GPIO as an output with strong drive mode and initial value = false (low)
	rslt = cyhal_gpio_init(STEPPER_ENABLEN, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_SLEEPN, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_STEP, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_DIR, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_USM0, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_USM1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_RESETN, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_SRN, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	rslt = cyhal_gpio_init(STEPPER_HOMEN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}

	cyhal_gpio_write(STEPPER_RESETN, false);
	cyhal_gpio_write(STEPPER_ENABLEN, false);
	cyhal_gpio_write(STEPPER_SLEEPN, true);
	cyhal_gpio_write(STEPPER_STEP, false);
	cyhal_gpio_write(STEPPER_DIR, true);
	cyhal_gpio_write(STEPPER_SRN, false);
	cyhal_gpio_write(STEPPER_USM0, false);
	cyhal_gpio_write(STEPPER_USM1, false);

	stepper_homen_irq_init();
}
