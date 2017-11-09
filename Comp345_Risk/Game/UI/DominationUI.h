#pragma once

#include "GameUI.h"

class DominationUI : public GameUI
{
public:
	explicit DominationUI(Game* game);
	~DominationUI();
	void update() override;
};
