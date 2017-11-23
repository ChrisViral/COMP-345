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









