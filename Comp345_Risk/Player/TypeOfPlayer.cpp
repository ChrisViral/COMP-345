#include "TypeOfPlayer.h"
#include "../Map/Country.h"
#include <iostream>

void TypeOfPlayer::reinforce(Player* player, bool skip)
{
	std::cout << "This kind of player doesn't have a reinforce method yet" << std::endl;
}

void TypeOfPlayer::attack(Player* player)
{
	std::cout << "This kind of player doesn't have a attack method yet" << std::endl;
}

bool TypeOfPlayer::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	std::cout << "This kind of player doesn't have a fortify method yet" << std::endl;
	return false;
}