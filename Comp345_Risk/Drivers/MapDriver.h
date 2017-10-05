// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include "../Base/Driver.h"

class MapDriver : public Driver
{
public:
	MapDriver();
	~MapDriver();
	void run() override;
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
};
