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

#include "Player.h"
#include <string>
#include <iostream>
#include <vector>
#include "../Map/Country.h"
#include <functional>

Player::Player()
{
}

Player::~Player()
{
}

Player::Player(DiceRoller aDiceRoller, std::vector<Country> aPlayersTerritoriesVector, Hand aPlayersCards)
{
	diceRoller = aDiceRoller;
	playersTerritories = aPlayersTerritoriesVector;
	playersCards = aPlayersCards;
}

Player::Player(std::string name, DiceRoller diceRoller, std::vector<Country> playersTerritories, Hand playersCards)
{
}

void Player::displayInfo()
{
	std::cout << "Here is what the Player can access during his turn:" << std::endl;
	std::cout << "\n1- Player has a dice roller object: " << std::endl;
	diceRoller.showRolls();
	std::cout << " \n2- Player owns one or more territories, Here they are: " << std::endl;
	for (Country c : playersTerritories)
	{
		std::cout << c.getName() << std::endl;
	}
	std::cout << " \n3- Player has one or more cards in his game, Here they are: " << std::endl;
	playersCards.displayCards();
}

void Player::reinforce(int total, bool skip)
{
	if (skip)
	{
		std::cout << "\nReinForce Method" << std::endl;
		return;
	}

	
}

void Player::attack(bool skip)
{
	if (skip)
	{
		std::cout << "\nAttack Method" << std::endl;
		return;
	}
}

bool Player::fortify(Country& source, Country& target, int amount, bool skip)
{
	if (skip)
	{
		std::cout << "\nFortify Method" << std::endl;
		return true;
	}


	//std::cout << "\nPlayer can fortify a territory of his choice:" << std::endl;
	//std::cout << " -- Exact fortify() function implementation has yet to be determined! -- " << std::endl;

	

	// check to see if this player owns the source and target country
	
	if (!ownsCountry(source) && !ownsCountry(target))
	{
		// TODO: implement country ownership when handing out countries to the players. right now the owners are null
		// TODO: uncomment this when countries have their owners set
		//return false;
	}

	// TODO: implement some sort of function to check if countries are adjacent to each other.
	// with the new added isReachable this could be solved, but their is no access to the riskmap from inside the player
	// Right now this is pseudo code
	//if (source is not adjacent to target) {
		//return false;
	//}
	
	
	// We can't exchange negative/more armies then we have from the source country to the target country
	// Also from the official rules, we must leave at least 1 army in the source country
	// We can't pull out all of our armies
	if (amount < 0 || amount > source.getArmies() - 1)
	{
		return false;
	}
	source.removeArmies(amount);
	target.addArmies(amount);
	return true;
	
	
	
	
	

}

const std::vector<Country>& Player::getCountries() const
{
	return playersTerritories;
}

std::string Player::getName() const
{
	return name;
}

int Player::controlled() const
{
	return playersTerritories.size();
}
bool Player::ownsCountry(const Country& country) const
{

	// TODO: figure out in the end if are keeping the getOwner() and a pointer to the owner in the player
	return (this == country.getOwner());

	// If we don't keep a pointer to the player owner, then use the bottom implementation
	
	/*
	for (const Country& c : playersTerritories)
	{
		if (c.getName() == country.getName())
		{
			return true;
		}
	}
	return false;*/
	
}

void Player::addCountry(Country country)
{ 
	playersTerritories.push_back(country); 
}