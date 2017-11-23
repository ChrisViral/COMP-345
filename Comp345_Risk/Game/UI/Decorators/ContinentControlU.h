#pragma once
#include "GameStatisticsDecorator.h"

class ContinentControlUi : public GameStatisticsDecorator
{
public:


	explicit ContinentControlUi(GameUI* decoratedUi)
		: GameStatisticsDecorator(decoratedUi)
	{
	}


	ContinentControlUi() {
	}

	~ContinentControlUi();
	int getDecoratorUiEnum() override;
	void update() override;

	
};

