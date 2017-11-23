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
#include "../Base/RiskObject.h"
#include "../Map/Country.h"
#include "../Game/Game.h"
#include "TypeOfPlayer.h"

class Human : public RiskObject, public TypeOfPlayer
{
public:
	Human();
	~Human();

	void playTurn(Player* player) override;

	//Player is given choice to place an allocated amount of troops (based on the countries he owns, the continents he controls
	//and cards he has on hand on any of his territories to reinforce them before attacking.
	void reinforce(Player* player, bool skip = false) override;

	//Method allows currentPlayerTurn to roll and take over countries adjacent to his own territories. Method ends when currentPlayerTurn 
	//decided or when he know longer has a territory with more than one troop remaining positioned on it.
	void attack(Player* player, bool skip = false) override;
	void attack(Player* player, Country& source, Country& target, bool skip = false);
	void fortify(Player* player);

	// If the amount given is larger or equal than the source country owns, then it will return false and no armies will be exchanged
	// If the amount if smaller, then it will exhange and return true
	// From the official rules, we must leave at least 1 army in the source country
	// We can't pull out all of our armies
	bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false) override;

	Country* chooseAttackSourceCountry(Player* player) const;
	Country* chooseAttackTargetCountry(Player* player, Country& source);
	Country* chooseFortifySourceCountry(Player* player) const;
	vector<Country*> getConnectedOwnedCountryList(Player* player, Country& source) const;
	Country* chooseFortifyTargetCountry(Player* player, Country& source) const;
	bool hasAdjUnOwnedCountry(Player* player, const Country& source) const;
	bool ownsCountry(Player* player, const Country& country) const;
	vector<Country*> getAdjUnOwnedCountryList(Player* player, const Country& source) const;
};
