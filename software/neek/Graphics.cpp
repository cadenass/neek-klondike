/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "Graphics.hpp"

#include "LCDTouchscreen.hpp"

#include <io.h>

namespace neek {

unsigned char * getBufferBeignWritten (alt_video_display * video) {
	alt_video_frame * frame =
			video->buffer_ptrs [video->buffer_being_written];
	return (unsigned char *) frame->buffer;
}

Graphics::Graphics (alt_video_display * video) : video_ (video) {
}

Graphics::~Graphics () {
}

void Graphics::clear (unsigned int color) {
	unsigned char * buffer = getBufferBeignWritten (video_);

	unsigned int offset = 0;
	for (unsigned int y = 0; y < LCDTouchscreen::LCD_HEIGHT; ++y) {
		for (unsigned int x = 0; x < LCDTouchscreen::LCD_WIDTH; ++x) {
			IOWR_32DIRECT (buffer, offset, color);
			offset += LCDTouchscreen::LCD_BYTES_PER_PIXEL;
		}
	}
}

void Graphics::drawBitmap (unsigned int x, unsigned int y,
		unsigned int width, unsigned int height,
		const Bitmap& bitmap, bool inverted) {
	unsigned char * buffer = getBufferBeignWritten (video_);

	unsigned int offsetBase = (y * LCDTouchscreen::LCD_WIDTH + x) *
			LCDTouchscreen::LCD_BYTES_PER_PIXEL;
	unsigned int bitmapBase = 0;
	for (unsigned int i = 0; i < height; ++i) {
		unsigned int offset = offsetBase;
		for (unsigned int j = 0; j < width; ++j) {
			unsigned int color = bitmap.content_[bitmapBase + j];
			if (inverted) {
				color = ~color;
			}
			IOWR_32DIRECT(buffer, offset, color);
			offset += LCDTouchscreen::LCD_BYTES_PER_PIXEL;
		}
		offsetBase += LCDTouchscreen::LCD_WIDTH
				* LCDTouchscreen::LCD_BYTES_PER_PIXEL;
		bitmapBase += bitmap.width_;
	}
}

}
