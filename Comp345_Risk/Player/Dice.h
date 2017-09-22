#pragma once

#include "../Base/RiskObject.h"

class Dice : public RiskObject {

public:
	Dice();
	~Dice();
	int roll();
	int getLastRoll();

private:
	int lastRoll;
};

