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

class PassiveAI : public RiskObject, public TypeOfPlayer
{
public:
	void playTurn(Player* player) override;

	//This AI will reinforce its weakest countries
	void reinforce(Player* player, bool skip = false) override;

	//This AI will fortify in order to move armies to weaker countries
	bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false) override;

private:
	Country* weakestCountry;
	Country* getFirstCountryWithExistingPath(Player* player, Country* weakestCountry);
};
