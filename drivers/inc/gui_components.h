/*
 * gui_components.h
 *
 *  Created on: Nov 14, 2016
 *      Author: root
 */

#ifndef GUI_COMPONENTS_H_
#define GUI_COMPONENTS_H_


/**
 * -----------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * -----------------------------------------------------------------------------------------------------
 */
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cmsis_device.h"
#include "sam3x_conf.h"

#include "display_driver.h"
#include "graphic_driver.h"

/**
 * -----------------------------------------------------------------------------------------------------
 * 												DEFINES
 * -----------------------------------------------------------------------------------------------------
 */

/**
 * -----------------------------------------------------------------------------------------------------
 * 												TYPEDEFS, variables
 * -----------------------------------------------------------------------------------------------------
 */
typedef struct TextField {
	char text[40];				/* The text contained within this TextField_t instance. */
	uint32_t row;				/* Row of the first character */
	uint32_t col;				/* column of the first character, defines location for the TextField */
	uint32_t width;				/* width in terms of characters */
	uint32_t height;			/* height in terms of characters */
	bool isSelected;			/* true if this TextField is selected */
	void (*cbTextField)(void);	/* Callback function for this TextField */
} TextField_t;

TextField_t* selectedTextField; /* the currently selected TextField */

/**
 * -----------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * -----------------------------------------------------------------------------------------------------
 */

/**
 * Creates a TextField.
 */
void gui_TextField_init(
		TextField_t* result,
		char* initText,
		uint32_t row,				/* Row of the first character */
		uint32_t col,				/* column of the first character, defines location for the TextField */
		uint32_t width,				/* width in terms of characters */
		uint32_t height,			/* height in terms of characters */
		void (*cbTextField)(void)   /* Callback function for this TextField */
);

/**
 * Select textField.
 */
void gui_TextField_select(TextField_t* txtField);

/**
 * Shows the specified TextField on the screen.
 */
void gui_TextField_show(TextField_t* txtField);

/**
 * Handles a keypress.
 */
void gui_handle_keypress(char ch);


#endif /* GUI_COMPONENTS_H_ */
