/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "LCDTouchscreen.hpp"

#include <list>
#include <algorithm>

#include "Graphics.hpp"
#include "Touchable.hpp"
#include "Displayable.hpp"
#include "HardwareMalfunction.hpp"

extern "C" {
	/*
	 * LCD's libraries.
	 */
	#include "altera_libs/alt_video_display.h"
	#include "altera_libs/alt_tpo_lcd.h"

	/*
	 * Touch-screen's libraries.
	 */
	#include "altera_libs/alt_touchscreen.h"
	#include "includes.h"
}

namespace neek {

enum Settings {
	LCD_BUFFERS_NUM = 2,
	LCD_COLOR_DEPTH = 32,
	TOUCHSCREEN_UPPER_RIGHT_ADC_X = 3946,
	TOUCHSCREEN_UPPER_RIGHT_ADC_Y = 3849,
	TOUCHSCREEN_UPPER_RIGHT_X = 799,
	TOUCHSCREEN_UPPER_RIGHT_Y = 0,
	TOUCHSCREEN_LOWER_LEFT_ADC_X = 132,
	TOUCHSCREEN_LOWER_LEFT_ADC_Y = 148,
	TOUCHSCREEN_LOWER_LEFT_X = 0,
	TOUCHSCREEN_LOWER_LEFT_Y = 479
};

class LCDTouchscreenImpl {
public:
	alt_tpo_lcd lcd_;
	alt_video_display * video_;
	Graphics * graphics_;

	alt_touchscreen touchscreen_;
	std::list <Touchable *> touchscreenListeners_;
	std::list <Displayable *> displayListeners_;
};

void onTouch (int, int x, int y, void * context) {
	LCDTouchscreenImpl * impl = static_cast <LCDTouchscreenImpl *> (context);

	typedef std::list <Touchable *>::iterator ListenersIter;
	for (ListenersIter iter = impl->touchscreenListeners_.begin ();
			iter != impl->touchscreenListeners_.end (); ++iter) {
		(*iter)->touched (x, y);
	}
}

LCDTouchscreen * LCDTouchscreen::instance_ = 0;

LCDTouchscreen * LCDTouchscreen::getInstance () {
	if (instance_ == 0) {
		instance_ = new LCDTouchscreen ();
	}
	return instance_;
}

LCDTouchscreen::LCDTouchscreen () : impl_ (new LCDTouchscreenImpl ()) {
	/*
	 * LCD's initialization.
	 */
	impl_->lcd_.scen_pio = LCD_I2C_EN_BASE;
	impl_->lcd_.scl_pio = LCD_I2C_SCL_BASE;
	impl_->lcd_.sda_pio = LCD_I2C_SDAT_BASE;
	 
	if(alt_tpo_lcd_init(&impl_->lcd_, LCD_WIDTH, LCD_HEIGHT) != 0) {
		throw HardwareMalfunction ("LCD initialization failed.");
	}

	impl_->video_ = alt_video_display_init (
			"/dev/lcd_sgdma", LCD_WIDTH, LCD_HEIGHT, LCD_COLOR_DEPTH,
			ALT_VIDEO_DISPLAY_USE_HEAP, ALT_VIDEO_DISPLAY_USE_HEAP,
			LCD_BUFFERS_NUM);

	if (impl_->video_ == 0) {
		throw HardwareMalfunction ("Video initialization failed.");
	}

	impl_->graphics_ = new Graphics (impl_->video_);

	/*
	 * Touch-screen's initialization.
	 */
	if (alt_touchscreen_init (&impl_->touchscreen_, TOUCH_PANEL_SPI_BASE,
			TOUCH_PANEL_SPI_IRQ, TOUCH_PANEL_PEN_IRQ_BASE,
			TOUCHSCREEN_SAMPLE_RATE, ALT_TOUCHSCREEN_SWAP_XY)) {
		throw HardwareMalfunction ("Touch-screen initialization failed.");
	}

	if (alt_touchscreen_register_callback_func (&impl_->touchscreen_,
			ALT_TOUCHSCREEN_CALLBACK_ON_PEN_DOWN, onTouch, impl_) != 0) {
		throw HardwareMalfunction ("Touch-screen initialization failed.");
	}

	alt_touchscreen_calibrate_upper_right (&impl_->touchscreen_,
			TOUCHSCREEN_UPPER_RIGHT_ADC_X, TOUCHSCREEN_UPPER_RIGHT_ADC_Y,
			TOUCHSCREEN_UPPER_RIGHT_X, TOUCHSCREEN_UPPER_RIGHT_Y);
	alt_touchscreen_calibrate_lower_left (&impl_->touchscreen_,
			TOUCHSCREEN_LOWER_LEFT_ADC_X, TOUCHSCREEN_LOWER_LEFT_ADC_Y,
			TOUCHSCREEN_LOWER_LEFT_X, TOUCHSCREEN_LOWER_LEFT_Y);
}

LCDTouchscreen::~LCDTouchscreen () {
	alt_video_display_close (impl_->video_,
			ALT_VIDEO_DISPLAY_USE_HEAP, ALT_VIDEO_DISPLAY_USE_HEAP);
	impl_->video_ = 0;
}

void LCDTouchscreen::addTouchable (Touchable * listener) {
	if (std::find (impl_->touchscreenListeners_.begin (),
			impl_->touchscreenListeners_.end (), listener)
					== impl_->touchscreenListeners_.end ()) {
		impl_->touchscreenListeners_.push_back (listener);
	}
}

void LCDTouchscreen::addDisplayable (Displayable * listener) {
	if (std::find (impl_->displayListeners_.begin (),
			impl_->displayListeners_.end (), listener)
					== impl_->displayListeners_.end ()) {
		impl_->displayListeners_.push_back (listener);
	}
}

void LCDTouchscreen::updateTouchscreen () {
	alt_touchscreen_event_loop_update (&impl_->touchscreen_);
}

void LCDTouchscreen::updateLCD () {
	typedef std::list <Displayable *>::iterator ListenersIter;
	for (ListenersIter iter = impl_->displayListeners_.begin ();
			iter != impl_->displayListeners_.end (); ++iter) {
		(*iter)->draw (impl_->graphics_, LCD_WIDTH, LCD_HEIGHT);
	}
	alt_video_display_register_written_buffer (impl_->video_);
}

}
