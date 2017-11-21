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
#include "../../Patterns/Observer/Observer.h"
#include "../Game.h"
#include "../GameState.h"
#include "../../Player/Player.h"

class Game;

class GameUI : public Observer
{
public:
	GameUI() : game(nullptr)
	{
	}

	virtual ~GameUI();
	void update() override;
	Game* getGame();
protected:
	GameUI(Game* game);
	Game* game;
};
