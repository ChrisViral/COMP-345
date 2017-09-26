
#include "Hand.h"

// The amount of cards to exchange for some amount of army
// The army exchange amount is specified to 3
const int Hand::CARD_EXCHANGE_AMOUNT = 3;

// The increment for armies to exchange with
const int Hand::ARMY_EXCHANGE_AMOUNT = 5;
// The amount of times an exchange has happened;
int Hand::exchangeCount = 1;

Hand::Hand() {
	for (int i = 0; i != CardType::_Count; i++) {
		CardType cardType = static_cast<CardType>(i);
		hand.insert({ cardType, std::vector<Card>() });
	}
}


Hand::~Hand() {
}


int Hand::exchange() {
	// Exchange a CARD_EXCHANGE_AMOUNT cards of all different kinds
	bool canExchange = true;
	for (int i = 0; i < CARD_EXCHANGE_AMOUNT; i++) {
		if (hand.at(CardType(i)).size() < 1) {
			canExchange = false;
			break;
		};
	}

	if (canExchange) {
		for (int i = 0; i < CARD_EXCHANGE_AMOUNT; i++) {
			hand.at(CardType(i)).pop_back();
		}
		
	} else {
		// Can't exchange, there is not 3 cards of different type
	}

	return exchangeForArmy();
}

int Hand::exchange(CardType cardType) {
	// Exchange a CARD_EXCHANGE_AMOUNT cards of the same kind
	std::vector<Card>& handType = hand.at(cardType);
	if (handType.size() >= Hand::CARD_EXCHANGE_AMOUNT) {
		for (int i = 0; i < Hand::CARD_EXCHANGE_AMOUNT; i++) {
			handType.pop_back();
		}
	} else {
		// Can't exchange, there is not enough cards of the same type
	}
	return exchangeForArmy();
}


void Hand::addCard(const Card& card) {
	hand.at(card.getCardType()).push_back(card);
}

int Hand::exchangeForArmy() {
	return exchangeCount++ * Hand::ARMY_EXCHANGE_AMOUNT;
}
