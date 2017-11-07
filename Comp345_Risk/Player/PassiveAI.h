#pragma once

#include "../Base/RiskObject.h"
#include "TypeOfPlayer.h"

class PassiveAI : public RiskObject, public TypeOfPlayer
{
public:
	virtual void playTurn(Player* player);

	//This AI will reinforce its weakest countries
	void reinforce(Player* player, bool skip = false);

	//This AI will fortify in order to move armies to weaker countries
	bool fortify(Player* player, Country& source, Country& target, int amount, bool skip = false);

private:
	Country* weakestCountry;
	Country* getFirstCountryWithExistingPath(Player* player, Country* weakestCountry);

};
