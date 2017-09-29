// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "Card.h"


Card::Card(CardType cardType)
{
	this->cardType = cardType;
}

Card::~Card()
{
}

const CardType& Card::getCardType() const
{
	return cardType;
}
