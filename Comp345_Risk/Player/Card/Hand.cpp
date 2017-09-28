
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


Exchangement Hand::exchange() {
	Exchangement ex{ true, {}, 0 };
	
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
			std::vector<Card>& handAtCardType = hand.at(CardType(i));
			ex.cardsExchanged.push_back(handAtCardType.back());
			handAtCardType.pop_back();
		}
	}
	ex.successfullyExchanged = canExchange;

	return exchangeForArmy(ex);
}

Exchangement Hand::exchange(CardType cardType) {
	Exchangement ex{ true,{}, 0 };
	// Exchange a CARD_EXCHANGE_AMOUNT cards of the same kind
	std::vector<Card>& handType = hand.at(cardType);
	if (handType.size() >= Hand::CARD_EXCHANGE_AMOUNT) {
		for (int i = 0; i < Hand::CARD_EXCHANGE_AMOUNT; i++) {
			ex.cardsExchanged.push_back(handType.back());
			handType.pop_back();
		}
	} else {
		// Can't exchange, there is not enough cards of the same type
		ex.successfullyExchanged = false;
	}
	return exchangeForArmy(ex);
}


void Hand::addCard(const Card& card) {
	hand.at(card.getCardType()).push_back(card);
}

Exchangement Hand::exchangeForArmy(Exchangement& exchangement) {
	if (exchangement.successfullyExchanged) {
		exchangement.armies = exchangeCount++ * Hand::ARMY_EXCHANGE_AMOUNT;
	} else {
		exchangement.armies = 0;
	}
	
	return exchangement;
}