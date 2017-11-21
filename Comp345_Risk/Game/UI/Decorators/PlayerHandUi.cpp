#include "PlayerHandUi.h"
#include <iostream>


PlayerHandUi::~PlayerHandUi()
{
}

int PlayerHandUi::getDecoratorUiEnum()
{
	return UIDecorator::PlayerHandUIDecorator;
}

void PlayerHandUi::update()
{
	decoratedUi->update();
	if (!enabled) return;
	std::cout << "------------------------------" << std::endl;
	std::cout << "PLAYER HAND UI" << std::endl;
	// TODO: custom decoration output for the player hand uis
	std::cout << "------------------------------" << std::endl;
}



