#include "Player/Dice.h"
#include "Player/DiceRoller.h"
#include <iostream>

int main()
{
	DiceRoller a; //creates a DiceRoller object
	for (int i = 0 ; i < 100; i++) //loops 100 times
	{
		a.roll(3); //rolls 3 dice and logs their rolls
		a.showRolls(); //prints out the log of the rolls, stating the total number of rolls, and the percentage of each rolls likely hood.
		std::cout << std::endl << std::endl; //skips two lines.
	}
	return 0;
}
