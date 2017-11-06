#pragma once

//#include "Player.h"
class Player;
class Country;

class TypeOfPlayer
{
public:
	//This method should be run. But the other methods can be used for testing/demo
	virtual void playTurn(Player* player) = 0;

	virtual void reinforce(Player* player, bool skip = false);

	virtual void attack(Player* player, bool skip = false);

	virtual bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false);
};
