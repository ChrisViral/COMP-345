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

#include "ContinentControlUI.h"
#include <iostream>
#include "UIOutputDecorator.h"


void ContinentControlUI::update()
{
	decoratedUi->update();
	if (!enabled) return;
	std::cout << "______________________________________________________________________________________" << std::endl;
	std::cout << "Continent Control UI" << std::endl;
	// TODO: custom decoration output for the continent control
	std::unordered_map<std::string, Continent> map = game->getGameState().map->getContinents();
	std::vector<Player*>* players = game->getGameState().players;
	for (std::unordered_map<std::string, Continent>::value_type it : map)
	{
		for (int i = 0 ; i < players->size(); i++) {
			if (it.second.ownedBy(players->at(i))) {
				std::cout << players->at(i)->getName() << " owns " << it.second.getName() << std::endl;
			} else {
				// TODO(Steven): remove when we get some output for when a player does have it
				std::cout << it.second.getName() << " is not owned by player " << players->at(i)->getName() << std::endl;
			}	
		}
	}
	std::cout << "______________________________________________________________________________________" << std::endl;
}

int ContinentControlUI::getDecoratorUiEnum()
{
	return UIDecorator::ContinentControlUIDecorator;
}

ContinentControlUI::~ContinentControlUI()
{
}

