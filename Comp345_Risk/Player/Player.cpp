#include <string>
#include "Player.h"
#include <iostream>
#include <vector>

Player::Player()
{
}

Player::~Player()
{
}

Player::Player(std::string aName, std::string aDiceRoller, std::vector<std::string> aPlayersTerritoriesVector, std::string aPlayersCards)
{
	name = aName;
	diceRoller = aDiceRoller;
	playersTerritories = aPlayersTerritoriesVector;
	playersCards = aPlayersCards;
}
std::string Player::getName()
{
	return name;
}
std::vector<std::string> Player::getTerritories()
{
	return std::vector<std::string>();
}

int Player::getNumberOfTerritories()
{
	int num = playersTerritories.size();
	return num;
}

std::string Player::getDiceRoller()
{
	return diceRoller;
}
std::string Player::getPlayersCards()
{
	return playersCards;
}

void Player::displayInfo()
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Dice: " << diceRoller << std::endl;
	std::cout << "Territories: ";
	for (unsigned int i = 0; i < playersTerritories.size(); i++)
		std::cout << playersTerritories[i];
	std::cout << std::endl;
	std::cout << "Cards: " << playersCards << std::endl;
}

void Player::reinforce()
{
	std::cout << "[Part 4: Main game loop: reinforcement phase.]" << std::endl;
}

void Player::attack()
{
	std::cout << "[Part 5: Main game loop: attack phase.]" << std::endl;
}

void Player::fortify()
{
	std::cout << "[Part 6: Main game loop: fortification phase.]" << std::endl;
}