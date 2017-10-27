#pragma once

#include "..\Base\Driver.h"
#include "../Map/Country.h"

class AttackDriver: public Driver
{
public:
	AttackDriver();
	~AttackDriver();
	void run() override;
	string getOpeningMessage() override;
	string getClosingMessage() override;
};