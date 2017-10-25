#pragma once
#include "Base/Driver.h"

class FortificationDriver : public Driver
{
public:
	FortificationDriver();
	~FortificationDriver();
	void run() override;
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
};

