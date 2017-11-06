#include "PassiveAI.h"

void PassiveAI::playTurn(Player * player)
{
	reinforce(player);
	fortify(player);
}

void PassiveAI::reinforce(Player* player, bool skip)
{
}

bool PassiveAI::fortify(Player* player, bool skip)
{
	return false;
}