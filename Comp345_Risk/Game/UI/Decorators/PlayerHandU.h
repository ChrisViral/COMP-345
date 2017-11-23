#pragma once
#include "GameStatisticsDecorator.h"
#include "../GameUI.h"




class PlayerHandUi : public GameStatisticsDecorator
{
public:

	explicit PlayerHandUi(GameUI* decoratedUi)
		: GameStatisticsDecorator(decoratedUi)
	{
	}


	PlayerHandUi() {
	}

	~PlayerHandUi();

	int getDecoratorUiEnum() override;
	void update() override;
};

