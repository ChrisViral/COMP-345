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

	std::cout << "\nRunning Human strategy" << std::endl;
	//human->executeStrategy();
	std::cout << "\nEnding Human strategy" << std::endl;
	
	std::cout << "\nRunning Aggressive strategy" << std::endl;
	aggressiveAI->executeStrategy();
	std::cout << "\nEnding Aggressive strategy" << std::endl;
	
	std::cout << "\nRunning Passive strategy" << std::endl;
	passiveAI->executeStrategy();
	std::cout << "\nEnding Passive strategy" << std::endl;

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
