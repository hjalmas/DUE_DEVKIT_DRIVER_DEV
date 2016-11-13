/*
 * pio_driver.h
 *
 *  Created on: Nov 8, 2016
 *      Author: Albin
 */

#ifndef INCLUDE_PIO_DRIVER_H_
#define INCLUDE_PIO_DRIVER_H_

/* Includes ---------------------------------------------*/
#include <stdio.h>
#include <limits.h>
#include "diag/Trace.h"
#include "cmsis_device.h"
#include "sam3x_conf.h"

/* Defines ----------------------------------------------*/

/* PIO failure code */
#define PIO_ERROR UINT_MAX

/* PIO settings */
#define PIO_INPUT 				1 << 0		/* Configure pin as input */
#define PIO_OUTPUT				1 << 1		/* Configure pin as output */
#define PIO_PULLUP				1 << 2		/* Use pullup */

/* PIO interrupt settings */
#define INT_EDG_FALLING 		1 << 0 		/* Falling edge detection */
#define INT_EDG_RISING			1 << 1		/* Rising edge detection */
#define INT_LVL_HIGH			1 << 2		/* High level detection */
#define INT_LVL_LOW				1 << 3		/* Low level detection */

/* Prototypes -------------------------------------------*/

/**
 * Configures the specified pin on the specified port according
 * to the specified settings.
 * This function can initiate multiple pins on the same port at once.
 */
void pio_init_pin(Pio* PIO, uint32_t PIN, uint32_t Settings);

/**
 * Configures the specified interrupt modes on the specified pin.
 * NOTE: you have to run "pio_init_pin()" before running this function.
 */
void pio_init_interrupt(Pio* PIO, uint32_t PIN, uint32_t Settings);

/**
 * Configures debounce on the specified pin with the specified
 * amount of debounce time (measured in ms).
 */
void pio_init_debounce(Pio* PIO, uint32_t PIN, uint32_t time_ms);

/**
 * Sets the pin (if configured as output) to the specified level (1 or 0).
 */
void pio_set_pin(Pio* PIO, uint32_t PIN, uint32_t state);

/**
 * Toggles the pin (if configured as output).
 */
void pio_toggle_pin(Pio* PIO, uint32_t PIN);

/**
 * Returns the peripheral ID of the specified Pio instance.
 * If the id is not found or something else goes wrong, this method
 * will return PIO_ERROR.
 */
uint32_t pio_getID(Pio* PIO);


#endif /* INCLUDE_PIO_DRIVER_H_ */
