// ==============================
//           COMP-345 D
//          Assignment 3
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#include "TypeOfPlayer.h"
#include "../Map/Country.h"
#include <iostream>
#include <functional>

void TypeOfPlayer::reinforce(Player* player, bool skip)
{
	player->getGame()->setCurrentPlayerTurnAndPhase(player, reinforcePhase);
}

void TypeOfPlayer::attack(Player* player, bool skip)
{
	player->getGame()->setCurrentPlayerTurnAndPhase(player, attackPhase);
}

bool TypeOfPlayer::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	player->getGame()->setCurrentPlayerTurnAndPhase(player, fortifyPhase);
	return false;
}
