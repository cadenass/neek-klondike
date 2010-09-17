/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "neek/LCDTouchscreen.hpp"
using neek::LCDTouchscreen;
#include "neek/HardwareMalfunction.hpp"
using neek::HardwareMalfunction;

#include "klondike/Layout.hpp"
using klondike::Layout;

#include <iostream>
#include <vector>

extern "C" {
	#include "includes.h"
}

#define LCD_TASK         1
#define TOUCHSCREEN_TASK 2

#define TASK_STACK_SIZE 2048
OS_STK touchscreen_task_stack [TASK_STACK_SIZE];
OS_STK lcd_task_stack [TASK_STACK_SIZE];

void updateTouchscreen (void * obj) {
	LCDTouchscreen * lcdTouchscreen = static_cast <LCDTouchscreen *> (obj);
	while (true) {
		OSTimeDlyHMSM (0, 0, 0, LCDTouchscreen::TOUCHSCREEN_SAMPLE_RATE);
		lcdTouchscreen->updateTouchscreen ();
	}
}

void updateLCD (void * obj) {
	LCDTouchscreen * lcdTouchscreen = static_cast <LCDTouchscreen *> (obj);
	while (true) {
		OSTimeDlyHMSM (0, 0, 0, 40);
		lcdTouchscreen->updateLCD ();
	}
}

int main () {
	try {
		LCDTouchscreen * lcdTouchscreen = LCDTouchscreen::getInstance ();

		Layout * layout = new Layout ();

		lcdTouchscreen->addTouchable (layout);
		lcdTouchscreen->addDisplayable (layout);

		int result = OSTaskCreateExt (updateTouchscreen,
			(void *) lcdTouchscreen,
			&touchscreen_task_stack [TASK_STACK_SIZE],
			TOUCHSCREEN_TASK,
			TOUCHSCREEN_TASK,
			touchscreen_task_stack,
			TASK_STACK_SIZE,
			NULL,
			0
		);

		result |= OSTaskCreateExt (updateLCD,
			(void *) lcdTouchscreen,
			&lcd_task_stack [TASK_STACK_SIZE],
			LCD_TASK,
			LCD_TASK,
			lcd_task_stack,
			TASK_STACK_SIZE,
			NULL,
			0
		);

		OSStart ();
	} catch (HardwareMalfunction& exception) {
		std::cerr << "Hardware error: " << exception.what () << std::endl; 
	}

	return 0;
}
