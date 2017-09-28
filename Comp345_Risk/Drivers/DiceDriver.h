// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include "Driver.h"

class DiceDriver : public Driver
{
public:
	DiceDriver();
	~DiceDriver();
	void run() override;
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
};
