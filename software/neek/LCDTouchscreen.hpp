/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_LCD_TOUCHSCREEN_HEADER
#define NIOSII_KLONDIKE_LCD_TOUCHSCREEN_HEADER

namespace neek {

class Graphics;

class Touchable;

class Displayable;

class LCDTouchscreenImpl;

/*
 * Describes functionality of LCD touch-screen module of Altera NEEK.
 */
class LCDTouchscreen {
public:
	/*
	 * Width of the LCD in pixels.
	 */
	static const unsigned int LCD_WIDTH = 800;

	/*
	 * Height of the LCD in pixels.
	 */
	static const unsigned int LCD_HEIGHT = 480;

	/*
	 * Number of bytes for representing color of the pixel.
	 */
	static const unsigned int LCD_BYTES_PER_PIXEL = 4;

	/*
	 * Maximum sample rate of touch-screen module.
	 */
	static const unsigned int TOUCHSCREEN_SAMPLE_RATE = 50;

	/*
	 * Returns single instance of the LCDTouchscreen class which can be used
	 *    to access functionality of the LCD touch-screen module.
	 *
	 * Module will be initialized during the first call of this method. If any
	 *   error will occur during initialization, then HardwareMalfunction
	 *   exception will be generated.
	 */
	static LCDTouchscreen * getInstance ();

	virtual ~LCDTouchscreen ();

	/*
	 * Adds component to be displayed on the LCD.
	 */
	void addDisplayable (Displayable * listener);

	/*
	 * Updates information, which is displayed on the LCD.
	 */
	void updateLCD ();

	/*
	 * Adds component which is handles touch-screen's events.
	 */
	void addTouchable (Touchable * listener);

	/*
	 * Updates status of touch-screen and generates appropriate events.
	 */
	void updateTouchscreen ();

private:
	LCDTouchscreen ();

	LCDTouchscreen (const LCDTouchscreen&);
	LCDTouchscreen& operator = (const LCDTouchscreen&);

	static LCDTouchscreen * instance_;

	LCDTouchscreenImpl * impl_;
};

}

#endif
