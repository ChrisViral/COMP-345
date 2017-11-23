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

#include <ctime>
#include <cstdlib>
#include "Dice.h"


Dice::Dice()
{
	// Create a new random seed on object creatio

	srand(time(nullptr));
	// Pre roll the die, and cache roll
	lastRoll = roll();
}

Dice::~Dice()
{
}

int Dice::roll()
{
	lastRoll = rand() % 6 + 1;
	return lastRoll;
}

int Dice::getLastRoll() const
{
	return lastRoll;
}
