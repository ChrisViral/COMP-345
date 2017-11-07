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
#include "../Map/RiskMap.h"
#include "../Patterns/Observer/Subject.h"

using std::vector;

enum GamePhase {
	attackPhase,
	reinforcePhase,
	fortifyPhase
};

class Game : public RiskObject, public Subject
{
public:

	Game();
	Game(vector<Player*>* players, RiskMap* map);
	~Game();
	void gameLoop();
	void setup();
	RiskMap* getMap() const;

	void setCurrentPlayerTurnAndPhase(Player* player, GamePhase phase);

private:
	std::pair<bool, Player*> checkWin() const;
	bool owned;
	int numPlayers;
	vector<Player*>* players;
	RiskMap* map;
	// Who is currently playing
	Player* currentPlayerTurn;
	// The current phase that the current player is in
	GamePhase currentPhase;
};
