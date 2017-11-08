#pragma once
#include "GameUI.h"
#include "../Game.h"


class TextBasedUI : public GameUI
{
public:


	explicit TextBasedUI(Game* game)
		: GameUI(game) {
	}

	~TextBasedUI();
	void update() override;
};

