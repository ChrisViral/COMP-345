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
	Game game = Game();

	game.gameLoop();
}
