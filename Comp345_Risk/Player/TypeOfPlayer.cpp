#include "TypeOfPlayer.h"
#include "../Map/Country.h"
#include <iostream>
#include <functional>

void TypeOfPlayer::reinforce(Player* player, bool skip)
{
	player->getGame()->setCurrentPlayerTurnAndPhase(player, GamePhase::reinforcePhase);
}

void TypeOfPlayer::attack(Player* player, bool skip)
{
	player->getGame()->setCurrentPlayerTurnAndPhase(player, GamePhase::attackPhase);
	
}

bool TypeOfPlayer::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	player->getGame()->setCurrentPlayerTurnAndPhase(player, GamePhase::fortifyPhase);
	return false;
}