#pragma once
#include "TypeOfPlayer.h"

using std::pair;

class RandomPlayer : public TypeOfPlayer
{
public:
	~RandomPlayer();
	void playTurn(Player* player) override;
	void reinforce(Player* player, bool skip = false) override;
	void attack(Player* player, bool skip = false) override;
	bool fortify(Player* player);
	bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false) override;
	void battle(pair<Country*, Country*> countries, int attackerRoll, int defenderRoll);

private:
	/*
	 * Random value between 0 and the max (exclusive)
	 */
	static int randomRange(int max)
	{
		return rand() % max;
	}

	/*
	 * Randomvalue between the min and max values inclusively
	 */
	static int randomRange(int min, int max)
	{
		return (rand() % (max - min + 1)) + min;
	}
};
