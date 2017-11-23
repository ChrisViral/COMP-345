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

#include "Continent.h"
#include "../Player/Player.h"
#include <iostream>

Continent::Continent(std::string continentName, int controlVal)
{
	name = continentName;
	controlValue = controlVal;
}

Continent::~Continent()
{
}

std::string Continent::getName() const
{
	return name;
}


int Continent::getControlValue() const
{
	return controlValue;
}

void Continent::addCountry(Node& node)
{
	countries.push_back(&node);
}

void Continent::traverseCountries()
{
	for (int i = 0; i < countries.size(); i++)
	{
		std::cout << countries[i]->country->getName() << std::endl;

		for (int j = 0; j < countries[i]->adjList.size(); j++)
		{
			std::cout << "\t" << countries[i]->adjList[j].country->getName() << std::endl;
		}

		std::cout << std::endl;
	}
}


bool Continent::ownedBy(const Player* player)
{
	for (Node* n : countries)
	{
		if (n->country->getOwner()->getName() != player->getName())
		{
			return false;
		}
	}
	return true;
}

vector<Node*> Continent::getCountries() const
{
	return countries;
}
