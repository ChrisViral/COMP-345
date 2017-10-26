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

Player::Player(string name, DiceRoller diceRoller, vector<Country*> playersTerritories, Hand playersCards)
	: name(name), diceRoller(diceRoller), playersTerritories(playersTerritories), playersCards(playersCards), game(nullptr)
{
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

void Player::reinforce(bool skip)
{
	//Temporary override for GameLoop purpose
	if (skip)
	{
		cout << "\nReinForce Method" << endl;
		return;
	}

	int total = std::max(3, int(playersTerritories.size() / 3));
	cout << name << " owns " << playersTerritories.size() << " territories, therefore he can reinforce with " << total << " armies." << endl;

	std::unordered_map<string, Continent> continents = game->getMap()->getContinents();
	for (std::pair<string, Continent> p : continents)
	{
		Continent c = p.second;
		if (c.ownedBy(this))
		{
			cout << name << " owns all of " << c.getName() << " therefore he gets an extra " << c.getControlValue() << " armies." << endl;
			total += p.second.getControlValue();
		}
	}

	Exchangement exchange = playersCards.exchange();
	if (exchange.successfullyExchanged)
	{
		cout << name << " exchanged the following cards to get " << exchange.armies << " armies." << endl;
		for (Card c : exchange.cardsExchanged)
		{
			cout << cardTypeEnumToString(c.getCardType()) << endl;
		}
		total += exchange.armies;
	}

	cout << name << " therefore has a final total of " << total << " armies to place" << endl;

	for (int i = 0; i < total; i++)
	{
		Country* c = playersTerritories[rand() % playersTerritories.size()];
		c->addArmies(1);
		cout << "Adding one army to " << c->getName() << endl;
	}

	cout << "All reinforcements distributed!" << endl << endl;

}

void Player::attack(bool skip)
{
	if (skip)
	{
		cout << "\nAttack Method" << endl;
		return;
	}
}

bool Player::fortify(Country& source, Country& target, int amount, bool skip)
{
	if (skip)
	{
		cout << "\nFortify Method" << endl;
		return true;
	}


	//std::cout << "\nPlayer can fortify a territory of his choice:" << std::endl;
	//std::cout << " -- Exact fortify() function implementation has yet to be determined! -- " << std::endl;

	

	// check to see if this player owns the source and target country
	
	if (ownsCountry(source) && ownsCountry(target))
	{
		if (!game->getMap()->isReachable(this, source, target)) {
				return false;
		}


		// We can't exchange negative/more armies then we have from the source country to the target country
		// Also from the official rules, we must leave at least 1 army in the source country
		// We can't pull out all of our armies
		if (amount < 0 || amount > source.getArmies() - 1) {
			return false;
		}
		source.removeArmies(amount);
		target.addArmies(amount);
		return true;
	} else {
		return false;
	}



	
	
	
	
	

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

void Player::addCountry(Country* country)
{ 
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

Hand Player::getHand() const
{
	return playersCards;
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
	cout << "This means " << name << " has placed a total of " << (armies - playersTerritories.size()) << " armies on the board during the setup phase" << endl;
}
