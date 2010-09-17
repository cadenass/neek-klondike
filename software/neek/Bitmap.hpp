/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_BITMAP_HEADER
#define NIOSII_KLONDIKE_BITMAP_HEADER

namespace neek {

class Graphics;

/*
	* Encapsulates basic information about 24-bit (true color) bitmap. This
	*   class only wraps information about the bitmap, which can be used only
	*   by the class Graphics.
 */
class Bitmap {
	/*
	 * Allows class Craphics perform direct access to the internal
	 *   representation of the class Bitmap.
	 */
	friend class Graphics;

public:
	/*
	 * Creates bitmap with the specified WIDTH and HEIGHT. Image's CONTENT
	 *   should be represented as one-dimensional array, which contains
	 *   information about color of each pixel, namely 32-bit integer value in
	 *   argb-format. Pixels should be listed starting from the upper-left
	 *   corner of bitmap left-to-right and top-to-bottom.
	 */
	Bitmap (unsigned int width, unsigned int height,
			const unsigned int * content);

private:
	unsigned int width_;
	unsigned int height_;
	const unsigned int * content_;
};

}

#endif
