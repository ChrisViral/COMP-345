// ==============================
//           COMP-345 D
//          Assignment 2
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#pragma once
#include <string>
#include "../../Base/RiskObject.h"


/*
 * CardType is the specialization for each card
 */
enum CardType
{
	artillery,
	cavalry,
	infantry,
	// Special enum value to indicate how many card types there are for this Enum
	// Used when we are generating the deck of cards
	_Count = 3
};

static std::string cardTypeEnumToString(const CardType& cardtype)
{
	switch (cardtype)
	{
	case artillery: return "artillery";
	case cavalry: return "cavalry";
	case infantry: return "infantry";
	default: return "";
	}
}


/*
 * A representation of a single card in a deck of cards
 * 
 * Each card has its own CardType enum
 */
class Card : public RiskObject
{
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
