// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once

#include <vector>
#include "../Base/RiskObject.h"
#include "RiskMap.h"

class Country;
struct Node;

class Continent : public RiskObject
{
public:
	Continent(std::string continentName, int controlVal);
	~Continent();
	int getControlValue() const;
	void addCountry(Node& country);
	std::string getName() const;
	void traverseCountries();

private:
	int controlValue;
	std::string name;
	std::vector<Node*> countries;
};
