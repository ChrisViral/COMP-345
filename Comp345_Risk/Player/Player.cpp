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
#include <algorithm>
#include "Card/Hand.h"
#include <cctype>
#include "../Base/Utils.h"
#include "TypeOfPlayer.h"


using std::vector;
using std::string;
using std::cout;
using std::endl;

Player::Player(): game(nullptr)
{
}

Player::~Player()
{
	game = nullptr;
}

Player::Player(DiceRoller aDiceRoller, vector<Country*> aPlayersTerritoriesVector, Hand aPlayersCards): game(nullptr)
{
	diceRoller = aDiceRoller;
	playersTerritories = aPlayersTerritoriesVector;
	playersCards = aPlayersCards;
}

Player::Player(string name, DiceRoller diceRoller, vector<Country*> playersTerritories, Hand playersCards, TypeOfPlayer* typePlayer)
	: name(name), diceRoller(diceRoller), playersTerritories(playersTerritories), playersCards(playersCards), game(nullptr)
{
	typeOfPlayer = typePlayer;
}

void Player::displayInfo()
{
	cout << "Here is what the Player can access during his turn:" << endl;
	cout << "\n1- Player has a dice roller object: " << endl;
	diceRoller.showRolls();
	cout << " \n2- Player owns one or more territories, Here they are: " << endl;
	for (Country* c : playersTerritories)
	{
		cout << c->getName() << endl;
	}
	cout << " \n3- Player has one or more cards in his game, Here they are: " << endl;
	playersCards.displayCards();
}

const vector<Country*>& Player::getCountries() const
{
	return playersTerritories;
}

string Player::getName() const
{
	return name;
}

int Player::controlled() const
{
	return playersTerritories.size();
}

void Player::addCountry(Country* country) {

	playersTerritories.push_back(country); 
}

void Player::setGame(Game* currentGame)
{
	game = currentGame;
}

void Player::addRandomArmy()
{
	playersTerritories[rand() % playersTerritories.size()]->addArmies(1);
}

Hand& Player::getHand()
{
	return playersCards;
}

DiceRoller Player::getDiceRoller()
{
	return diceRoller;
}

void Player::printPlayerArmyInfo()
{
	//See how many countries they own
	cout << name << " owns " << playersTerritories.size() << " countries" << endl;

	//Count player's armies
	int armies = 0;
	for (Country* c : playersTerritories)
	{
		//See what country the player owns
		cout << name << " owns " << c->getName() << " and has " << c->getArmies() << " armies stationed there" << endl;
		armies += c->getArmies();
	}

	//See total amount of armies owned by a player
	cout << name << " has a total of " << armies << " placed on the board" << endl;
}

void Player::setStrategy(TypeOfPlayer* typePlayer)
{
	typeOfPlayer = typePlayer;
}

void Player::executeStrategy()
{		
	typeOfPlayer->playTurn(this);
}



//These methods can be used for specific testing/demo purposes. But in reality executeStrategy should be used.
void Player::executeAttack(bool skip)
{
	typeOfPlayer->attack(this,skip);
}

void Player::executeReinforce(bool skip)
{
	typeOfPlayer->reinforce(this, skip);
}

void Player::executeFortify(Country& source, Country& target, int amount, bool skip)
{
	typeOfPlayer->fortify(this, source, target, amount, skip);
}

void Player::removeCountry(Country* country)
{
	for (int i = 0; i < playersTerritories.size(); i++)
	{
		if (country->getName() == playersTerritories[i]->getName())
		{
			playersTerritories.erase(playersTerritories.begin() + i);
			return;
		}
	}
}