#pragma once

#include "../Base/RiskObject.h"
#include "../Player/Player.h"

class Continent;

class Country : public RiskObject
{
public:
	Country();
	Country(std::string countryName, Continent& cont);
	Country(std::string countryName, Continent& cont, int x, int y);
	~Country();
	Continent* getContinent();
	std::string getName();
	int getArmies();
	void addArmies(int amount);
	void removeArmies(int amount);
	Player* getOwner();
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
