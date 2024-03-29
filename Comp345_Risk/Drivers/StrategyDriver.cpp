// ==============================
//           COMP-345 D
//          Assignment 4
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
#include "../Player/PassiveAI.h"
#include "../Player/AggressiveAI.h"
#include "../Player/CheaterAI.h"
#include "../Player/RandomPlayer.h"

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
	Deck* deck = new Deck(map->size());

	Player* randomAI = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(deck), new RandomPlayer);
	Player* aggressiveAI = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(deck), new AggressiveAI);
	Player* passiveAI = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(deck), new PassiveAI);
	Player* cheaterAI = new Player("Cheater 1", DiceRoller(), vector<Country*>(), Hand(deck), new CheaterAI);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(randomAI);
	players->push_back(aggressiveAI);
	players->push_back(passiveAI);
	players->push_back(cheaterAI);

	//Load a game with the above info and run the setup
	Game game(players, map, deck);
	//We want to know how this affected the players and map
	game.setup();

	cout << "\nRunning Random strategy" << endl;
	randomAI->executeStrategy();
	cout << "\nEnding Random strategy" << endl;

	cout << "\nRunning Aggressive strategy" << endl;
	aggressiveAI->executeStrategy();
	cout << "\nEnding Aggressive strategy" << endl;

	cout << "\nRunning Passive strategy" << endl;
	passiveAI->executeStrategy();
	cout << "\nEnding Passive strategy" << endl;

	cout << "\nRunning Cheater strategy" << endl;
	cheaterAI->executeStrategy();
	cout << "\nEnding Cheater strategy" << endl;

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

string StrategyDriver::getOpeningMessage()
{
	return "Starting Strategy driver";
}

string StrategyDriver::getClosingMessage()
{
	return "Ending Strategy driver";
}
