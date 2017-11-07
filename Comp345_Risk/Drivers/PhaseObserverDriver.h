#pragma once

#include "../Base/Driver.h"

class PhaseObserverDriver : public Driver
{
public:
	PhaseObserverDriver();
	~PhaseObserverDriver();

	void run() override;
	string getOpeningMessage() override;
	string getClosingMessage() override;
};

