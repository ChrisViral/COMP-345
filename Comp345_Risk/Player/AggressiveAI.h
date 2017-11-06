#pragma once

#include "../Base/RiskObject.h"
#include "TypeOfPlayer.h"

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
	bool fortify(Player* player, bool skip = false);
};
