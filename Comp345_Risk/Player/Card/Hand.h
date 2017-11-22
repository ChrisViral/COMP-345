// ==============================
//           COMP-345 D
//          Assignment 3
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#pragma once

#include <vector>
#include "Card.h"
#include <unordered_map>
#include "Deck.h"

struct Exchangement
{
	bool successfullyExchanged;
	std::vector<Card> cardsExchanged;
	int armies;
};


class Hand : public RiskObject
{
public:
	Hand();
	explicit Hand(Deck* deck);
	~Hand();

	// The amount of cards to exchangeAll for some amount of army
	const static int CARD_EXCHANGE_AMOUNT;
	// The increment for armies to exchangeAll with
	const static int ARMY_EXCHANGE_AMOUNT;


	// Adds a card to our hand
	void addCard(const Card& card);
	Exchangement exchangeAll();
	// Exchange a CARD_EXCHANGE_AMOUNT cards of all different kinds
	Exchangement exchange();
	// Exchange a CARD_EXCHANGE_AMOUNT cards of the same kind
	Exchangement exchange(CardType cardType);

	//Display cards
	void displayCards();

private:

	Deck* deck;
	// The amount of times an exchangeAll has happened;
	static int exchangeCount;
	// The collection of cards is split up into each card type
	// for easier exchangeAll
	std::unordered_map<CardType, std::vector<Card>> hand;
	// Gets the amount of armies to exchangeAll our cards for
	Exchangement exchangeForArmy(Exchangement& exchangement);
};
