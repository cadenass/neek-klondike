/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_DISPLAYABLE_HEADER
#define NIOSII_KLONDIKE_DISPLAYABLE_HEADER

namespace neek {

class Graphics;

/*
 * Interface for components which are displayed on the LCD.
 */
class Displayable {
public:
	virtual ~Displayable () {}

	/*
	 * Draws displayable component using specified GRAPHICS context. Additional
	 * parameters specify WIDTH and HEIGHT of graphical context.
	 */
	virtual void draw (Graphics * graphics, unsigned int width,
			unsigned int height) = 0;

protected:
	Displayable () {}

private:
	Displayable (const Displayable&);
	Displayable& operator = (const Displayable&);
};

}

#endif
