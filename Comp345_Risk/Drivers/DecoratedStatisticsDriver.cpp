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

#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "DecoratedStatisticsDriver.h"
#include "../Game/Game.h"
#include "../Game/UI/GameUI.h"
#include "../Player/AggressiveAI.h"
#include "../Game/UI/Decorators/UIOutputDecorator.h"
#include "../Player/Human.h"
#include <iostream>
#include "../Player/RandomPlayer.h"


DecoratedStatisticsDriver::DecoratedStatisticsDriver()
{
}


DecoratedStatisticsDriver::~DecoratedStatisticsDriver()
{
}


void DecoratedStatisticsDriver::run()
{
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);
	Deck* deck = new Deck(map->size());

	Player* p1 = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(deck), new RandomPlayer);
	Player* p2 = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(deck), new AggressiveAI);
	Player* p3 = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(deck), new AggressiveAI);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(p1);
	players->push_back(p2);
	players->push_back(p3);

	//Load a game with the above info and run the setup
	Game game(players, map, deck);
	//We want to know how this affected the players and map
	game.setup();


	UIOutputDecorator output(&game);


	output.setDecoratorEnabled(PlayerHandUIDecorator, false);
	output.setDecoratorEnabled(ContinentControlUIDecorator, false);
	output.setDecoratorEnabled(DominationUIDecorator, false);


	GameUI* ui = output.getUi();

	game.registerObserver(ui);
	players->at(0)->registerObserver(ui);
	players->at(1)->registerObserver(ui);
	players->at(2)->registerObserver(ui);


	game.gameLoop();


	//Clear memory

	delete map;
	map = nullptr;
	delete deck;
	deck = nullptr;

	delete players->at(0);
	delete players->at(1);
	delete players->at(2);
	players->clear();

	delete players;
	players = nullptr;
}

string DecoratedStatisticsDriver::getOpeningMessage()
{
	return "Starting Decorated Statistics Driver";
}

string DecoratedStatisticsDriver::getClosingMessage()
{
	return "Ending Decorated Statistics Driver";
}
