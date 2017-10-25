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
#include "../Base/RiskObject.h";
#include "Card/Hand.h"
#include "../Map/Country.h"
#include "DiceRoller.h"

class Player : public RiskObject
{
public:
	Player();
	~Player();
	Player(DiceRoller diceRoller, std::vector<Country> playersTerritories, Hand playersCards);

	void displayInfo();
	//All Player's assests are displayed

	void reinforce(int total = 0);
	//Player is given choice to place an allocated amount of troops (based on the countries he owns, the continents he controls
	//and cards he has on hand on any of his territories to reinforce them before attacking.

	void attack();
	//Method allows player to roll and take over countries adjacent to his own territories. Method ends when player 
	//decided or when he know longer has a territory with more than one troop remaining positioned on it.

	void fortify();
	//Method can be invoked after attack turn is complete. Player can take as many troops as he’d like
	//from one of his territories, and put them in one of his other
	//territories that is connected either by land or sea in order to fortify it.

	std::string getName();

	int controlled();

private:
	DiceRoller diceRoller;
	std::vector<Country> playersTerritories;
	Hand playersCards;
};
