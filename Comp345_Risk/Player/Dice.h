// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include "../Base/RiskObject.h"

class Dice : public RiskObject
{
public:
	Dice();
	~Dice();
	int roll();
	int getLastRoll() const;

private:
	int lastRoll;
};
