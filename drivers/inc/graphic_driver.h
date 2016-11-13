/*
 * graphic_driver.h
 *
 *  Created on: Nov 11, 2016
 *      Author: Albin Hjälmås
 */

#ifndef GRAPHIC_DRIVER_H_
#define GRAPHIC_DRIVER_H_

/* Includes -------------------------------------------------------------------------*/
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "diag/Trace.h"
#include "cmsis_device.h"
#include "sam3x_conf.h"

#include "pio_driver.h"
#include "display_driver.h"

/* Defines ---------------------------------------------------------------------------*/

/* Text alignment relative to screen boundary */
#define TEXT_ALIGN_LEFT			0x00
#define TEXT_ALIGN_CENTER		0x01
#define TEXT_ALIGN_RIGHT		0x02


/* Prototypes ------------------------------------------------------------------------*/

/**
 * prints text on the specified location on the screen.
 */
void graph_print_text(char* txt, uint8_t row, uint8_t col, uint8_t TEXT_ALIGN);

/**
 * prints text in a box on the specified location on the screen.
 * Only single-line text.
 */
void graph_print_textBox(char* txt, uint8_t row, uint8_t col, uint8_t TEXT_ALIGN);

/**
 * Draws a pixel at the specified location on the screen;
 */
void graph_draw_pixel(uint16_t x, uint16_t y);

/**
 * Draws a line between (x0, y0) and (x1, y1) on the display.
 */
void graph_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/**
 * Draws a rectangle with (x0, y0) in the upper left corner.
 */
void graph_draw_rect(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height);

#endif /* GRAPHIC_DRIVER_H_ */
