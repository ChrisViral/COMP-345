// ==============================
//           COMP-345 D
//          Assignment 3
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

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

StrategyDriver::StrategyDriver()
{
}

StrategyDriver::~StrategyDriver()
{
}

void StrategyDriver::run()
{
	//Load the basic map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	Player* human = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), new Human);
	Player* aggressiveAI = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);
	Player* passiveAI = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(), new PassiveAI);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(human);
	players->push_back(aggressiveAI);
	players->push_back(passiveAI);

	//Load a game with the above info and run the setup
	Game game(players, map);
	//We want to know how this affected the players and map
	game.setup();

	cout << "\nRunning Human strategy" << endl;
	human->executeStrategy();
	cout << "\nEnding Human strategy" << endl;

	cout << "\nRunning Aggressive strategy" << endl;
	aggressiveAI->executeStrategy();
	cout << "\nEnding Aggressive strategy" << endl;

	cout << "\nRunning Passive strategy" << endl;
	passiveAI->executeStrategy();
	cout << "\nEnding Passive strategy" << endl;

	//Clear memory
	delete map;
	map = nullptr;

	delete players->at(0);
	delete players->at(1);
	delete players->at(2);
	players->clear();

	delete players;
	players = nullptr;
}

string StrategyDriver::getOpeningMessage()
{
	return "Starting Strategy driver";
}

string StrategyDriver::getClosingMessage()
{
	return "Ending Strategy driver";
}
