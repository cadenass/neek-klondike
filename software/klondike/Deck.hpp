/*
 * Nios II Klondike Solitaire (Altera Neek Edition)
 */

#ifndef NIOSII_KLONDIKE_DECK_HEADER
#define NIOSII_KLONDIKE_DECK_HEADER

#include "Card.hpp"

#include <vector>

namespace klondike {

/*
 * Describes deck of playing cards.
 */
class Deck {
public:
	/*
	 * Creates standard deck of 52 playing cards.
	 */
	static Deck of52Cards ();

	/*
	 * Creates empty deck of playing cards.
	 */
	Deck ();

	/*
	 * Returns top card of the deck.
	 */
	Card top () const;

	/*
	 * Inserts CARD into top of the deck.
	 */
	void insert (const Card& card);

	/*
	 * Removes top card from the deck.
	 */
	void remove ();

	/*
	 * Shuffles cards in the deck.
	 */
	void shuffle ();

	/*
	 * Reverses order of the cards in the stack.
	 */
	void reverse ();

	/*
	 * Inserts cards from the given DECK into top of the current deck.
	 */
	void merge (const Deck& deck);

	/*
	 * Splits deck into two by removing specified NUMBER OF CARDS from top.
	 */
	Deck split (unsigned int cardsNum);

	/*
	 * Removes all cards from the deck.
	 */
	void clear ();

	/*
	 * Checks whether deck is empty or not.
	 */
	bool empty () const;

	/*
	 * Returns number of the cards in the deck.
	 */
	unsigned int size () const;

	/*
	 * Returns card which is in the specified POSITION.
	 */
	const Card& operator [] (unsigned int pos) const;

private:
	Deck (const std::vector <Card>& cards);

	std::vector <Card> cards_;
};

}

#endif
