/*
 *
 *  Created on: 3/23/2023
 *      Author: Joseph Zhou
 */

#include <servo.h>
	cyhal_pwm_t servo_pwm_obj;
/**Send PWM to servo for specified time
 * @param
 *  freq: frequency to send to motor, range is 400 to 2000
 *  time: pwm output time in ms
 */
void servo_run(uint32_t freq, uint32_t time)
{
	// Set a duty cycle of 50% and frequency of 1Hz
	rslt = cyhal_pwm_set_duty_cycle(&servo_pwm_obj, 50, freq);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	// start the PWM output
	rslt = cyhal_pwm_start(&servo_pwm_obj);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}

	// Delay for observing the output
	cyhal_system_delay_ms(time);

	// Stop the PWM output
	rslt = cyhal_pwm_stop(&servo_pwm_obj);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
}
/** Initialize the GPIO pins for the stepper driver
 *
 * @param
 *
 */
void servo_init(void)
{
	cy_rslt_t   rslt;


	// Initialize PWM on the supplied pin and assign a new clock
	rslt = cyhal_pwm_init(&servo_pwm_obj, SERVO_SIG, NULL);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	// Set a duty cycle of 50% and frequency of 1Hz
	rslt = cyhal_pwm_set_duty_cycle(&servo_pwm_obj, 50, 1000000);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	// Start the PWM output
	rslt = cyhal_pwm_start(&servo_pwm_obj);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
}
