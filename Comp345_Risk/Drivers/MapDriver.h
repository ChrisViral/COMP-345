#pragma once
#include "Driver.h"

class MapDriver : public Driver
{
public:
	MapDriver();
	~MapDriver();
	void run() override;
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
};