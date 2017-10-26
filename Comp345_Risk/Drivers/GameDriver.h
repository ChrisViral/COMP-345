#pragma once
#include "../Base/Driver.h"

class GameDriver : public Driver
{
public:
	GameDriver();
	~GameDriver();
	void run() override;
	string getOpeningMessage() override;
	string getClosingMessage() override;
};

