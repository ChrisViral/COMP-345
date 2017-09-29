// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "Country.h"

Country::Country() : continent(nullptr), armies(0)/*,owner(nullptr)*/, x(0), y(0)
{
}

Country::Country(std::string countryName, Continent& cont) : /*owner(nullptr),*/x(0), y(0)
{
	name = countryName;
	continent = &cont;
	armies = 0;
}

Country::Country(std::string countryName, Continent& cont, int x, int y) : Country(countryName, cont)
{
	this->x = x;
	this->y = y;
}

Country::~Country()
{
}

Continent* Country::getContinent() const
{
	return continent;
}

std::string Country::getName() const
{
	return name;
}

int Country::getArmies() const
{
	return armies;
}

void Country::addArmies(int amount)
{
	armies += amount;
}

void Country::removeArmies(int amount)
{
	armies -= amount;
}
/* TODO: Figure out why uncommenting this causes build errors
Player* Country::getOwner() const
{
	return owner;
}
*/
void Country::setX(int val)
{
	x = val;
}

void Country::setY(int val)
{
	y = val;
}
