#include "StatisticsDriver.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Game/Game.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"
#include "../Player/Player.h"
#include "../Player/AggressiveAI.h"
#include <iostream>
#include "../Game/UI/DominationUI.h"

using std::vector;
using std::cout;
using std::endl;

StatisticsDriver::StatisticsDriver()
{
}

StatisticsDriver::~StatisticsDriver()
{
}

void StatisticsDriver::run()
{
	//Load the basic map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	Player* p1 = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI());
	Player* p2 = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI());

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(p1);
	players->push_back(p2);

	//Load a game with the above info and run the setup
	Game game(players, map);
	game.setup();

	//UI
	GameUI* ui = new DominationUI(&game);
	p1->registerObserver(ui);
	p2->registerObserver(ui);

	//Test
	game.gameLoop();

	//Clear memory
	delete map;
	map = nullptr;

	delete players->at(0);
	delete players->at(1);
	players->clear();

	delete players;
	players = nullptr;

	delete ui;
	ui = nullptr;
}

string StatisticsDriver::getOpeningMessage()
{
	return "Starting Game driver";
}

string StatisticsDriver::getClosingMessage()
{
	return "Ending Game driver";
}
