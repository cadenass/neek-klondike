/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "Card.hpp"

#include "../neek/Bitmap.hpp"
using neek::Bitmap;

#include "../resources/faces.res"

namespace klondike {

Card::Card () : rank_ (CardRank_Unknown), suit_ (CardSuit_Unknown) {
}

Card::Card (CardRank rank, CardSuit suit) : rank_ (rank), suit_ (suit) {
}

CardRank Card::rank () const {
	return rank_;
}

CardSuit Card::suit () const {
	return suit_;
}

Bitmap Card::face () const {
	if (rank_ == CardRank_Unknown || suit_ == CardSuit_Unknown) {
		return Bitmap (0, 0, 0);
	} else {
		return Bitmap (CARD_WIDTH, CARD_HEIGHT,
			resources::faces [suit_ * CARD_RANKS_NUM + rank_]);
	}
}

bool Card::red () const {
	return suit_ == CardSuit_Heart || suit_ == CardSuit_Diamond;
}

bool Card::black () const {
	return suit_ == CardSuit_Club || suit_ == CardSuit_Spade;
}

}
