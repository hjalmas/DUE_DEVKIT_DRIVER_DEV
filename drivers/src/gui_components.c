/*
 * gui_components.c
 *
 *  Created on: Nov 14, 2016
 *      Author: root
 */

/**
 * -----------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * -----------------------------------------------------------------------------------------------------
 */
#include "../inc/gui_components.h"

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

/**
 * -----------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * -----------------------------------------------------------------------------------------------------
 */
static print_TextField(TextField_t* txtField);
/**
 * -----------------------------------------------------------------------------------------------------
 * 												Declarations
 * -----------------------------------------------------------------------------------------------------
 */

/**
 * Initializes a TextField.
 */
void gui_TextField_init(TextField_t* result, char* initText, uint32_t row, /* Row of the first character */
uint32_t col, /* column of the first character, defines location for the TextField */
uint32_t width, /* width in terms of characters */
uint32_t height, /* height in terms of characters */
void (*cbTextField)(void) /* Callback function for this TextField */
) {
	strcpy(result->text, initText);
	result->row = row;
	result->col = col;
	result->width = width;
	result->height = height;
	result->isSelected = false;
	result->cbTextField = cbTextField;
}

/**
 * Select textField.
 */
void gui_TextField_select(TextField_t* txtField) {
	if (selectedTextField != NULL) {
		selectedTextField->isSelected = false;
		selectedTextField = txtField;
		txtField->isSelected = true;
		gui_TextField_show(txtField); /* Redraw textfield and highlight edges */
	} else {
		selectedTextField = txtField;
		txtField->isSelected = true;
	}
}

/**
 * Shows the specified TextField on the screen.
 */
void gui_TextField_show(TextField_t* txtField) {
	volatile uint16_t rectWidth = (txtField->width + 1) * 6 + 3;
	volatile uint16_t x0 = (txtField->col - 1) * 6 - 1, y0 = (txtField->row - 1)
			* 8 - 2;
	graph_draw_rect(x0, y0, rectWidth, 11);
	print_TextField(txtField);
}

/**
 * Handles a keypress.
 */
void gui_handle_keypress(char ch) {

	TextField_t* f = selectedTextField;
	size_t length = strlen(f->text);

	/* if a carrriage return (enter key) is detected, then run handler */
	if (ch == 0x0D && f != NULL) {
		f->cbTextField();
		return;
		/* If a backspace key was pressed */
	} else if (ch == 0x08 && length > 0 && f != NULL) {
		f->text[length - 1] = '\0';
		print_TextField(f);
		/* just a normal keypress */
	} else if (f != NULL) {
		f->text[length] = ch;
		f->text[length + 1] = '\0';
		print_TextField(f);
	}
}

/**
 * Prints the text in a TextField
 */
static print_TextField(TextField_t* txtField) {

	TextField_t* f = txtField;
	size_t length = strlen(f->text);

	if (length > f->width) {
		graph_print_text(f->text + length - f->width, (uint8_t) f->row,
				(uint8_t) f->col, TEXT_ALIGN_LEFT);
	} else if (length >= 0) {
		graph_print_text(f->text, (uint8_t) f->row, (uint8_t) f->col,
				TEXT_ALIGN_LEFT);
		for (int i = 0; i < f->width - length; i++) {
			disp_wr_byte(DATA_WR_INC_ADP, 0x00);
		}
		for (int i = 0; i < f->width - length; i++) {
			disp_wr_byte(DATA_WR_DEC_ADP, 0x00);
		}

	}
}

