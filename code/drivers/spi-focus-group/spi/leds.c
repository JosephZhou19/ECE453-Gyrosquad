/*
 * ece453.c
 *
 *  Created on: Jan 18, 2022
 *      Author: Joe Krachey
 */

#include <leds.h>
#include <stdio.h>

cy_rslt_t rslt;

/** Initialize the LED on the ECE453 MCU Dev Board
 *
 * @param
 *
 */
void leds_init(void)
{
	/* Initialize LED401.  You will need to examine the HAL API to determine how to
	 * initialize an IO pin an output
	 */
    //bool write_val = true;

    // Initialize pin P5_5 GPIO as an output with strong drive mode and initial value = false (low)
    rslt = cyhal_gpio_init(PIN_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);

    // Write the value to the output pin
    /*if(CY_RSLT_SUCCESS == rslt){
           cyhal_gpio_write(PIN_USER_LED, 1);
           cyhal_system_delay_ms(5000);
           cyhal_gpio_write(PIN_USER_LED, 0);

    }*/



    //    while(1){
//        cyhal_gpio_write(PIN_USER_LED, 0);
//        cyhal_system_delay_ms(1000);
//        cyhal_gpio_write(PIN_USER_LED, 1);
//        cyhal_system_delay_ms(1000);
//    }

}



