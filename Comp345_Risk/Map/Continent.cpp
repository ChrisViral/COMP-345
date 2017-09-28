// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "Continent.h"
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
			std::cout << "\t" << countries[i]->adjList[j].country.getName() << std::endl;
		}

		std::cout << std::endl;
	}
}
