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

#include "GameStartDriver.h"
#include <iostream>
#include "../Game/GameStart.h"

GameStartDriver::GameStartDriver()
{
}

GameStartDriver::~GameStartDriver()
{
}

string GameStartDriver::getOpeningMessage()
{
	return "Starting Game Start driver";
}

string GameStartDriver::getClosingMessage()
{
	return "Ending Game Start driver";
}

void GameStartDriver::run()
{

	GameStart gamestart;

	//Ask user to pick a map
	gamestart.askForMap();

	//Create the map
	gamestart.createMap();

	//Create the deck
	gamestart.createDeck();	

	std::cout << std::endl;

	//Get input from the user for the number of players
	gamestart.askForPlayers();

	//Create the players
	gamestart.createPlayers();

	std::cout << "The number of countries in the map: " << gamestart.getMap()->size() << std::endl;
	std::cout << "The number of cards in the deck: " << gamestart.getDeck().getDeckSize() << std::endl;
	std::cout << "The number of players in the game: " << gamestart.getPlayers()->size() << std::endl;
}

