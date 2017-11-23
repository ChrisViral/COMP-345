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

#include "GameStatisticsDecorator.h"


GameStatisticsDecorator::GameStatisticsDecorator(GameUI* decoratedUi)
{
	setDecoratedUI(decoratedUi);
	enabled = false;
}

GameStatisticsDecorator::GameStatisticsDecorator()
{
	enabled = false;
}

GameStatisticsDecorator::~GameStatisticsDecorator()
{
	
}

void GameStatisticsDecorator::update()
{
	decoratedUi->update();
}

void GameStatisticsDecorator::setDecoratedUI(GameUI* decoratedUi)
{
	this->decoratedUi = decoratedUi;
	this->game = decoratedUi->getGame();
}









