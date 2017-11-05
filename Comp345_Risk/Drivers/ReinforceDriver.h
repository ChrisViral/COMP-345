#pragma once

#include "..\Base\Driver.h"

class ReinforceDriver : public Driver
{
public:
	ReinforceDriver();
	~ReinforceDriver();
	void run() override;
	string getOpeningMessage() override;
	string getClosingMessage() override;
};

