#include "Deck.h"
#include <algorithm>


Deck::Deck(int countryCount) {
	cardDeck.reserve(countryCount);
	for (int i = 0; i < countryCount; i++) {
		// Since we need to have equal amount of card types
		// We are picking them round robin style
		Card card((CardType(i % CardType::_Count)));
		cardDeck.push_back(card);
	}

	// Once we distrubuted the card types eqaully in the deck, we'll shuffle it randomly with a random seed
	std::random_device::result_type seed = std::random_device{}();
	std::shuffle(cardDeck.begin(),cardDeck.end(), std::default_random_engine(seed));
}


Deck::~Deck() {
}

const Card& Deck::draw() {
	// In this case, we are using the vector as a stack
	// When we pop off the stack, we are removing a card from the back of the vector
	// Draw the next card from the back of the vector / stack
	Card& top = cardDeck.back();
	// Since pop_back does not return a reference to what it pops
	// we have to manually call .back() first to get a reference to the card
	// Pop it off the stack
	cardDeck.pop_back();
	// Return the card we just popped back
	// Since this is a reference, the caller of this function must take ownership of the card reference
	return top;
}

bool Deck::isEmpty() const {
	return cardDeck.size() == 0;
}

int Deck::getDeckSize() const {
	return cardDeck.size();
}
