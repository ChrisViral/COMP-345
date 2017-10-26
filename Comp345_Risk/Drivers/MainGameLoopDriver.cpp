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

#include "MainGameLoopDriver.h"
#include "../Player/Player.h"
#include "../Game/Game.h"
#include "../Map/MapLoader/MapLoader.h"

MainGameLoopDriver::MainGameLoopDriver()
{
}

MainGameLoopDriver::~MainGameLoopDriver()
{
}

string MainGameLoopDriver::getOpeningMessage()
{
	return "Starting Main Game Loop driver";
}

string MainGameLoopDriver::getClosingMessage()
{
	return "Ending Main Game Loop driver";
}

void MainGameLoopDriver::run()
{
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);
	
	vector<Player*> players(rand() % 5 + 2);
	Game gameLoop(&players, map);
	gameLoop.setup();
	gameLoop.openingAnnouncement();
	gameLoop.playGame();
}
