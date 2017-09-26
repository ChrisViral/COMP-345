#include "CardDistributor.h"



/*
 *
 *  // TODO: Code to be put in the driver
	Deck deck(42);
	Hand h1;
	Hand h2;
	Hand h3;

	std::vector<std::reference_wrapper<Hand>> hands;
	hands.push_back(h1);
	hands.push_back(h2);
	hands.push_back(h3);

	CardDistributor dist(deck, hands);


	std::cout << h1.exchange() << std::endl;
	std::cout << h1.exchange() << std::endl;
	std::cout << h2.exchange() << std::endl;
	std::cout << h3.exchange() << std::endl;
 */

CardDistributor::CardDistributor(Deck& deck, std::vector<std::reference_wrapper<Hand>> hands) {
	int handCount = hands.size();
	int deckSize = deck.getDeckSize();

	for (int i = 0; i < deckSize; i++) {
		const Card& card = deck.draw();
		hands[i % handCount].get().addCard(card);
	}
	
		
}



CardDistributor::~CardDistributor() {
}
