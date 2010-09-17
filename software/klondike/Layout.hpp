/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_LAYOUT_HEADER
#define NIOSII_KLONDIKE_LAYOUT_HEADER

#include "Deck.hpp"

#include "../neek/Touchable.hpp"
#include "../neek/Displayable.hpp"

#include "../neek/Graphics.hpp"
#include "../neek/Bitmap.hpp"

#include <vector>

namespace klondike {

/*
 * Describes layout for the klondike solitaire.
 */
class Layout : public neek::Touchable, public neek::Displayable {
public:
	/*
	 * Creates layout (also deals cards).
	 */
	Layout ();

	~Layout ();

	/*
	 * Inherited from neek::Displayable.
	 */
	virtual void draw (neek::Graphics * graphics, unsigned int width,
			unsigned int height);

	/*
	 * Inherited from neek::Touchable.
	 */
	virtual void touched (unsigned int x, unsigned int y);

private:
	Layout (const Layout&);
	Layout& operator = (const Layout&);

	void deal ();

	neek::Bitmap backImage_;
	neek::Bitmap dealImage_;
	neek::Bitmap redealImage_;
	neek::Bitmap foundationImage_;

	static const unsigned int BACKGROUND_COLOR = 0x00008000;

	static const unsigned int FOUNDATIONS_NUM = 4;
	static const unsigned int PILES_NUM = 7;
	static const unsigned int GAPS_NUM = PILES_NUM - 1;

	static const unsigned int TABLEAU_Y = CARD_HEIGHT + CARD_HEIGHT / 10;
	static const unsigned int CLOSED_TAG = CARD_HEIGHT / 10;
	static const unsigned int OPENED_TAG = CARD_HEIGHT / 5;

	Deck stock_;
	Deck waste_;

	std::vector <Deck> foundations_;

	std::vector <Deck> closedPiles_;
	std::vector <Deck> openedPiles_;

	unsigned int gapSize_;

	bool wasteSel_;
	bool pileSel_;
	unsigned int selPileInd_;
	unsigned int selCardsNum_;

	bool dealVisible_;

	void drawDeal (neek::Graphics * graphics);

	void drawStock (neek::Graphics * graphics);
	void drawWaste (neek::Graphics * graphics);
	void drawFoundations (neek::Graphics * graphics);
	void drawClosedPiles (neek::Graphics * graphics);
	void drawOpenedPiles (neek::Graphics * graphics);

	bool dealTouched (unsigned int x, unsigned int y);
	bool stockTouched (unsigned int x, unsigned int y);
	bool wasteTouched (unsigned int x, unsigned int y);
	bool foundationTouched (unsigned int x, unsigned int y);
	void pileTouched (unsigned int x, unsigned int y);
};

}

#endif
