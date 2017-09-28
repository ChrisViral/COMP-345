// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "Deck.h"
#include <algorithm>


Deck::Deck(int countryCount)
{
	for (int i = 0; i < countryCount; i++)
	{
		// Since we need to have equal amount of card types
		// We are picking them round robin style
		Card card((CardType(i % _Count)));
		cardDeck.push_front(card);
	}

	// Once we distrubuted the card types eqaully in the deck, we'll shuffle it randomly with a random seed
	std::random_device::result_type seed = std::random_device{}();
	shuffle(cardDeck.begin(), cardDeck.end(), std::default_random_engine(seed));
}


Deck::~Deck()
{
}

const Card& Deck::draw()
{
	// In this case, we are using a deque for fast inserts in the front/end
	// the front of the deck is the top of the deck
	// Since pop_front doesn't return the card
	// we have to first get a reference to the card at the top of the deck
	Card& top = cardDeck.front();

	// Once we have a reference to the top of the deck
	// we can remove it from the top of the deck
	cardDeck.pop_front();
	// Return the card we just popped back
	// Since this is a reference, the caller of this function must take ownership of the card reference
	return top;
}

bool Deck::isEmpty() const
{
	return cardDeck.size() == 0;
}

int Deck::getDeckSize() const
{
	return cardDeck.size();
}

void Deck::addCard(const Card& card)
{
	// Adds the card on the bottom of the deck
	cardDeck.push_back(card);
}
