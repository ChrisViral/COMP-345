// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include "Driver.h"

class PlayerDriver : public Driver
{
public:
	PlayerDriver();
	~PlayerDriver();
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
	void run() override;
};
