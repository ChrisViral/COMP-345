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
