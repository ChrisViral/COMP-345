#pragma once
#include "../Base/Driver.h"

class GameStartDriver: public Driver
{
public:
	GameStartDriver();
	~GameStartDriver();
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
	void run() override;
};
