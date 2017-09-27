#include "Country.h"

Country::Country()
{

}

Country::Country(std::string countryName, Continent& cont)
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

Continent* Country::getContinent()
{
	return continent;
}

std::string Country::getName()
{
	return name;
}

int Country::getArmies()
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

Player* Country::getOwner()
{
	return owner;
}

void Country::setX(int val)
{
	x = val;
}

void Country::setY(int val)
{
	y = val;
}