// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include "../Player/Card/Hand.h"
#include "Driver.h"

class CardDriver : public Driver
{
public:
	CardDriver();
	~CardDriver();
	void run() override;
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
	static void printExchangement(Exchangement& ex);
};
