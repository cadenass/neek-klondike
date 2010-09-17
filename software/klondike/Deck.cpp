/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#include "Deck.hpp"

#include "Card.hpp"

#include "../neek/Bitmap.hpp"
using neek::Bitmap;

#include <algorithm>
#include <iterator>

#include <cstdlib>
#include <ctime>

namespace klondike {

Deck Deck::of52Cards () {
	std::vector <Card> cards;
	for (unsigned int suit = 0; suit < CARD_SUITS_NUM; ++suit) {
		for (unsigned int rank = 0; rank < CARD_RANKS_NUM; ++rank) {
			cards.push_back (Card ((CardRank) rank, (CardSuit) suit));
		}
	}
	return Deck (cards);
}

Deck::Deck () {
}

Deck::Deck (const std::vector <Card>& cards)
		: cards_ (cards) {
}

Card Deck::top () const {
	return cards_.back ();
}

void Deck::insert (const Card& card) {
	cards_.push_back (card);
}

void Deck::remove () {
	cards_.pop_back ();
}

void Deck::shuffle () {
	srand ((unsigned) time (NULL));

	unsigned int cardsNum = cards_.size ();
	std::vector <Card> shuffledCards;
	for (unsigned int i = 0; i < cardsNum; ++i) {
		unsigned int pos = rand () % cards_.size ();
		Card selCard = cards_ [pos];
		shuffledCards.push_back (selCard);
		cards_.erase (cards_.begin () + pos);
	}
	cards_ = shuffledCards;
}

void Deck::reverse () {
	std::reverse (cards_.begin (), cards_.end ());
}

void Deck::merge (const Deck& mergedStack) {
	std::copy (mergedStack.cards_.begin (), mergedStack.cards_.end (),
			std::back_inserter (cards_));
}

Deck Deck::split (unsigned int cardsNum) {
	std::vector <Card> splittedCards;
	std::copy (cards_.begin () + (cards_.size () - cardsNum), cards_.end (),
			std::back_inserter (splittedCards));
	cards_.erase (cards_.begin () + cards_.size () - cardsNum, cards_.end ());
	return Deck (splittedCards);
}

void Deck::clear () {
	cards_.clear ();
}

bool Deck::empty () const {
	return cards_.empty ();
}

unsigned int Deck::size () const {
	return cards_.size ();
}

const Card& Deck::operator [] (unsigned int pos) const {
	return cards_ [pos];
}

}
