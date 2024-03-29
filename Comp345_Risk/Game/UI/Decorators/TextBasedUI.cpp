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

#include "TextBasedUI.h"
#include "../../../Player/Player.h"
#include "../../GameState.h"
#include <iostream>


TextBasedUI::~TextBasedUI()
{
}

void TextBasedUI::update()
{
	GameState state = game->getGameState();
	this->decorator->setDecoratorFlags(state.decoratorFlag);


	std::cout << "______________________________________________________________________________________" << std::endl;
	std::cout << "Undecorated UI" << std::endl;

	std::cout << "Current Turn# " << state.turnNumber << std::endl;
	std::cout << state.currentPlayerTurn->getName() << ": " << gamePhaseToString(state.currentPhase) << std::endl;

	for (int i = 0; i < state.recentActions->size(); i++)
	{
		std::cout << state.recentActions->at(i) << std::endl;
	}

	state.recentActions->clear();

	std::cout << "______________________________________________________________________________________" << std::endl;
}
