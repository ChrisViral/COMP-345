// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once

#include "../Base/RiskObject.h"
#include <string>

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
