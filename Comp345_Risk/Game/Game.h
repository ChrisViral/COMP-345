#pragma once

#include "../Base/RiskObject.h"
#include "../Player/Player.h"
#include "../Map/RiskMap.h"

using std::vector;

class Game : public RiskObject
{
public:
	Game();
	~Game();
private:
	vector<Player> players;
	RiskMap map;
};

