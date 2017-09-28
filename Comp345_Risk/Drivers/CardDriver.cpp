// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "CardDriver.h"
#include <iostream>
#include "../Player/Card/Deck.h"

CardDriver::CardDriver()
{
}

CardDriver::~CardDriver()
{
}

std::string CardDriver::getOpeningMessage()
{
	return "Ending Card driver";
}

std::string CardDriver::getClosingMessage()
{
	return "Starting Card driver";
}

void CardDriver::printExchangement(Exchangement& ex)
{
	std::cout << std::endl;
	std::cout << "Successfully Exchanged: " << ex.successfullyExchanged << std::endl;
	std::cout << "Cards Exchanged: {";
	for (int i = 0; i < ex.cardsExchanged.size(); i++)
	{
		std::cout << cardTypeEnumToString(ex.cardsExchanged[i].getCardType()) << ", ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Armies exchanged: " << ex.armies << std::endl;
}

void CardDriver::run()
{
	// This will be taken from how many countries are in the map 
	// once all the parts are together
	// for now, the card count is specified just for the driver
	int cardAmount = 100;
	// Create a deck of cards
	Deck deck1(cardAmount);

	// Create a map to hold the statistics
	std::unordered_map<CardType, int> cardStats;

	// Prefill the stats with zeros
	for (int i = 0; i < _Count; i++)
	{
		cardStats.insert({CardType(i), 0});
	}

	// Draw all the cards of the deck
	for (int i = 0; i < cardAmount; i++)
	{
		const Card& card = deck1.draw();
		// Count the cards drawn
		cardStats.at(card.getCardType())++;
	}


	// Print out the card stats
	for (auto it = cardStats.begin(); it != cardStats.end(); ++it)
	{
		std::cout << cardTypeEnumToString(it->first) << ", Count: " << it->second << std::endl;
	}


	// Create another deck to test hand objects
	Deck deck2(cardAmount);

	Hand h1;
	Hand h2;

	// Let both hands draw from the deck
	for (int i = 0; i < cardAmount / 2; i++)
	{
		const Card& c1 = deck2.draw();
		const Card& c2 = deck2.draw();

		h1.addCard(c1);
		h2.addCard(c2);
	}

	// Exchange cards for armies
	Exchangement e1 = h1.exchange();
	Exchangement e2 = h1.exchange(artillery);

	Exchangement e3 = h2.exchange();
	Exchangement e4 = h2.exchange(infantry);

	printExchangement(e1);
	printExchangement(e2);
	printExchangement(e3);
	printExchangement(e4);

	deck2.addCard(e1.cardsExchanged[0]);
	deck2.addCard(e1.cardsExchanged[1]);
	deck2.addCard(e1.cardsExchanged[2]);
}
