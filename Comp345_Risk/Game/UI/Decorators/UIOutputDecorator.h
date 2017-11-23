// ==============================
//           COMP-345 D
//          Assignment 4
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

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
	GameUI* getUi() const;

private:
	std::unordered_map<UIDecorator, GameStatisticsDecorator*> decorators;

	Game* game;
	GameUI* decoratedUI;
};
