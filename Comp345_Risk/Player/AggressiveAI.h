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

#include "../Base/RiskObject.h"
#include "TypeOfPlayer.h"
#include <vector>

class AggressiveAI: public RiskObject, public TypeOfPlayer
{
public:
	~AggressiveAI();
	void playTurn(Player* player) override;

	//This AI will reinforce its strongest country
	void reinforce(Player* player, bool skip = false) override;

	//This AI will attack untill it cannot attack anymore
	void attack(Player* player, bool skip = false) override;

	//This AI will fortify in order to maximize aggregation of forces in one country
	bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false) override;

	Country* getStrongestCountry() { return strongestCountry; }

private:
	Country* strongestCountry;
	vector<Country*> getAdjUnOwnedCountryList(Player* player, const Country& source);
	bool ownsCountry(Player* player, const Country& country) const;
	int defend(Country* country);
	Country* getFirstCountryWithExistingPath(Player* player, Country* strongestCountry);
	void handleBattle(Country* strongestCountry, Country* defendingCountry, int attackerRoll, int defenderRoll);
};
