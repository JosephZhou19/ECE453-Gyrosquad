/*
 */

#ifndef SPI_H__
#define SPI_H__

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

/* Macros */
#define PIN_MCU_SPI_MOSI	P9_0
#define PIN_MCU_SPI_MISO	P9_1
#define PIN_MCU_SPI_CLK		P9_2

#define SPI_FREQ			1000000

/* Public Global Variables */
extern cyhal_spi_t mSPI;
extern cy_rslt_t   rslt;



/* Public API */
cy_rslt_t spi_init(void);

#endif 
