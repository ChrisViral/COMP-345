#pragma once
#include "../Base/RiskObject.h"


/*
 * CardType is the specialization for each card
 */
enum CardType {
	artillery,
	cavalry,
	infantry,
	// Special enum value to indicate how many card types there are for this Enum
	// Used when we are generating the deck of cards
	_Count = 3 
};


/*
 * A representation of a single card in a deck of cards
 * 
 * Each card has its own CardType enum
 */
class Card : public RiskObject {
public:
	// Creates a card with the specified CardType specialization
	Card(CardType);
	~Card();
	// Gets the card's specialization
	const CardType& getCardType() const;
private:
	// The CardType specialization
	CardType cardType;
};

