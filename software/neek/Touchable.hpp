/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_TOUCHABLE_HEADER
#define NIOSII_KLONDIKE_TOUCHABLE_HEADER

namespace neek {

/*
 * Interface for components which are handle touch-screen's events.
 */
class Touchable {
public:
	virtual ~Touchable () {}

	/*
	 * Handles pressing at point which is specified by X and Y coordinates.
	 */
	virtual void touched (unsigned int x, unsigned int y) = 0;

protected:
	Touchable () {}

private:
	Touchable (const Touchable&);
	Touchable& operator = (const Touchable&);
};

}

#endif
