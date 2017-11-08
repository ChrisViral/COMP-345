#pragma once

#include "GameState.h"


#include <vector>
#include "GamePhase.h"

class Player;
class RiskMap;



class GameState {
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
};

