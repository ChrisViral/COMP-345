#include "../Player/DiceRoller.h"
#include <iostream>
#include "DiceDriver.h"

DiceDriver::DiceDriver() { }
DiceDriver::~DiceDriver() { }

std::string DiceDriver::getOpeningMessage()
{
	return "Starting Dice driver";
}

std::string DiceDriver::getClosingMessage()
{
	return "Ending Dice driver";
}

void DiceDriver::run()
{
	DiceRoller a; //creates a DiceRoller object
	for (int i = 0 ; i < 100; i++) //loops 100 times
	{
		a.roll(3); //rolls 3 dice and logs their rolls
		a.showRolls(); //prints out the log of the rolls, stating the total number of rolls, and the percentage of each rolls likely hood.
	}
}
