#pragma once

#include <vector>
#include "../Base/RiskObject.h"
#include "../Map/RiskMap.h"

class Country;
struct Node;

class Continent : public RiskObject
{
public:
	Continent(std::string continentName, int controlVal);
	~Continent();
	int getControlValue();
	void addCountry(Node country);
	std::string getName();

private:
	int controlValue;
	std::string name;
	std::vector<Node*> countries;
};

