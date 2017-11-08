// ==============================
//           COMP-345 D
//          Assignment 2
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#pragma once
#include "Dice.h"
#include <string>

struct DiceRollCache {
	int rollA;
	int rollB;
	int rollC;
	int numberOfDice;
	std::string getOutputForNumberOfDice()
	{
		switch (numberOfDice)
		{
		case 1: return std::to_string(rollA) + "\n";
		case 2: return std::to_string(rollA) + "\n" + std::to_string(rollB);	
		case 3: return std::to_string(rollA) + "\n" + std::to_string(rollB) + "\n" +  std::to_string(rollC);
		}
		return {};
	}
};

class DiceRoller
{
public:
	DiceRoller();
	~DiceRoller();
	int roll(int numberOfDice); //function rolls a number of dice and returns a string containing the rolls.
	void showRolls() const; //prints out the total number of rolls and the percent of each rolls outcome.
	DiceRollCache getLastRoll();


private:
	Dice myDice;
	int totalRolls;
	float num1;
	float num2;
	float num3;
	float num4;
	float num5;
	float num6;
	DiceRollCache cache;


};
