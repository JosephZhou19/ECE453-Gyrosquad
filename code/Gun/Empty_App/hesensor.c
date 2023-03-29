#include <hesensor.h>

volatile bool ALERT_HESENSOR_SIG = false;

/* IO Pin Handler Struct */
cyhal_gpio_callback_data_t hesensor_sig_cb_data =
{
    .callback     = hesensor_sig_handler,
    .callback_arg = (void*)NULL
};
/** IRQ handler for hall effect sensor signal
 *
 * @param
 *
 */
void hesensor_sig_handler(void* handler_arg, cyhal_gpio_event_t event)
{
	bool      read_val;
	read_val = cyhal_gpio_read(HESENSOR_SIG);
	ALERT_HESENSOR_SIG= read_val;
}
/** Configure STEPPER_HOMEN to generate an interrupt when the homen is low
 *
 * @param
 *
 */
static void hesensor_sig_irq_init(void)
{
	/* You will need to examine the HAL API to determine how to
	 * register a callback function when an interrupt has been detected
	 */
	cyhal_gpio_register_callback(HESENSOR_SIG, &hesensor_sig_cb_data);
	/* You will need to examine the HAL API to enable falling edge event to
	 * generate an interrupt
	 */
	cyhal_gpio_enable_event(HESENSOR_SIG, CYHAL_GPIO_IRQ_BOTH, 3, true);
}

void hesensor_init(void)
{
	cy_rslt_t   rslt;
	rslt = cyhal_gpio_init(HESENSOR_SIG, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
	if(rslt != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(rslt == CY_RSLT_SUCCESS);
	}
	hesensor_sig_irq_init();
}
