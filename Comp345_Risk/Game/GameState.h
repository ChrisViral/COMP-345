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

#include "GameState.h"


#include <vector>
#include "GamePhase.h"

class Player;
class RiskMap;


class GameState
{
public:

	GameState();
	~GameState();

	// TODO(Steven) move all this to const or private with getter/setters
	bool owned;

	int numPlayers;
	std::vector<Player*>* players;
	RiskMap* map;
	Player* currentPlayerTurn;
	GamePhase currentPhase;
	std::vector<std::string>* recentActions;
	int turnNumber;
};
