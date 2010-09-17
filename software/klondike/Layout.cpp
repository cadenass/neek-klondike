/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "Layout.hpp"

#include "Card.hpp"
#include "Deck.hpp"

#include "../neek/Touchable.hpp"
using neek::Touchable;
#include "../neek/Displayable.hpp"
using neek::Displayable;

#include "../neek/Graphics.hpp"
using neek::Graphics;
#include "../neek/Bitmap.hpp"
using neek::Bitmap;

#include "../resources/others.res"

namespace klondike {

namespace {

bool contains (unsigned int upperLeftX, unsigned int upperLeftY,
			unsigned int width, unsigned int height,
			unsigned int x, unsigned int y){
	return (x >= upperLeftX && x < upperLeftX + width) &&
			(y >= upperLeftY && y < upperLeftY + height);
}


bool ascending (const Card& lower, const Card& upper) {
	CardRank oneLess [] = {CardRank_Three, CardRank_Four, CardRank_Five,
			CardRank_Six, CardRank_Seven, CardRank_Eight, CardRank_Nine,
			CardRank_Ten, CardRank_Jack, CardRank_Queen, CardRank_King,
			CardRank_Unknown, CardRank_Two};
	return oneLess [lower.rank ()] == upper.rank ();
}

bool alternatingColors (const Card& lower, const Card& upper) {
	return lower.red () && upper.black () || lower.black () && upper.red ();
}

}

Layout::Layout ()
		: backImage_ (CARD_WIDTH, CARD_HEIGHT, resources::back),
		dealImage_ (CARD_WIDTH, CARD_HEIGHT, resources::deal),
		redealImage_ (CARD_WIDTH, CARD_HEIGHT, resources::redeal),
		foundationImage_ (CARD_WIDTH, CARD_HEIGHT, resources::foundation) {

	for (unsigned int i = 0; i < FOUNDATIONS_NUM; ++i) {
		foundations_.push_back (Deck ());
	}
	for (unsigned int i = 0; i < PILES_NUM; ++i) {
		openedPiles_.push_back (Deck ());
		closedPiles_.push_back (Deck ());
	}

	deal ();

	dealVisible_ = false;
}

Layout::~Layout () {
}

void Layout::deal () {
	Deck dealtDeck = Deck::of52Cards ();
	dealtDeck.shuffle ();

	for (unsigned int i = 0; i < FOUNDATIONS_NUM; ++i) {
		foundations_ [i].clear ();
	}

	for (unsigned int i = 0; i < PILES_NUM; ++i) {
		closedPiles_ [i].clear ();
		for (unsigned int j = 0; j < i; ++j) {
			closedPiles_ [i].insert (dealtDeck.top ());
			dealtDeck.remove ();
		}
	}

	for (unsigned int i = 0; i < PILES_NUM; ++i) {
		openedPiles_ [i].clear ();
		openedPiles_ [i].insert (dealtDeck.top ());
		dealtDeck.remove ();
	}

	stock_.clear ();
	while (!dealtDeck.empty ()) {
		stock_.insert (dealtDeck.top ());
		dealtDeck.remove ();
	}

	waste_.clear ();

	wasteSel_ = false;
	pileSel_ = false;
}

void Layout::draw (Graphics * graphics, unsigned int width,
			unsigned int height) {
	gapSize_ = (width - PILES_NUM * CARD_WIDTH) / GAPS_NUM;

	graphics->clear (BACKGROUND_COLOR);

	drawDeal (graphics);
	drawStock (graphics);
	drawWaste (graphics);
	drawFoundations (graphics);
	drawClosedPiles (graphics);
	drawOpenedPiles (graphics);
}

void Layout::drawDeal (Graphics * graphics) {
	if (!dealVisible_) {
		return;
	}
	unsigned int pileX = 2 * (CARD_WIDTH + gapSize_);
	unsigned int pileY = 0;
	graphics->drawBitmap (pileX, pileY, CARD_WIDTH, CARD_HEIGHT, dealImage_);
}

void Layout::drawStock (Graphics * graphics) {
	if (stock_.empty ()) {
		graphics->drawBitmap (0, 0, CARD_WIDTH, CARD_HEIGHT, redealImage_);
	} else {
		graphics->drawBitmap (0, 0, CARD_WIDTH, CARD_HEIGHT, backImage_);
	}
}

void Layout::drawWaste (Graphics * graphics) {
	if (waste_.empty ()) {
		return;
	}
	unsigned int pileX = CARD_WIDTH + gapSize_;
	unsigned int pileY = 0;
	graphics->drawBitmap (pileX, pileY, CARD_WIDTH, CARD_HEIGHT,
			waste_.top ().face (), wasteSel_);
}

void Layout::drawFoundations (Graphics * graphics) {
	unsigned int pileX = 3 * (CARD_WIDTH + gapSize_);
	unsigned int pileY = 0;
	for (unsigned int i = 0; i < FOUNDATIONS_NUM; ++i) {
		Bitmap bitmap = foundations_ [i].empty () ?
				foundationImage_ : foundations_ [i].top ().face ();
		graphics->drawBitmap (pileX, pileY, CARD_WIDTH, CARD_HEIGHT, bitmap);
		pileX += CARD_WIDTH + gapSize_;
	}
}

void Layout::drawClosedPiles (Graphics * graphics) {
	unsigned int pileX = 0;
	for (unsigned i = 0; i < PILES_NUM; ++i) {
		unsigned int cardY = TABLEAU_Y;
		unsigned int size = closedPiles_ [i].size ();
		for (unsigned int j = 0; j < size; ++j) {
			unsigned int bitmapHeight = (j != size - 1) ?
					CLOSED_TAG : CARD_HEIGHT;
			graphics->drawBitmap (pileX, cardY, CARD_WIDTH, bitmapHeight,
					backImage_);
			cardY += CLOSED_TAG;
		}
		pileX += CARD_WIDTH + gapSize_;
	}
}

void Layout::drawOpenedPiles (Graphics * graphics) {
	unsigned int pileX = 0;
	for (unsigned i = 0; i < PILES_NUM; ++i) {
		unsigned int cardY = TABLEAU_Y +
				closedPiles_ [i].size () * CLOSED_TAG;
		unsigned int size = openedPiles_ [i].size ();
		for (unsigned int j = 0; j < size; ++j) {
			unsigned int bitmapHeight = (j != size - 1) ?
				OPENED_TAG : CARD_HEIGHT;
			bool cardSel = pileSel_ && (selPileInd_ == i) &&
					(j >= (size - selCardsNum_));
			Card drawnCard = openedPiles_ [i][j];
			graphics->drawBitmap (pileX, cardY, CARD_WIDTH, bitmapHeight,
					drawnCard.face (), cardSel);
			cardY += OPENED_TAG;
		}
		pileX += CARD_WIDTH + gapSize_;
	}
}

void Layout::touched (unsigned int x, unsigned int y) {
	if (dealTouched (x, y)) {
		return;
	}

	dealVisible_ = false;

	if (stockTouched (x, y)) {
		return;
	}
	if (wasteTouched (x, y)) {
		return;
	}
	if (foundationTouched (x, y)) {
		return;
	}
	pileTouched (x, y);
}

bool Layout::dealTouched (unsigned int x, unsigned int y) {
	unsigned int dealX = 2 * (CARD_WIDTH + gapSize_);
	unsigned int dealY = 0;
	if (!contains (dealX, dealY, CARD_WIDTH, CARD_HEIGHT, x, y)) {
		return false;
	}

	if (dealVisible_) {
		deal ();
	}
	dealVisible_ = !dealVisible_;
	return true;
}

bool Layout::stockTouched (unsigned int x, unsigned int y) {
	unsigned int stockX = 0;
	unsigned int stockY = 0;
	if (!contains (stockX, stockY, CARD_WIDTH, CARD_HEIGHT, x, y)) {
		return false;
	}

	if (stock_.empty ()) {
		stock_.merge (waste_);
		stock_.reverse ();
		waste_.clear ();
	} else {
		waste_.insert (stock_.top ());
		stock_.remove ();
	}
	wasteSel_ = false;
	pileSel_ = false;
	return true;
}

bool Layout::wasteTouched (unsigned int x, unsigned int y) {
	unsigned int wasteX = CARD_WIDTH + gapSize_;
	unsigned int wasteY = 0;
	if (!contains (wasteX, wasteY, CARD_WIDTH, CARD_HEIGHT, x, y)) {
		return false;
	}

	pileSel_ = false;
	if (!waste_.empty ()) {
		wasteSel_ = !wasteSel_;
	}
	return true;
}

bool Layout::foundationTouched (unsigned int x, unsigned int y) {
	unsigned int pileX = 3 * (CARD_WIDTH + gapSize_);
	unsigned int selPile = 0;
	for (unsigned int i = 0; i < FOUNDATIONS_NUM; ++i) {
		if (contains (pileX, selPile, CARD_WIDTH, CARD_HEIGHT, x, y)) {
			if (!wasteSel_ && !pileSel_ && (selCardsNum_ == 1)) {
				return true;
			}
			Deck& selPile = wasteSel_ ? waste_ : openedPiles_ [selPileInd_];
			Card topCard = selPile.top ();

			wasteSel_ = false;
			pileSel_ = false;

			bool isAce = foundations_ [i].empty () &&
					topCard.rank () == CardRank_Ace;
			bool isNextInSuit = false;
			if (!isAce) {
				const Card& topCardInSuit = foundations_ [i].top ();
				isNextInSuit = ascending (topCardInSuit, topCard) &&
						(topCardInSuit.suit () == topCard.suit ());
			}
			if (isAce || isNextInSuit) {
				foundations_ [i].insert (topCard);
				selPile.remove ();
			}
			return true;
		}
		pileX += CARD_WIDTH + gapSize_;
	}

	return false;
}

void Layout::pileTouched (unsigned int x, unsigned int y) {
	unsigned int pileX = 0;
	for (unsigned i = 0; i < PILES_NUM; ++i) {
		Deck& closedPile = closedPiles_ [i];
		Deck& openedPile = openedPiles_ [i];
		if (!openedPiles_ [i].empty ()) {
			unsigned int topCardY = TABLEAU_Y +
					closedPile.size () * CLOSED_TAG +
					(openedPile.size () - 1) * OPENED_TAG;

			if (contains (pileX, topCardY, CARD_WIDTH, CARD_HEIGHT, x, y)) {
				if (wasteSel_) {
					Card selCard = waste_.top ();
					Card topCard = openedPile.top ();
					if (ascending (selCard, topCard)
							&& alternatingColors (selCard, topCard)) {
						waste_.remove ();
						openedPile.insert (selCard);
					}
					wasteSel_ = false;
				} else if (pileSel_) {
					Deck& selPile = openedPiles_ [selPileInd_];
					Card baseCard = selPile [selPile.size () - selCardsNum_];
					Card topCard = openedPile.top ();
					if (ascending (baseCard, topCard)
							&& alternatingColors (baseCard, topCard)) {
						openedPile.merge (selPile.split (selCardsNum_));
					}
					pileSel_ = false;
				} else {
					pileSel_ = true;
					selPileInd_ = i;
					selCardsNum_ = 1;
				}
			} else {
				unsigned int pileY = TABLEAU_Y +
						closedPile.size () * CLOSED_TAG;
				unsigned int pileHeight = (openedPile.size () - 1) *
						OPENED_TAG;
				if (contains (pileX, pileY, CARD_WIDTH, pileHeight, x, y)) {
					wasteSel_ = false;
					pileSel_ = true;
					selPileInd_ = i;
					selCardsNum_ = openedPile.size () -
							(y - pileY) / OPENED_TAG;
				}
			}
		} else {
			if (!closedPile.empty ()) {
				unsigned int topCardY = TABLEAU_Y +
						(closedPile.size () - 1) * CLOSED_TAG;
				if (contains (pileX, topCardY,
						CARD_WIDTH, CARD_HEIGHT, x, y)) {
					openedPile.insert (closedPile.top ());
					closedPile.remove ();
					wasteSel_ = false;
					pileSel_ = false;
				}
			} else {
				if (contains (pileX, TABLEAU_Y,
						CARD_WIDTH, CARD_HEIGHT, x, y)) {
					if (wasteSel_) {
						Card selCard = waste_.top ();
						if (selCard.rank () == CardRank_King) {
							openedPile.insert (selCard);
							waste_.remove ();
						}
						wasteSel_ = false;
					} else if (pileSel_) {
						Deck& selPile = openedPiles_ [selPileInd_];
						Card baseCard =
								selPile [selPile.size () - selCardsNum_];
						if (baseCard.rank () == CardRank_King) {
							openedPile.merge (selPile);
							selPile.clear ();
						}
						pileSel_ = false;
					}
				}
			}
		}
		pileX += CARD_WIDTH + gapSize_;
	}
}

}
