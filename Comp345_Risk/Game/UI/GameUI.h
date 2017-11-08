#pragma once
#include "../../Patterns/Observer/Observer.h"
#include "../Game.h"
#include "../GameState.h"
#include "../../Player/Player.h"

class Game;

class GameUI : public Observer 
{
public:
	virtual ~GameUI();
	virtual void update();
protected:
	GameUI(Game* game);
	Game* game;

};

