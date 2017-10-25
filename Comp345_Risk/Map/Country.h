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

class Continent;
class Player;

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
	void setX(int val);
	void setY(int val);

private:
	Continent* continent;
	std::string name;
	int armies;
	// TODO: do we want to keep this pointer or just remove it?
	// TODO: owner is not set yet. Needs to be implemented when handing out the countries
	Player* owner;
	int x;
	int y;
};
