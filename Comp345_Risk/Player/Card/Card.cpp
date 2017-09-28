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
