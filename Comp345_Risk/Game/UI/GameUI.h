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
#include "../../Patterns/Observer/Observer.h"
#include "../Game.h"
//class UIOutputDecorator;
#include "Decorators/UIOutputDecorator.h"


class GameUI : public Observer
{
public:
	GameUI() : game(nullptr)
	{
	}

	virtual ~GameUI();
	void update() override;
	// hacx
	void attachDecorator(UIOutputDecorator* decorator);
	Game* getGame() const;
protected:
	GameUI(Game* game);
	Game* game;
	UIOutputDecorator* decorator;
};
