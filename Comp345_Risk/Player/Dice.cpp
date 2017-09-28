#include <cstdlib>
#include <ctime>
#include "Dice.h"



Dice::Dice() {
	// Create a new random seed on object creatio
	
	std::srand(std::time(NULL));
	// Pre roll the die, and cache roll
	lastRoll = roll();
}

Dice::~Dice() {

}

int Dice::roll() {
	lastRoll = (std::rand() % 6 + 1);
	return lastRoll;
}

int Dice::getLastRoll() const
{
	return lastRoll;
}
