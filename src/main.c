/* Includes -------------------------------------------------------------------*/
#include "main.h"

/* Variables ------------------------------------------------------------------*/
extern bool kpadFlag;
TextField_t txtField;
/* Definitions ----------------------------------------------------------------*/

/* Prototypes -----------------------------------------------------------------*/
void lcd_example(void);
void keypad_example(void);
void cbTextField(void);

/* Compiler stuff -------------------------------------------------------------*/
/**
 * Sample pragmas to cope with warnings. Please note the related line at
 * the end of this function, used to pop the compiler diagnostics status.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wconversion"

/* Main -----------------------------------------------------------------------*/

/**
 * Normally at this stage most of the microcontroller subsystems, including
 * the clock, were initialised by the CMSIS SystemInit() function invoked
 * from the startup file, before calling main().
 * (see system/src/cortexm/_initialize_hardware.c)
 */
int main(int argc, char* argv[]) {

	// Disable watchdog timer
	WDT->WDT_MR = WDT_MR_WDDIS;

	//Print simple message through SWD debugger.
#ifdef DEBUG
	trace_puts("DEBUG is running...\n");
#endif

	kpad_init();
	lcd_example();
	graph_print_textBox("~PRESS THE KEYPAD~", 2, 1, TEXT_ALIGN_CENTER);
	graph_print_text("", 4, 1, TEXT_ALIGN_LEFT);

	gui_TextField_init(&txtField, "Hejsanaowidjwijjnj", 4, 2, 10, 1,
			cbTextField);
	gui_TextField_select(&txtField);
	gui_TextField_show(&txtField);

	while (1) {
		if (kpadFlag) {
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
	}

	return EXIT_SUCCESS;
}

void lcd_example(void) {
	disp_init();
	disp_wr_cmd(CURS_ON_BLINK_ON | TEXT_ON_GRAPHIC_ON);
	//disp_wr_cmd(TEXT_ON_GRAPHIC_ON);
	disp_wr_cmd(CURSOR_8_LINE);
	disp_wr_hword(CURSOR_AUTOMOVE, 0x0001);
	disp_wr_hword(SET_ADDRESS_PIONTER, FRAME_TEXT_1);
	disp_set_frame(FRAME_1);
	disp_full_clear();

	/*
	 graph_print_text("Hello, world!", 8, 15);
	 graph_draw_pixel(2, 2);
	 graph_draw_pixel(5, 5);


	 graph_draw_line(0, 0, 29, 127);
	 graph_draw_line(0, 0, 59, 127);
	 graph_draw_line(0, 0, 119, 127);
	 graph_draw_line(0, 0, 239, 127);
	 graph_draw_line(0, 0, 239, 63);

	 graph_draw_line(239, 0, 209, 127);
	 graph_draw_line(239, 0, 179, 127);
	 graph_draw_line(239, 0, 119, 127);
	 graph_draw_line(239, 0, 0, 127);
	 graph_draw_line(239, 0, 0, 63);

	 graph_draw_line(0, 127, 29, 0);
	 graph_draw_line(0, 127, 59, 0);
	 graph_draw_line(0, 127, 119, 0);
	 graph_draw_line(0, 127, 239, 0);
	 graph_draw_line(0, 127, 239, 63);

	 graph_draw_line(239, 127, 209, 0);
	 graph_draw_line(239, 127, 179, 0);
	 graph_draw_line(239, 127, 119, 0);
	 graph_draw_line(239, 127, 0, 0);
	 graph_draw_line(239, 127, 0, 63);


	 disp_full_clear();
	 graph_print_text("Hello, world!", 8, 15);
	 graph_draw_rect(0, 0, 240, 128);
	 graph_draw_rect(2, 2, 236, 124);
	 graph_print_textBox("~MENU~", 4, 2, TEXT_ALIGN_CENTER);
	 graph_print_textBox("  Temperature Graph  ", 7, 2, TEXT_ALIGN_CENTER);
	 graph_print_textBox("   Humidity Graph    ", 9, 2, TEXT_ALIGN_CENTER);
	 graph_print_textBox("   Current Weather   ", 11, 2, TEXT_ALIGN_CENTER);
	 graph_print_textBox("      Settings       ", 13, 2, TEXT_ALIGN_CENTER);

	 disp_set_frame(FRAME_2);
	 disp_full_clear();
	 graph_print_text("Hello, world!", 8, 15);
	 graph_draw_rect(0, 0, 240, 128);
	 graph_draw_rect(2, 2, 236, 124);
	 graph_print_textBox("~FRAME 2 MENU~", 4, 2, TEXT_ALIGN_CENTER);

	 disp_set_frame(FRAME_1);
	 disp_set_frame(FRAME_2);
	 */
}

void cbTextField(void) {
	trace_puts(txtField.text);
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
