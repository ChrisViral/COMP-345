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

#include <vector>
#include "Base/RiskObject.h"
#include "Player/TypeOfPlayer.h"

class CheaterAI : public RiskObject, public TypeOfPlayer
{
public:
	~CheaterAI();
	void playTurn(Player* player) override;

	//This AI will reinforce its strongest country
	void reinforce(Player* player, bool skip = false) override;

	//This AI will attack untill it cannot attack anymore
	void attack(Player* player, bool skip = false) override;

	//This AI will fortify in order to maximize aggregation of forces in one country
	bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false) override;	

private:
	vector<Country*> getAdjUnOwnedCountryList(Player* player, const Country& source);
	bool hasAdjUnOwnedCountry(Player* player, const Country& source);
	bool ownsCountry(Player* player, const Country& country) const;
	int defend(Country* country);
	int getTotalArmies(Player* player);
	vector<Country*> getFringeCountries(Player* player);
	void redistributeArmiesToFringes(Player* player, vector<Country*> fringes, int totalCountries);
	vector<Country*> getTargets(Player* player);
};
