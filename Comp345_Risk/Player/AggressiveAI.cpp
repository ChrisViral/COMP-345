#include "AggressiveAI.h"
#include <iostream>

void AggressiveAI::playTurn(Player * player)
{
	reinforce(player);
	attack(player);
	fortify(player);
}

void AggressiveAI::reinforce(Player* player, bool skip)
{
	std::cout << "fewfw" << std::endl;
}

void AggressiveAI::attack(Player* player, bool skip)
{
}

bool AggressiveAI::fortify(Player* player, bool skip)
{
	return false;
}
