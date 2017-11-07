#pragma once

#include "../Base/RiskObject.h"
#include "TypeOfPlayer.h"
#include <vector>

class AggressiveAI: public RiskObject, public TypeOfPlayer
{
public:
	~AggressiveAI();
	virtual void playTurn(Player* player);

	//This AI will reinforce its strongest country
	void reinforce(Player* player, bool skip = false);

	//This AI will attack untill it cannot attack anymore
	void attack(Player* player, bool skip = false);

	//This AI will fortify in order to maximize aggregation of forces in one country
	bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false);

	Country* getStrongestCountry() { return strongestCountry; }

private:
	Country* strongestCountry;
	std::vector<Country*> getAdjUnOwnedCountryList(Player* player, const Country& source);
	bool ownsCountry(Player* player, const Country& country) const;
	int defend(Country* country);
	Country* getFirstCountryWithExistingPath(Player* player, Country* strongestCountry);
	void handleBattle(Country* strongestCountry, Country* defendingCountry, int attackerRoll, int defenderRoll);
};
