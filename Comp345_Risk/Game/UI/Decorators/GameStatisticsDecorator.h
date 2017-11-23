#pragma once

#include "../GameUI.h"




class GameStatisticsDecorator : public GameUI
{
public:
	GameStatisticsDecorator(GameUI* decoratedUi);
	GameStatisticsDecorator();
	void setDecoratedUI(GameUI* decoratedUi);
	~GameStatisticsDecorator();
	virtual int getDecoratorUiEnum() = 0;
	bool enabled;
	void update() override;
	
protected:
	GameUI* decoratedUi;

};

