#pragma once
#include <string>
#include <vector>

class Player
{
public:
	Player();
	~Player();
	Player(std::string, std::string, std::vector<std::string>, std::string);

	std::string getName();
	//Get name of player

	std::vector<std::string> getTerritories();
	//Get territories of player

	int getNumberOfTerritories();
	//See how many territories player has.

	std::string getDiceRoller();
	//Show player's dice roller

	std::string getPlayersCards();
	//Show player's cards

	void displayInfo();
	//Show all player info

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
	std::string name;
	std::string diceRoller;
	std::vector<std::string> playersTerritories;
	std::string playersCards;
};
