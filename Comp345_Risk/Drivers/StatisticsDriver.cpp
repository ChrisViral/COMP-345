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

#include "StatisticsDriver.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Game/Game.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"
#include "../Player/Player.h"
#include "../Player/AggressiveAI.h"
#include <iostream>

#include "../Player/PassiveAI.h"
#include "../Player/Human.h"
#include "../Game/UI/GameUI.h"
#include "../Game/UI/Decorators/DominationUI.h"

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
	////Load the basic map
	//RiskMap* map = new RiskMap();
	//MapLoader loader("mapfiles/World.map");
	//loader.tryParseMap(map);

	//Player* human = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);
	//Player* aggressiveAI = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);
	//Player* passiveAI = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);

	////Create four players at random
	//vector<Player*>* players = new vector<Player*>;
	//players->push_back(human);
	//players->push_back(aggressiveAI);
	//players->push_back(passiveAI);

	////Load a game with the above info and run the setup
	//Game game(players, map);
	////We want to know how this affected the players and map
	//game.setup();

	//// Create the ui display
	//GameUI* ui = new DominationUI(&game);
	//GameUI* temp = new GameUI();
	//// Register the ui to the game
	//// Everytime a game state changes, the ui will be notified
	//game.registerObserver(temp);
	//players->at(0)->registerObserver(ui);
	//players->at(1)->registerObserver(ui);
	//players->at(2)->registerObserver(ui);


	//game.gameLoop();


	////Clear memory
	//delete map;
	//map = nullptr;

	//delete players->at(0);
	//delete players->at(1);
	//delete players->at(2);
	//players->clear();

	//delete players;
	//players = nullptr;

	//delete ui;
	//delete temp;
	//ui = nullptr;
	//temp = nullptr;
}

string StatisticsDriver::getOpeningMessage()
{
	return "Starting Game driver";
}

string StatisticsDriver::getClosingMessage()
{
	return "Ending Game driver";
}
