#pragma once
#include "Driver.h"

class MapLoaderDriver
	: public Driver
{
public:
	MapLoaderDriver();
	~MapLoaderDriver();
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
	void run() override;
};
