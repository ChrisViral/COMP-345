#pragma once

#include "../Base/Driver.h"

class DecoratedStatisticsDriver : public Driver{
public:
	DecoratedStatisticsDriver();
	~DecoratedStatisticsDriver();

	void run() override;
	string getOpeningMessage() override;
	string getClosingMessage() override;
};

