//This is the implementation file Player.cpp of the class Player.
//The interface for the class Player is in the header file Player.h.

#include "Player.h"
#include "Dice.h"
#include "Territories.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Player::Player()
{

}

Player::Player(Dice aDiceRoller, Territories aPlayersTerritoriesVector, Cards aPlayersCards)
{
	diceRoller = aDiceRoller;
	playersTerritories = aPlayersTerritoriesVector;
	playersCards = aPlayersCards;

}

void Player::displayInfo()
{
	cout << "Here is what the Player can access during his turn:" << endl;
	cout << "\n1- Player has a dice roller object: " << endl;
	cout << diceRoller.getDiceRoller() << endl;
	cout << " \n2- Player owns one or more territories, Here they are: " << endl;
	cout << playersTerritories.getTerritories() << endl;
	cout << " \n3- Player has one or more cards in his game, Here they are: " << endl;
	cout << playersCards.getCards() << endl;
}

void Player::reinforce()
{
	cout << "\nPlayer can reinforce a territory of his choice:" << endl;
		cout << " -- Exact reinforce() function implementation has yet to be determined! -- " << endl;
}

void Player::attack()
{
	cout << "\nPlayer can attack a territory of his choice:" << endl;
		cout << " -- Exact attack() function implementation has yet to be determined! -- " << endl;
}

void Player::fortify()
{
	cout << "\nPlayer can fortify a territory of his choice:" << endl;
		cout << " -- Exact fortify() function implementation has yet to be determined! -- " << endl;
}