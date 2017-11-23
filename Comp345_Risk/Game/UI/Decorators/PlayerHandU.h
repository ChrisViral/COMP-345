#pragma once
#include "GameStatisticsDecorator.h"
#include "../GameUI.h"




class PlayerHandUI : public GameStatisticsDecorator
{
public:

	explicit PlayerHandUI(GameUI* decoratedUi)
		: GameStatisticsDecorator(decoratedUi)
	{
	}


	PlayerHandUI() {
	}

	~PlayerHandUI();

	int getDecoratorUiEnum() override;
	void update() override;
};

