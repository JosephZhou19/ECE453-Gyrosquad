/*
 * eeprom.h
 *
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdio.h>
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "spi.h"

//active low
#define EEPROM_CS_PIN					P7_1

#define EEPROM_CMD_WREN					0x06
#define EEPROM_CMD_WRDI					0x04
#define EEPROM_CMD_RDSR					0x05
#define EEPROM_CMD_WRSR					0x01
#define EEPROM_CMD_READ					0x03
#define EEPROM_CMD_WRITE				0x02
#define EEPROM_CMD_RDID					0x83
#define EEPROM_CMD_WRID					0x82
#define EEPROM_CMD_RDLS					0x83
#define EEPROM_CMD_LID 					0x82

/** Initializes the IO pins used to control the CS of the
 *  EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_cs_init(void);

/** Determine if the EEPROM is busy writing the last
 *  transaction to non-volatile storage
 *
 * @param
 *
 */
cy_rslt_t eeprom_wait_for_write(void);

/** Enables Writes to the EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_write_enable(void);

/** Disable Writes to the EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_write_disable(void);


/** Writes a single byte to the specified address
 *
 * @param address -- 16 bit address in the EEPROM
 * @param data    -- value to write into memory
 *
 */
cy_rslt_t eeprom_write_byte(uint16_t address, uint8_t data);

/** Reads a single byte to the specified address
 *
 * @param address -- 16 bit address in the EEPROM
 * @param data    -- value read from memory
 *
 */
cy_rslt_t eeprom_read_byte(uint16_t address, uint8_t *data);

/** Tests Writing and Reading the EEPROM
 *
 * @param
 *
 */
cy_rslt_t eeprom_test(void);

#endif /* EEPROM_H_ */
