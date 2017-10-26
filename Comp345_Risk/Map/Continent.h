// ==============================
//           COMP-345 D
//          Assignment 2
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

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
	bool ownedBy(const Player* player);

private:
	int controlValue;
	std::string name;
	std::vector<Node*> countries;
};
