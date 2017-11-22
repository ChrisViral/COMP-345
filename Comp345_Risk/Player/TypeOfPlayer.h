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

#pragma once

#include "Player.h"
//class Player;
class Country;

class TypeOfPlayer
{
public:
	virtual ~TypeOfPlayer() = 0;

	//This method should be run. But the other methods can be used for testing/demo
	virtual void playTurn(Player* player) = 0;

	virtual void reinforce(Player* player, bool skip = false);

	virtual void attack(Player* player, bool skip = false);

	virtual bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false);
};
