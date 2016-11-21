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

/* Live wather data page components --------------*/
TextField_t tempTxtField;
TextField_t presTxtField;
TextField_t txtField3;
TextField_t txtField4;
Button_t returnButton;

/**
 * -----------------------------------------------------------------------------------------------------
 * 												PROTOTYPES
 * -----------------------------------------------------------------------------------------------------
 */
/* GUI functions ----------------*/
void gui_init(void);
void showMainMenu(void);
void showLiveWeatherData(void);
void showErrorPage(char** messages);

/* Peripheral callback functions-*/
void cbKeyPress(void);
void cbTempSensor(void);
void cbBarometer(void);

/* Main menu callbacks ----------*/
void cbMenuLiveWeatherDataBtn(void);
void cbMenuItem2Btn(void);
void cbMenuItem3Btn(void);
void cbMenuSettingsBtn(void);

/* Live weather data Callbacks -------------*/
void cbReturnButton(void);

/* Private functions -----------------------*/
static void degCelsius(uint16_t row, uint16_t col);
static void toTmpStr(char* strBuffer, uint32_t val);
static void toPressStr(char* strBuffer, uint32_t val);

/**
 * -----------------------------------------------------------------------------------------------------
 * 												DECLARATIONS
 * -----------------------------------------------------------------------------------------------------
 */

/**
 * Initialize the graphical user interface.
 */
void gui_init(void) {

	/* Initialize main menu components */
	gui_Button_init(&menuLiveWatherDataBtn,"Live Weather Data", 7, 10, 20, cbMenuLiveWeatherDataBtn);
	gui_Button_init(&menuItem2Btn,"Page 2", 9, 10, 20, cbMenuItem2Btn);
	gui_Button_init(&menuItem3Btn,"Page 3", 11, 10, 20, cbMenuItem3Btn);
	gui_Button_init(&menuSettingsBtn,"Settings", 13, 10, 20, cbMenuSettingsBtn);

	/* Initialize Live weather data components */
	gui_TextField_init(&tempTxtField, "", 6, 23, 6, NULL);
	gui_TextField_init(&presTxtField, "", 8, 23, 6, NULL);
	gui_TextField_init(&txtField3, "", 10, 23, 6, NULL);
	gui_TextField_init(&txtField4, "", 12, 23, 6, NULL);
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
 * Display the Live weather data page on the screen.
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
	gui_TextField_show(&presTxtField);
	gui_TextField_show(&txtField3);
	gui_TextField_show(&txtField4);
	gui_Button_show(&returnButton);
	gui_select_component(&returnButton);

	degCelsius(tempTxtField.row, tempTxtField.col + 8);
	graph_print_text("kPa", presTxtField.row, presTxtField.col + 8, TEXT_ALIGN_LEFT);
}

/**
 * Show the error page on the screen.
 */
void showErrorPage(char** messages) {

}

/**
 * -----------------------------------------------------------------------------------------------------
 * 										PERIPHERAL CALLBACK FUNCTIONS
 * -----------------------------------------------------------------------------------------------------
 */

/**
 * Callback function to handle key-presses.
 */
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

/**
 * Callback function to handle temperature sensor events.
 */
void cbTempSensor(void) {
	if(currPage != LIVE_WEATHER) {
		return;
	}

	char str[6];
	volatile uint32_t val = temp_read();
	toTmpStr(str, val);
	gui_TextField_setText(&tempTxtField, str);
}

/**
 * Callback function to handle Barometer events.
 */
void cbBarometer(void) {
	volatile uint8_t flags = MPL_read_flags();

	if(currPage != LIVE_WEATHER) {
		MPL_clear_interrupts();
		return;
	}

	char str[7];
	volatile uint32_t val = MPL_read_pressure();
	toPressStr(str, val);
	gui_TextField_setText(&presTxtField, str);
	MPL_clear_interrupts();
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

/**
 * Convert a integer value to a string, appropriate for the temperature data.
 */
static void toTmpStr(char* strBuffer, uint32_t val) {
	strBuffer[0] = 0x30 + (val/1000) % 10;
	strBuffer[1] = 0x30 + (val/100) % 10;
	strBuffer[2] = '\.';
	strBuffer[3] = 0x30 + (val/10) % 10;
	strBuffer[4] = 0x30 + val % 10;
	strBuffer[5] = '\0';
}

/**
 * Convert a integer value to a string, appropriate for the pressure data.
 */
static void toPressStr(char* strBuffer, uint32_t val) {
	strBuffer[0] = 0x30 + (val/100000) % 10;
	strBuffer[1] = 0x30 + (val/10000) % 10;
	strBuffer[2] = 0x30 + (val/1000) % 10;
	strBuffer[3] = '\.';
	strBuffer[4] = 0x30 + (val/100) % 10;
	strBuffer[5] = 0x30 + (val/10) % 10;
	strBuffer[6] = '\0';
}
