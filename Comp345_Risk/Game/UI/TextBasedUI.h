#pragma once
#include "GameUI.h"

class TextBasedUI : public GameUI
{
public:
	TextBasedUI();
	~TextBasedUI();
	void update() override;
};

