#pragma once
#include "../Base/Driver.h"

class StrategyDriver : public Driver
{
public:
	StrategyDriver();
	~StrategyDriver();
	void run() override;
	string getOpeningMessage() override;
	string getClosingMessage() override;
};

