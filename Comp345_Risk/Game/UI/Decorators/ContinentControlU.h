#pragma once
#include "GameStatisticsDecorator.h"

class ContinentControlUI : public GameStatisticsDecorator
{
public:


	explicit ContinentControlUI(GameUI* decoratedUi)
		: GameStatisticsDecorator(decoratedUi)
	{
	}


	ContinentControlUI() {
	}

	~ContinentControlUI();
	int getDecoratorUiEnum() override;
	void update() override;

	
};

