/*
 * graphic_driver.c
 *
 *  Created on: Nov 11, 2016
 *      Author: Albin Hjälmås
 */

/* Includes -------------------------------------------------------------------------------------------*/
#include "../drivers/inc/graphic_driver.h"

/* Private definitions --------------------------------------------------------------------------------*/

/* Private prototypes ---------------------------------------------------------------------------------*/

/* Private variables ----------------------------------------------------------------------------------*/

/* Extern variables -----------------------------------------------------------------------------------*/
extern uint16_t currTxtFrame;
extern uint16_t currGraphFrame;
extern uint16_t currFrame;

/* Declarations ---------------------------------------------------------------------------------------*/

/**
 * prints text on the specified location on the screen.
 */
void graph_print_text(char* txt, uint8_t row, uint8_t col, uint8_t TEXT_ALIGN) {

	volatile uint16_t nCol = col;
	volatile uint16_t txtLength = (uint16_t) strlen(txt);

	/* Set text alignment */
	switch (TEXT_ALIGN) {
	case TEXT_ALIGN_CENTER:
		nCol = 20 - txtLength / 2;
		break;
	case TEXT_ALIGN_RIGHT:
		nCol = 41 - col - txtLength;
		break;
	}

	volatile uint16_t startAddress = currTxtFrame
			+ (uint16_t) (40 * row + nCol - 41);
	disp_wr_hword(SET_ADDRESS_PIONTER, startAddress);
	for (unsigned int i = 0; i < txtLength; i++) {
		disp_wr_byte(DATA_WR_INC_ADP, a2dispTxt(txt[i]));
	}
}

/**
 * prints text in a box on the specified location on the screen.
 * Only single-line text.
 */
void graph_print_textBox(char* txt, uint8_t row, uint8_t col,
		uint8_t TEXT_ALIGN) {

	volatile uint16_t nCol = col;
	volatile uint16_t txtLength = (uint16_t) strlen(txt);

	/* Set text alignment */
	switch (TEXT_ALIGN) {
	case TEXT_ALIGN_CENTER:
		nCol = 20 - txtLength / 2;
		break;
	case TEXT_ALIGN_RIGHT:
		nCol = 41 - col - txtLength;
		break;
	}

	volatile uint16_t rectWidth = txtLength * 6 + 3;
	volatile uint16_t x0 = (nCol - 1) * 6 - 1, y0 = (row - 1) * 8 - 2;
	graph_draw_rect(x0, y0, rectWidth, 11);
	graph_print_text(txt, row, col, TEXT_ALIGN);
}

/**
 * Clears 1 character on the display.
 */
void graph_clear_char(uint8_t row, uint8_t col) {
	volatile uint16_t startAddress = currTxtFrame
			+ (uint16_t) (40 * row + col - 41);
	disp_wr_hword(SET_ADDRESS_PIONTER, startAddress);
	disp_wr_byte(DATA_WR_DEC_ADP, 0);
}

/**
 * Draws a pixel at the specified location on the screen;
 */
void graph_draw_pixel(uint16_t x, uint16_t y) {
	volatile uint16_t address = currGraphFrame + x / 6 + y * 40;
	disp_wr_hword(SET_ADDRESS_PIONTER, address);
	volatile uint8_t currData = disp_rd_byte(DATA_RD);
	disp_wr_byte(DATA_WR, (0x20 >> (x % 6)) | currData);
}

/**
 * Draws a line between (x0, y0) and (x1, y1) on the display.
 */
void graph_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	volatile int32_t dx = (int32_t) (x1 - x0), dy = (int32_t) (y1 - y0);
	volatile int32_t threshold = 0;
	volatile int32_t slope = abs((dy * 100000) / dx);
	volatile uint16_t y = 0, x = 0, xLim = abs(x1 - x0), yLim = abs(y1 - y0);

	/* Just an orthogonal line */
	if (dx == 0) {
		for (; y <= yLim; y++) {

			if (dy > 0) {
				graph_draw_pixel(x0, y0 + y);
			} else {
				graph_draw_pixel(x0, y0 - y);
			}

		}
		return;
	} else if (dy == 0) {
		for (; x <= xLim; x++) {

			if (dx > 0) {
				graph_draw_pixel(x0 + x, y0);
			} else {
				graph_draw_pixel(x0 - x, y0);
			}

		}
		return;
	}

	if (slope <= 100000) { /* First octant */

		for (; x <= xLim; x++) {

			if (dx > 0 && dy > 0) {
				graph_draw_pixel(x0 + x, y0 + y);
			} else if (dx < 0 && dy > 0) {
				graph_draw_pixel(x0 - x, y0 + y);
			} else if (dx < 0 && dy < 0) {
				graph_draw_pixel(x0 - x, y0 - y);
			} else {
				graph_draw_pixel(x0 + x, y0 - y);
			}

			threshold += slope;
			if (threshold >= 100000) {
				y++;
				threshold -= 100000;
			}
		}

	} else if (slope > 100000) { /* Second octant */

		slope = abs((dx * 100000) / dy);
		for (; y <= yLim; y++) {

			if (dx > 0 && dy > 0) {
				graph_draw_pixel(x0 + x, y0 + y);
			} else if (dx < 0 && dy > 0) {
				graph_draw_pixel(x0 - x, y0 + y);
			} else if (dx < 0 && dy < 0) {
				graph_draw_pixel(x0 - x, y0 - y);
			} else {
				graph_draw_pixel(x0 + x, y0 - y);
			}

			threshold += slope;
			if (threshold >= 100000) {
				x++;
				threshold -= 100000;
			}
		}

	}
}

/**
 * Draws a rectangle with (x0, y0) in the upper left corner.
 */
void graph_draw_rect(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height) {

	volatile uint16_t x1 = x0 + width - 1, y1 = y0 + height - 1;
	graph_draw_line(x0, y0, x0, y1);
	graph_draw_line(x0, y1, x1, y1);
	graph_draw_line(x1, y1, x1, y0);
	graph_draw_line(x0, y0, x1, y0);
}

/**
 * Converts from ascii to display text.
 */
uint8_t a2dispTxt(char ascii) {
	volatile uint8_t result = ascii - 0x20;
	return result;
}

/* Private functions ----------------------------------------------------------------------------------*/
