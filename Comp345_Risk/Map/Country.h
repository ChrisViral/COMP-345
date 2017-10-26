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

#include "../Base/RiskObject.h"
#include <string>
#include "RiskMap.h"

class Player;
class Continent;

class Country : public RiskObject
{
public:
	Country();
	Country(std::string countryName, Continent& cont);
	Country(std::string countryName, Continent& cont, int x, int y);
	~Country();
	Continent* getContinent() const;
	std::string getName() const;
	int getArmies() const;
	void addArmies(int amount);
	void removeArmies(int amount);
	Player* getOwner() const;

	void setOwner(Player* player);
	void setX(int val);
	void setY(int val);

private:
	Continent* continent;
	std::string name;
	int armies;
	Player* owner;
	int x;
	int y;
};
