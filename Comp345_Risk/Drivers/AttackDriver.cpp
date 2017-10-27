#include "AttackDriver.h"
#include "../Map/Country.h"
#include "../Game/Game.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"
#include "../Player/Player.h"


AttackDriver::AttackDriver()
{
}


AttackDriver::~AttackDriver()
{
}

void AttackDriver::run()
{
	//Load the basic map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(new Player("Player 1", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 2", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 3", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 4", DiceRoller(), vector<Country>(), Hand()));

	//Load a game with the above info and run the setup
	Game game(players, map);
	//We want to know how this affected the players and map
	game.setup();
	players->at(0)->attack();
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


string AttackDriver::getOpeningMessage()
{
	return "Starting Attack() driver";
}

string AttackDriver::getClosingMessage()
{
	return "Ending Attack() driver";
}
