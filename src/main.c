/**
 * --------------------------------------------------------------------------------------------------
 * 										INCLUDES
 * --------------------------------------------------------------------------------------------------
 */

#include "main.h"

/**
 * --------------------------------------------------------------------------------------------------
 * 										VARIABLES
 * --------------------------------------------------------------------------------------------------
 */
extern bool kpadFlag;
static bool tempFlag = false;
static uint32_t ticks = 0;

/**
 * --------------------------------------------------------------------------------------------------
 * 										DEFINES
 * --------------------------------------------------------------------------------------------------
 */

/**
 * --------------------------------------------------------------------------------------------------
 * 										PROTOTYPES
 * --------------------------------------------------------------------------------------------------
 */
void lcd_init(void);
extern void gui_init(void);
extern void cbKeyPress(void);
extern void cbTempSensor(void);

void delay_ms(uint32_t t_ms);
uint32_t getTicks(void);

/**
 * --------------------------------------------------------------------------------------------------
 * 										COMPILER STUFF
 * --------------------------------------------------------------------------------------------------
 */
/**
 * Sample pragmas to cope with warnings. Please note the related line at
 * the end of this function, used to pop the compiler diagnostics status.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wconversion"

/**
 * --------------------------------------------------------------------------------------------------
 * 										MAIN
 * --------------------------------------------------------------------------------------------------
 */

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
	/* initialize 1ms timebase */
	SysTick_Config(SystemCoreClock/1000);

	/* Initialize hardware and software stack*/
	kpad_init();
	lcd_init();
	gui_init();
	temp_init();

	while (1) {
		if (kpadFlag) {
			cbKeyPress();
		}

		if(tempFlag) {
			cbTempSensor();
			tempFlag = false;
		}
	}

	return EXIT_SUCCESS;
}

void lcd_init(void) {
	disp_init();
	disp_wr_cmd(CURS_ON_BLINK_ON | TEXT_ON_GRAPHIC_ON);
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

/**
 * returns the current ticks value.
 */
uint32_t getTicks(void) {
	return ticks;
}

/**
 * Delays execution for the specified amount of ms.
 */
void delay_ms(uint32_t t_ms) {
	volatile uint32_t t0 = ticks;
	while(t_ms > getTicks() - t0) {
		asm("NOP");
	};
}

/**
 * --------------------------------------------------------------------------------------------------
 * 										INTERRUPT HANDLERS
 * --------------------------------------------------------------------------------------------------
 */
void SysTick_Handler(void) {
	ticks++;

	if(ticks % 250 == 0) {
		temp_trig();
	}

}

void TC0_Handler(void) {
	volatile uint32_t dummy = TC0->TC_CHANNEL[0].TC_SR;
	tempFlag = true;
}

#pragma GCC diagnostic pop

/**
 * --------------------------------------------------------------------------------------------------
 * 										EOF
 * --------------------------------------------------------------------------------------------------
 */
