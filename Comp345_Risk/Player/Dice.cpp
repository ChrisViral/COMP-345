// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

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
