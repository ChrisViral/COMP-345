// ==============================
//           COMP-345 D
//          Assignment 2
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#pragma once

#include "../Base/RiskObject.h"
#include "../Player/Player.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"

class Game : public RiskObject
{
public:
	Game();
	~Game();
	void gameLoop();

private:
	bool checkWin(std::vector<Player*> players, RiskMap* map);
	RiskMap* map = new RiskMap();
	std::vector<Player*> players;
};
