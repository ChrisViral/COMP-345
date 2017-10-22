// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

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
	void reinforce();

	//Method allows player to roll and take over countries adjacent to his own territories. Method ends when player 
	//decided or when he know longer has a territory with more than one troop remaining positioned on it.
	void attack();
	
	//Method can be invoked after attack turn is complete. Player can take as many troops as he’d like
	//from one of his territories, and put them in one of his other
	//territories that is connected either by land or sea in order to fortify it.

	// If the amount given is larger or equal than the source country owns, then it will return false and no armies will be exchanged
	// If the amount if smaller, then it will exhange and return true
	// From the official rules, we must leave at least 1 army in the source country
	// We can't pull out all of our armies
	bool fortify(Country& source, Country& target, int amount);
	

private:
	DiceRoller diceRoller;
	std::vector<Country> playersTerritories;
	Hand playersCards;

	bool ownsCountry(const Country& country) const;

	
};
