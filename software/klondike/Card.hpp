/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_CARD_HEADER
#define NIOSII_KLONDIKE_CARD_HEADER

#include "../neek/Bitmap.hpp"

namespace klondike {

/*
 * Enumeration of suits of the playing cards.
 */
enum CardSuit {
	CardSuit_Heart = 0,
	CardSuit_Diamond,
	CardSuit_Club,
	CardSuit_Spade,

	CardSuit_Unknown
};

/*
 * Enumeration of ranks of the playing cards.
 */
enum CardRank {
	CardRank_Two = 0,
	CardRank_Three, CardRank_Four, CardRank_Five, CardRank_Six,
	CardRank_Seven, CardRank_Eight, CardRank_Nine, CardRank_Ten,
	CardRank_Jack, CardRank_Queen, CardRank_King, CardRank_Ace,

	CardRank_Unknown
};

/*
 * Useful constants.
 */
enum CardsProperties {
	CARD_SUITS_NUM = 4,
	CARD_RANKS_NUM = 13,
	CARD_WIDTH = 71,
	CARD_HEIGHT = 96
};

/*
 * Contains parameters of the playing card.
 */
class Card {
public:
	/*
	 * Allows to use this class with the standard containers.
	 */
	Card ();

	/*
	 * Creates playing card with the specified SUIT and RANK.
	 */
	Card (CardRank rank, CardSuit suit);

	/*
	 * Returns rank of the playing card.
	 */
	CardRank rank () const;

	/*
	 * Returns suit of the playing card.
	 */
	CardSuit suit () const;

	/*
	 * Returns face's image of the playing card.
	 */
	neek::Bitmap face () const;

	/*
	 * Returns true if card is red (i.e. it belongs to hearts or diamonds).
	 */
	bool red () const;

	/*
	 * Returns true if card is black (i.e. it belongs to clubs or spades).
	 */
	bool black () const;

private:
	CardRank rank_;
	CardSuit suit_;
};

}

#endif
