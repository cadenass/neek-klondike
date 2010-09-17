/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_GRAPHICS_HEADER
#define NIOSII_KLONDIKE_GRAPHICS_HEADER

#include "Bitmap.hpp"

extern "C" {
    #include "altera_libs/alt_video_display.h"
}

namespace neek {

/*
 * Allows to draw in the LCD's frame buffer.
 */
class Graphics {
public:
	/*
	 * Creates graphic context for the specified VIDEO-display.
	 */
	Graphics (alt_video_display * video);

	~Graphics ();

	/*
	 * Clears graphic context and fills it with specified COLOR.
	 */
	void clear (unsigned int color);

	/*
	 * Draws specified BITMAP (or part of it) in the given position.
	 *
	 * Client specifies position of the upper-left corner of the bitmap (X and
	 *   Y coordinates). Also it specifies required WIDTH and HEIGHT, which
	 *   should be less or equal to the bitmap's size. Additional parameter
	 *   can be used, when bitmap's colors should be INVERTED.
	 */
	void drawBitmap (unsigned int x, unsigned int y,
			unsigned int width, unsigned int height,
			const Bitmap& bitmap, bool inverted = false);

private:
	Graphics (const Graphics&);
	Graphics& operator = (const Graphics&);

	alt_video_display * video_;
};

}

#endif
