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

#pragma once
#include "../GameUI.h"


class TextBasedUI : public GameUI
{
public:


	explicit TextBasedUI(Game* game)
		: GameUI(game)
	{
	}

	~TextBasedUI();
	void update() override;
};
