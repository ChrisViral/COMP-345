#pragma once
#include <unordered_map>
//#include "Game/UI/GameUI.h"
//#include "Game/UI/Decorators/GameStatisticsDecorator.h"

class Game;
class GameStatisticsDecorator;
class GameUI;

enum UIDecorator
{
	DominationUIDecorator,
	PlayerHandUIDecorator,
	ContinentControlUIDecorator
};

class UIOutputDecorator
{
public:
	UIOutputDecorator(Game* game);
	~UIOutputDecorator();
	void setDecoratorEnabled(UIDecorator decorator, bool enabled);
	void setDecoratorFlags(int octalFlag);
	GameUI* getUi();
	
private:
	std::unordered_map<UIDecorator, GameStatisticsDecorator*> decorators;
	
	Game* game;
	GameUI* decoratedUI;
};

