/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "Bitmap.hpp"

namespace neek {

Bitmap::Bitmap (unsigned int width, unsigned int height,
		const unsigned int * content)
		: width_ (width), height_ (height), content_ (content) {
}

}
