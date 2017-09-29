// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "DiceRoller.h"
#include "Dice.h"
#include <iostream>
#include <iomanip>
#include <string>

DiceRoller::DiceRoller()
{
	totalRolls = 0;
	num1 = 0;
	num2 = 0;
	num3 = 0;
	num4 = 0;
	num5 = 0;
	num6 = 0;
}


DiceRoller::~DiceRoller()
{
}

//function call to roll up to 3 dice, as per the game rules
//and track the output of each dice in terms of the percentage of rolls. 
//Returns the rolls as an integer where of each digit represents one of the rolls. 

//EX: rollA = 2, rollB = 4, rollC = 1
//function will output 142.
int DiceRoller::roll(int numberOfDice)
{
	//variables to hold the roll values, initialized to 0, so that they dont affect the output the function will return.
	int rollA = 0;
	int rollB = 0;
	int rollC = 0;


	//switch case to determine how many times to roll the myDice object. If an invalid number of dice has been passed to the roll function, it will notify the user.
	switch (numberOfDice)
	{
	case 1:
		{
			rollA = myDice.roll();
			std::cout << rollA << std::endl;
			totalRolls++;

			break;
		}
	case 2:
		{
			rollA = myDice.roll();
			std::cout << rollA << std::endl;
			totalRolls++;
			rollB = myDice.roll();
			std::cout << rollB << std::endl;
			totalRolls++;

			break;
		}
	case 3:
		{
			rollA = myDice.roll();
			std::cout << rollA << std::endl;
			totalRolls++;
			rollB = myDice.roll();
			std::cout << rollB << std::endl;
			totalRolls++;
			rollC = myDice.roll();
			std::cout << rollC << std::endl;
			totalRolls++;

			break;
		}
	default:
		{
			std::cout << "Not a valid number of Dice have been rolled." << std::endl;
		}
	}

	//switch to increment the number of times each roll value has been rolled.
	switch (rollA)
	{
	case 1:
		{
			num1++;
			break;
		}
	case 2:
		{
			num2++;
			break;
		}
	case 3:
		{
			num3++;
			break;
		}
	case 4:
		{
			num4++;
			break;
		}
	case 5:
		{
			num5++;
			break;
		}
	case 6:
		{
			num6++;
			break;
		}
	default:
		{
			break;
		}
	}
	switch (rollB)
	{
	case 1:
		{
			num1++;
			break;
		}
	case 2:
		{
			num2++;
			break;
		}
	case 3:
		{
			num3++;
			break;
		}
	case 4:
		{
			num4++;
			break;
		}
	case 5:
		{
			num5++;
			break;
		}
	case 6:
		{
			num6++;
			break;
		}
	default:
		{
			break;
		}
	}
	switch (rollC)
	{
	case 1:
		{
			num1++;
			break;
		}
	case 2:
		{
			num2++;
			break;
		}
	case 3:
		{
			num3++;
			break;
		}
	case 4:
		{
			num4++;
			break;
		}
	case 5:
		{
			num5++;
			break;
		}
	case 6:
		{
			num6++;
			break;
		}
	default:
		{
			break;
		}
	}
	return rollC * 100 + rollB * 10 + rollA;
}

//prints out the percentage of each roll's likeliness.
void DiceRoller::showRolls() const
{
	std::cout << std::fixed;
	std::cout << std::setprecision(3);
	std::cout << "Total Number of Rolls: " << totalRolls << std::endl;
	std::cout << "Percent of 1s: " << num1 / totalRolls * 100 << std::endl;
	std::cout << "Percent of 2s: " << num2 / totalRolls * 100 << std::endl;
	std::cout << "Percent of 3s: " << num3 / totalRolls * 100 << std::endl;
	std::cout << "Percent of 4s: " << num4 / totalRolls * 100 << std::endl;
	std::cout << "Percent of 5s: " << num5 / totalRolls * 100 << std::endl;
	std::cout << "Percent of 6s: " << num6 / totalRolls * 100 << std::endl;
}
