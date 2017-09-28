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