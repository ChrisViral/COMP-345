// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

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

void Player::reinforce()
{
	std::cout << "\nPlayer can reinforce a territory of his choice:" << std::endl;
	std::cout << " -- Exact reinforce() function implementation has yet to be determined! -- " << std::endl;
}

void Player::attack()
{
	std::cout << "\nPlayer can attack a territory of his choice:" << std::endl;
	std::cout << " -- Exact attack() function implementation has yet to be determined! -- " << std::endl;
}

bool Player::fortify(Country& source, Country& target, int amount)
{
	std::cout << "\nPlayer can fortify a territory of his choice:" << std::endl;
	//std::cout << " -- Exact fortify() function implementation has yet to be determined! -- " << std::endl;

	// Cannot exchange armies, if the countries are not owned by the same player
	if (source.getOwner() != target.getOwner())
	{
		return false;
	}
	
	// We can't exchange more armies then we have from the source country to the target country
	// Also from the official rules, we must leave at least 1 army in the source country
	// We can't pull out all of our armies
	if (amount >= source.getArmies())
	{
		return false;
	}
	source.removeArmies(amount);
	target.addArmies(amount);
	return true;
	
	
	
	
	

}

