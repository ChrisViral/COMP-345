//This is the header file Player.h This is the interface for the class Player.
//Values of this type are Player objects. A Player owns a
//collection of territories, a hand of Risk cards and his own dice
//roller object.

#ifndef PLAYER_H
#define PLAYER_H

#include "Dice.h"
#include "Territories.h"
#include "Cards.h"
#include <string>
#include <vector>
using namespace std;

class Player
{
public:
	Player();
	Player(Dice diceRoller, Territories playersTerritories, Cards playersCards);
	void displayInfo();
	//All Player's assests are displayed

	void reinforce();
	//Player is given choice to place an allocated amount of troops (based on the countries he owns, the continents he controls
	//and cards he has on hand on any of his territories to reinforce them before attacking.

	void attack();
	//Method allows player to roll and take over countries adjacent to his own territories. Method ends when player 
	//decided or when he know longer has a territory with more than one troop remaining positioned on it.

	void fortify();
	//Method can be invoked after attack turn is complete. Player can take as many troops as he’d like
	//from one of his territories, and put them in one of his other
	//territories that is connected either by land or sea in order to fortify it.
private:
	Dice diceRoller;
	Territories playersTerritories;
	Cards playersCards;
};
#endif //PLAYER_H