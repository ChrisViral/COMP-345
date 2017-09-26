#include "Continent.h"

Continent::Continent(std::string continentName, int controlVal)
{
	name = continentName;
	controlValue = controlVal;
}

Continent::~Continent()
{
}

std::string Continent::getName()
{
	return name;
}


int Continent::getControlValue()
{
	return controlValue;
}

void Continent::addCountry(Node node)
{
	countries.push_back(&node);
}