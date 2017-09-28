#pragma once
#include "Dice.h"

class DiceRoller
{
public:
	DiceRoller();
	~DiceRoller();
	int roll(int numberOfDice); //function rolls a number of dice and returns a string containing the rolls.
	void showRolls(); //prints out the total number of rolls and the percent of each rolls outcome.

private:
	Dice myDice;
	int totalRolls;
	float num1;
	float num2;
	float num3;
	float num4;
	float num5;
	float num6;
};
