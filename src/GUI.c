/*
 * GUI.c
 *
 *  Created on: Nov 18, 2016
 *      Author: root
 */
/**
 * -----------------------------------------------------------------------------------------------------
 * 												INCLUDES
 * -----------------------------------------------------------------------------------------------------
 */
#include "main.h"
/**
 * -----------------------------------------------------------------------------------------------------
 * 												DEFINES
 * -----------------------------------------------------------------------------------------------------
 */
#define MAIN_MENU 0
#define LIVE_WEATHER 1

/**
 * -----------------------------------------------------------------------------------------------------
 * 												TYPEDEFS, variables
 * -----------------------------------------------------------------------------------------------------
 */

static uint32_t currPage = MAIN_MENU;

/* Main menu components -----------*/
Button_t menuLiveWatherDataBtn;
Button_t menuItem2Btn;
Button_t menuItem3Btn;
Button_t menuSettingsBtn;
void* componentsMM[] = {
		&menuLiveWatherDataBtn,
		&menuItem2Btn,
		&menuItem3Btn,
		&menuSettingsBtn,
};
uint32_t menuIdx = 0;

/* Page 1 components --------------*/
TextField_t tempTxtField;
TextField_t txtField2;
TextField_t txtField3;
TextField_t txtField4;
Button_t returnButton;

/**
 * -----------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * -----------------------------------------------------------------------------------------------------
 */
void gui_init(void);
void cbKeyPress(void);
void cbTempSensor(void);

void showMainMenu(void);
void showLiveWeatherData(void);

/* Main menu callbacks ----------*/
void cbMenuLiveWeatherDataBtn(void);
void cbMenuItem2Btn(void);
void cbMenuItem3Btn(void);
void cbMenuSettingsBtn(void);

/* Live weather data Callbacks -------------*/
void cbReturnButton(void);

/* Private functions -----------------------*/
static void degCelsius(uint16_t row, uint16_t col);

/**
 * -----------------------------------------------------------------------------------------------------
 * 												DECLARATIONS
 * -----------------------------------------------------------------------------------------------------
 */

void gui_init(void) {

	/* Initialize main menu components */
	gui_Button_init(&menuLiveWatherDataBtn,"Live Weather Data", 7, 10, 20, cbMenuLiveWeatherDataBtn);
	gui_Button_init(&menuItem2Btn,"Page 2", 9, 10, 20, cbMenuItem2Btn);
	gui_Button_init(&menuItem3Btn,"Page 3", 11, 10, 20, cbMenuItem3Btn);
	gui_Button_init(&menuSettingsBtn,"Settings", 13, 10, 20, cbMenuSettingsBtn);

	/* Initialize Live weather data components */
	gui_TextField_init(&tempTxtField, "", 6, 25, 6, NULL);
	gui_TextField_init(&txtField2, "", 8, 25, 6, NULL);
	gui_TextField_init(&txtField3, "", 10, 25, 6, NULL);
	gui_TextField_init(&txtField4, "", 12, 25, 6, NULL);
	gui_Button_init(&returnButton,"Return To Main Menu", 14, 9, 22, cbReturnButton);

	showMainMenu();
}

/**
 * Display the main menu on the screen.
 */
void showMainMenu(void) {
	currPage = MAIN_MENU;
	disp_full_clear();
	graph_draw_rect(0, 0, 240, 128, true);
	graph_draw_rect(2, 2, 236, 124, true);
	graph_draw_rect(40, 16, 155, 96, true);
	graph_draw_rect(38, 14, 159, 100, true);
	graph_print_textBox("~Main Menu~", 4, 1, TEXT_ALIGN_CENTER);
	gui_Button_show(&menuLiveWatherDataBtn);
	gui_Button_show(&menuItem2Btn);
	gui_Button_show(&menuItem3Btn);
	gui_Button_show(&menuSettingsBtn);
	gui_select_component(&menuLiveWatherDataBtn);
}

/**
 * Display page 1 on the screen.
 */
void showLiveWeatherData(void) {
	currPage = LIVE_WEATHER;
	disp_full_clear();
	graph_draw_rect(0, 0, 240, 128, true);
	graph_draw_rect(2, 2, 236, 124, true);
	graph_print_textBox("~Live Weather Data~", 3, 1, TEXT_ALIGN_CENTER);
	graph_print_text("Temperature: ", 6, 9, TEXT_ALIGN_LEFT);
	gui_TextField_show(&tempTxtField);
	graph_print_text("Air Pressure: ", 8, 9, TEXT_ALIGN_LEFT);
	gui_TextField_show(&txtField2);
	gui_TextField_show(&txtField3);
	gui_TextField_show(&txtField4);
	gui_Button_show(&returnButton);
	gui_select_component(&returnButton);
}

void cbKeyPress(void) {
	volatile uint32_t key = kpad_get_key();

	switch (key) {
	case KEY_0:
		gui_handle_keypress('0');
		break;
	case KEY_1:
		gui_handle_keypress('1');
		break;
	case KEY_2:
		gui_handle_keypress('2');
		break;
	case KEY_3:
		gui_handle_keypress('3');
		break;
	case KEY_4:
		gui_handle_keypress('4');
		break;
	case KEY_5:
		gui_handle_keypress('5');
		break;
	case KEY_6:
		gui_handle_keypress('6');
		break;
	case KEY_7:
		gui_handle_keypress('7');
		break;
	case KEY_8:
		gui_handle_keypress('8');
		break;
	case KEY_9:
		gui_handle_keypress('9');
		break;
	case KEY_A:

		if(currPage == MAIN_MENU) {
			menuIdx == 0 ? menuIdx = 3 : menuIdx--;
			gui_select_component(componentsMM[menuIdx]);
	 	}

		break;
	case KEY_B:

		if(currPage == MAIN_MENU) {
			menuIdx == 3 ? menuIdx = 0 : menuIdx++;
			gui_select_component(componentsMM[menuIdx]);
		}

		break;
	case KEY_C:
		gui_handle_keypress(0x08);
		break;
	case KEY_D:
		gui_handle_keypress(0x0D);
		break;
	default:
		break;

	}
}

void cbTempSensor(void) {
	if(currPage != LIVE_WEATHER) {
		return;
	}

	volatile uint32_t val = temp_read();
	char* str = malloc(12);
	sprintf(str, "%d.%d", val/100, val%100);
	if(strlen(str) < 5) {
		strcat(str, "0");
	}
	gui_TextField_setText(&tempTxtField, str);
	degCelsius(tempTxtField.row, tempTxtField.col + 5);

	free(str);
}

/**
 * -----------------------------------------------------------------------------------------------------
 * 												CALLBACK FUNCTIONS
 * -----------------------------------------------------------------------------------------------------
 */

/* Main menu callbacks ---------------------*/

void cbMenuLiveWeatherDataBtn(void) {
	gui_select_component(&returnButton);
	showLiveWeatherData();
}

void cbMenuItem2Btn(void) {

}

void cbMenuItem3Btn(void) {

}

void cbMenuSettingsBtn(void) {

}

/* Page 1 callbacks ------------------------*/

void cbReturnButton(void) {
	gui_select_component(&menuLiveWatherDataBtn);
	showMainMenu();
}

/**
 * -----------------------------------------------------------------------------------------------------
 * 												PRIVATE FUNCTIONS
 * -----------------------------------------------------------------------------------------------------
 */
static void degCelsius(uint16_t row, uint16_t col) {
	graph_print_text("C", row, col+1, TEXT_ALIGN_LEFT);
	volatile uint16_t x0 = 0, y0 = 0;
	y0 = 8 * (row-1) + 1;
	x0 = 6 * (col-1) + 4;
	graph_draw_circle(x0, y0, 2, true);
}
