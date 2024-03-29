// ==============================
//           COMP-345 D
//          Assignment 4
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#pragma once
#include "Card.h"
#include <deque>


class Deck : public RiskObject
{
public:

	// Create a deck of cards with the same amount of cards as there are countries
	// A deck will have an equal distribution of CardTypes given that the country count is a multiple of the amount of CardTypes
	Deck(int countryCount);
	~Deck();
	// Draws a card from on top of the card deck
	// the caller of this function must take ownership of the card reference
	// Note before calling draw(), you should check to see if the deck of cards is empty by calling isEmpty()
	// Calling draw on an empty deck will give you a runtime error
	const Card& draw();
	// Checks to see if the deck of cards is empty
	bool isEmpty() const;
	// Gets the amount of cards in the deck
	int getDeckSize() const;

	// Add a card back into the deck
	void addCard(const Card& card);

private:
	// The collection of cards in this deck
	std::deque<Card> cardDeck;
};
