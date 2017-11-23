// ==============================
//           COMP-345 D
//          Assignment 4
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

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
	Country* getRandomAndRemove(vector<Country*>& countries) const;

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
