#include "StrategyDriver.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Game/Game.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"
#include "../Player/Player.h"
#include <iostream>
#include "../Player/Human.h"
#include "../Player/PassiveAI.h"
#include "../Player/AggressiveAI.h"

using std::vector;
using std::cout;
using std::endl;

GameDriver::GameDriver()
{
}

GameDriver::~GameDriver()
{
}

void GameDriver::run()
{
	//Load the basic map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), new Human()));
	players->push_back(new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), new Human()));
	players->push_back(new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(), new Human()));
	players->push_back(new Player("Player 4", DiceRoller(), vector<Country*>(), Hand(), new Human()));

	//Load a game with the above info and run the setup
	Game game(players, map);
	//We want to know how this affected the players and map
	game.setup();


	players->at(0)->executeAttack();

	//Clear memory
	delete map;
	map = nullptr;

	delete players->at(0);
	delete players->at(1);
	delete players->at(2);
	delete players->at(3);
	players->clear();

	delete players;
	players = nullptr;
}

string GameDriver::getOpeningMessage()
{
	return "Starting Game driver";
}

string GameDriver::getClosingMessage()
{
	return "Ending Game driver";
}
