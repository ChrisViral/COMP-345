#pragma once
#include <unordered_map>
#include "Game/UI/GameUI.h"
#include "Game/UI/Decorators/GameStatisticsDecorator.h"

class Game;
class GameStatisticsDecorator;

enum UIDecorator
{
	DominationUIDecorator,
	PlayerHandUIDecorator,
	ContinentControlUIDecorator
};

class UIOutput
{
public:
	UIOutput(Game* game);
	~UIOutput();
	void setDecoratorEnabled(UIDecorator decorator, bool enabled);
	GameUI* getUi();
	
private:
	std::unordered_map<UIDecorator, GameStatisticsDecorator*> decorators;
	
	Game* game;
	GameUI* decoratedUI;
};

