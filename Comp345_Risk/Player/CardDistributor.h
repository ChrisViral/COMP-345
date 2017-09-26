#pragma once
#include "Hand.h"
#include "Deck.h"


class CardDistributor {
public:
	CardDistributor(Deck& deck, std::vector<std::reference_wrapper<Hand>> hands);
	~CardDistributor();
};

