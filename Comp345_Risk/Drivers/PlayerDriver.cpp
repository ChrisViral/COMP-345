// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include <string>
#include "../Map/Continent.h"
#include "../Player/Player.h"
#include "../Map/Country.h"
#include "PlayerDriver.h"
#include "../Player/Card/Card.h";
#include "../Player/DiceRoller.h";
#include "../Player/Card/Hand.h";


PlayerDriver::PlayerDriver()
{
}

PlayerDriver::~PlayerDriver()
{
}


std::string PlayerDriver::getOpeningMessage()
{
	return "Starting Player driver";
}

std::string PlayerDriver::getClosingMessage()
{
	return "Ending Player driver";
}

void PlayerDriver::run()
{
	//Sample Dice, Territory and Card objects are created to demonstrate the Player object class.
	DiceRoller playerDice;
	std::vector<Country> playerTerritories;
	Hand hand;

	//Roll the dice a few times
	playerDice.roll(3);
	playerDice.roll(3);
	playerDice.roll(3);

	//Add countries
	Continent na("North America", 5);
	playerTerritories.push_back(Country("Alaska", na));
	playerTerritories.push_back(Country("Northwest Territory", na));
	playerTerritories.push_back(Country("Alberta", na));
	playerTerritories.push_back(Country("Greenland", na));
	playerTerritories.push_back(Country("Ontario", na));
	playerTerritories.push_back(Country("Quebec", na));
	playerTerritories.push_back(Country("Western United States", na));
	playerTerritories.push_back(Country("Eastern United States", na));
	playerTerritories.push_back(Country("Central America", na));

	//Add cards
	hand.addCard(Card(infantry));
	hand.addCard(Card(infantry));
	hand.addCard(Card(infantry));
	hand.addCard(Card(infantry));
	hand.addCard(Card(artillery));
	hand.addCard(Card(artillery));
	hand.addCard(Card(cavalry));

	//Player is initialized and given his dice, territories and cards (in sample form)
	Player newPlayer(playerDice, playerTerritories, hand);

	//Player assets are displayed using function in Player class.
	newPlayer.displayInfo();

	//Player's reinforce, attack and fortify functions are shown.
	newPlayer.reinforce();
	newPlayer.attack();
	newPlayer.fortify();
}
