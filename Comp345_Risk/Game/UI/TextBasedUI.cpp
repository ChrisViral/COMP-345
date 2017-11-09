#include "TextBasedUI.h"
#include <iostream>




TextBasedUI::~TextBasedUI()
{
}

void TextBasedUI::update()
{
	
	GameState state = game->getGameState();
	std::cout << "================================" << std::endl;
	std::cout << state.currentPlayerTurn->getName() << ": " << gamePhaseToString(state.currentPhase) << std::endl;
	
	for (int i = 0; i < state.recentActions->size(); i++) {
		std::cout << state.recentActions->at(i) << std::endl;
	}

	state.recentActions->clear();

	std::cout << "================================" << std::endl;
	
}