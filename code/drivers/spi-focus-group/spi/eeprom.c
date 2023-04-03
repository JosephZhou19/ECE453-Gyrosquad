/*
 * eeprom.c
 *
 */

#include "eeprom.h"

/** Initializes the IO pins used to control the CS of the
 *  EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_cs_init(void)
{
    return cyhal_gpio_init(EEPROM_CS_PIN, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, true);
}

/** Determine if the EEPROM is busy writing the last
 *  transaction to non-volatile storage
 *
 * @param
 *
 */
cy_rslt_t eeprom_wait_for_write(void)
{
	uint8_t *data;
	cyhal_gpio_write(EEPROM_CS_PIN, 0);

		// send instruction to read from the status register
		if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, EEPROM_CMD_RDSR))
		{
			// receive data (status register)
			if (CY_RSLT_SUCCESS == cyhal_spi_recv(&mSPI, data)){

				// actually get the status out of the recieved data
				//least sig bit is 1 if the device is busy
				while ((*data & 0x01) == 0x01){
					printf("spin!!\n");
					// wait while device is busy
					if (CY_RSLT_SUCCESS == cyhal_spi_recv(&mSPI, data)){}
				}
				return CY_RSLT_SUCCESS;
			}

		}
		//opsies something bad happend
		return 0;

}

/** Enables Writes to the EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_write_enable(void)
{
	cyhal_gpio_write(EEPROM_CS_PIN, 0);
	if (CY_RSLT_SUCCESS == eeprom_wait_for_write()) {
	    if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, EEPROM_CMD_WREN)){
	    	cyhal_gpio_write(EEPROM_CS_PIN, 1);
	    	return CY_RSLT_SUCCESS;

	    }
	}
	return 0;
}

/** Disable Writes to the EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_write_disable(void)
{
	cyhal_gpio_write(EEPROM_CS_PIN, 0);
	if (CY_RSLT_SUCCESS == eeprom_wait_for_write()) {
	    if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, EEPROM_CMD_WRDI)){
	    	cyhal_gpio_write(EEPROM_CS_PIN, 1);
	    	return CY_RSLT_SUCCESS;
	    }
	}
	return 0;
}


/** Writes a single byte to the specified address
 *
 * @param address -- 16 bit address in the EEPROM
 * @param data    -- value to write into memory
 *
 */
cy_rslt_t eeprom_write_byte(uint16_t address, uint8_t data)
{
	// write enable
	if (CY_RSLT_SUCCESS == eeprom_write_enable()){
		cyhal_gpio_write(EEPROM_CS_PIN, 0);

			// send instruction
			if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, EEPROM_CMD_WRITE)) {

				// send address MSB
				if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, (address>>8))) {

					// send address LSB
					if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, (address & 0x0f))){

						// send data
						if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, data)){

							// disable CS
							cyhal_gpio_write(EEPROM_CS_PIN, 1);
					    	return CY_RSLT_SUCCESS;

						}
					}
				}
			}
	}
	return 0;

}

/** Reads a single byte from the specified address
 *
 * @param address -- 16 bit address in the EEPROM
 * @param data    -- value read from memory
 *
 */
cy_rslt_t eeprom_read_byte(uint16_t address, uint8_t *data)
{
	cyhal_gpio_write(EEPROM_CS_PIN, 0);

		// send instruction
		if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, EEPROM_CMD_READ))
		{
			// send address MSB
			if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, (address>>8))){

				// send address LSB
				if (CY_RSLT_SUCCESS == cyhal_spi_send(&mSPI, (address & 0x0f))){

					// receive data
					if (CY_RSLT_SUCCESS == cyhal_spi_recv(&mSPI, data)){

						// disable CS
						cyhal_gpio_write(EEPROM_CS_PIN, 1);
						return CY_RSLT_SUCCESS;
					}
				}
			}
		}
		return 0;

}


/** Tests Writing and Reading the EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_test(void)
{
	printf("entering the TEST!\n");
	uint8_t i;
	uint16_t addr;
	cy_rslt_t   rslt;
	uint8_t data;
	uint8_t expected_data;

	// Write the data to the eeprom.
	addr = 0x20;
	data = 0x10;
	for(i = 0; i < 20; i++)
	{
		rslt = eeprom_write_byte(addr, data);
		if(rslt != CY_RSLT_SUCCESS)
		{
			printf("* -- EEPROM WRITE FAILURE\n\r");
			return -1;
		}
		addr++;
		data++;
	}

	// Read the data back and verify everything matches what was written
	addr = 0x20;
	expected_data = 0x10;
	for(i = 0; i < 20; i++)
	{
		rslt = eeprom_read_byte(addr, &data);
		if(rslt != CY_RSLT_SUCCESS)
		{
			printf("* -- EEPROM READ FAILURE\n\r");
			return -1;
		}
		if(expected_data != data)
		{
			printf("* -- EEPROM READ DATA DOES NOT MATCH\n\r");
			return -1;
		}

		addr++;
		expected_data++;
	}
	printf("* -- EEPROM Test Passed\n\r");
	return CY_RSLT_SUCCESS;
}
