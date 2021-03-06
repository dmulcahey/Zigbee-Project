/** @file hal/micro/spi.h
 * @brief Generic SPI manipulation routines.
 *
 * See @ref spi for documentation.
 *
 * <!-- Copyright 2008 by Ember Corporation. All rights reserved.        *80*-->
 */

/** @addtogroup spi
 *
 * This file contains the prototypes and defines for direct SPI access.
 * These functions are generic.
 *
 * See spi.h for source code.
 *
 * These functions are suitable for use by any module, but are entirely
 * dependent upon appropriate sharing of the SPI bus through chip selects
 * and hold lines.
 *
 * Some functions in this file return an ::EmberStatus value. See
 * error-def.h for definitions of all ::EmberStatus return values.
 *
 *@{
 */

#ifndef __SPI_H__
#define __SPI_H__

/**
 * @brief Configures the relavent pins and initializes the USART0 module
 * for operation at 8-bits, master mode, 3-pin, maximum speed (2MHz).
 */
void halCommonInitSpi(void);

/**
 * @brief Writes a byte over the SPI.
 *
 * @param dataByte  The byte to be sent out over the SPI.
 */
void halCommonSpiWrite(int8u dataByte);

/**
 * @brief Reads a byte over the SPI without changing the mode.
 *
 * @return The byte read.
 */
int8u halCommonSpiRead(void);

/**
 * @brief Reads and writes a byte over the SPI.
 *
 * @param dataByte  The byte to be sent out over the SPI.
 *
 * @return The byte read.
 */
int8u halCommonSpiReadWrite(int8u dataByte);

#endif //__SPI_H__

/** @} END addtogroup */

