// ==============================
//           COMP-345 D
//          Assignment 4
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

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
