#pragma once
#include "../Base/Driver.h"

class StatisticsDriver : public Driver
{
public:
	StatisticsDriver();
	~StatisticsDriver();
	void run() override;
	string getOpeningMessage() override;
	string getClosingMessage() override;
};
