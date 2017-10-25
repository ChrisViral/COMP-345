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

#pragma once
#include <vector>
#include "../Base/RiskObject.h"
#include "Card/Hand.h"
#include "DiceRoller.h"
#include "../Map/Country.h"

//class Country;

class Player : public RiskObject
{
public:
	Player();
	~Player();
	Player(DiceRoller diceRoller, std::vector<Country> playersTerritories, Hand playersCards);

	//All Player's assests are displayed
	void displayInfo();
	
	//Player is given choice to place an allocated amount of troops (based on the countries he owns, the continents he controls
	//and cards he has on hand on any of his territories to reinforce them before attacking.
	void reinforce(int total = 0);

	//Method allows player to roll and take over countries adjacent to his own territories. Method ends when player 
	//decided or when he know longer has a territory with more than one troop remaining positioned on it.
	void attack();

	// If the amount given is larger or equal than the source country owns, then it will return false and no armies will be exchanged
	// If the amount if smaller, then it will exhange and return true
	// From the official rules, we must leave at least 1 army in the source country
	// We can't pull out all of our armies
	bool fortify(Country& source, Country& target, int amount);

	// Return the countries that this player owns
	const std::vector<Country>& getCountries();

	std::string getName();
	int controlled();

private:
	DiceRoller diceRoller;
	std::vector<Country> playersTerritories;
	Hand playersCards;

	bool ownsCountry(const Country& country) const;

	
};
