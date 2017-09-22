
#include "Dice.h"
#include <stdlib.h>
#include <ctime>


Dice::Dice() {
	// Create a new random seed on object creation
	srand(time(NULL));
	// Pre roll the die, and cache roll
	lastRoll = roll();
}

Dice::~Dice() {

}

int Dice::roll() {
	lastRoll = (rand() % 6 + 1);
	return lastRoll;
}

int Dice::getLastRoll() {
	return lastRoll;
}
