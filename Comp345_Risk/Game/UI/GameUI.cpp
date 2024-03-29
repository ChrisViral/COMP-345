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

#include "GameUI.h"


GameUI::GameUI(Game* game)
{
	this->game = game;
}

GameUI::~GameUI()
{
}


void GameUI::update()
{
}

void GameUI::attachDecorator(UIOutputDecorator* decorator)
{
	this->decorator = decorator;
}

Game* GameUI::getGame() const
{
	return game;
}
