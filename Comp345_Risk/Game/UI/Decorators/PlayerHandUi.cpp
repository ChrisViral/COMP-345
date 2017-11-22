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
	std::cout << "______________________________________________________________________________________" << std::endl;
	std::cout << "PLAYER HAND UI" << std::endl;
	// TODO: custom decoration output for the player hand uis
	vector<Player*>* players = game->getPlayers();
	
	for (int i = 0; i < players->size(); i++)
	{
		std::cout << players->at(i)->getName() << std::endl;
		players->at(i)->getHand().displayCards();
		std::cout << std::endl;
	}
	
	std::cout << "______________________________________________________________________________________" << std::endl;
}



