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

#include "Hand.h"
#include <iostream>

using std::vector;

// The amount of cards to exchangeAll for some amount of army
// The army exchangeAll amount is specified to 3
const int Hand::CARD_EXCHANGE_AMOUNT = 3;

// The increment for armies to exchangeAll with
const int Hand::ARMY_EXCHANGE_AMOUNT = 5;
// The amount of times an exchangeAll has happened;
int Hand::exchangeCount = 1;

Hand::Hand(): deck(nullptr)
{
}

Hand::Hand(Deck* deck)
{
	this->deck = deck;
	for (int i = 0; i != _Count; i++)
	{
		CardType cardType = static_cast<CardType>(i);
		hand.insert({cardType, vector<Card>()});
	}
}

Hand::~Hand()
{
	deck = nullptr;
}

Exchangement Hand::exchange()
{
	Exchangement ex{true, {}, 0};

	// Exchange a CARD_EXCHANGE_AMOUNT cards of all different kinds
	bool canExchange = true;
	for (int i = 0; i < CARD_EXCHANGE_AMOUNT; i++)
	{
		if (hand.at(CardType(i)).size() < 1)
		{
			canExchange = false;
			break;
		}
	}

	if (canExchange)
	{
		for (int i = 0; i < CARD_EXCHANGE_AMOUNT; i++)
		{
			vector<Card>& handAtCardType = hand.at(CardType(i));
			ex.cardsExchanged.push_back(handAtCardType.back());
			handAtCardType.pop_back();
		}
	}
	ex.successfullyExchanged = canExchange;

	return exchangeForArmy(ex);
}

Exchangement Hand::exchange(CardType cardType)
{
	Exchangement ex{true,{}, 0};
	// Exchange a CARD_EXCHANGE_AMOUNT cards of the same kind
	vector<Card>& handType = hand.at(cardType);
	if (handType.size() >= CARD_EXCHANGE_AMOUNT)
	{
		for (int i = 0; i < CARD_EXCHANGE_AMOUNT; i++)
		{
			ex.cardsExchanged.push_back(handType.back());
			handType.pop_back();
		}
	}
	else
	{
		// Can't exchangeAll, there is not enough cards of the same type
		ex.successfullyExchanged = false;
	}
	return exchangeForArmy(ex);
}

void Hand::displayCards()
{
	std::cout << "Amount of Infantry cards: " << hand[infantry].size() << std::endl;
	std::cout << "Amount of Artillery cards: " << hand[artillery].size() << std::endl;
	std::cout << "Amount of Cavalry cards: " << hand[cavalry].size() << std::endl;
}

void Hand::addCard(const Card& card)
{
	hand.at(card.getCardType()).push_back(card);
}

Exchangement Hand::exchangeAll()
{
	//Try to exchange three different types
	Exchangement ex = exchange();
	int i = 0;

	//Try to exchange three of a kind
	while (!ex.successfullyExchanged && i != _Count)
	{
		ex = exchange(static_cast<CardType>(i++));
	}

	//Put cards back into the deck
	if (ex.successfullyExchanged)
	{
		for (Card c : ex.cardsExchanged)
		{
			deck->addCard(c);
		}
	}

	//Return the result
	return ex;
}

Exchangement Hand::exchangeForArmy(Exchangement& exchangement) const
{
	if (exchangement.successfullyExchanged)
	{
		exchangement.armies = exchangeCount++ * ARMY_EXCHANGE_AMOUNT;
	}
	else
	{
		exchangement.armies = 0;
	}

	return exchangement;
}
