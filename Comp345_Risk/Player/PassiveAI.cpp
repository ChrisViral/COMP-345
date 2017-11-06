#include "PassiveAI.h"
#include "../Player/Player.h"


void PassiveAI::playTurn(Player * player)
{
	reinforce(player);
	//fortify(player);
}

void PassiveAI::reinforce(Player* player, bool skip)
{
}

bool PassiveAI::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	return false;
}