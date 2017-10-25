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
#include "../Game/MainGameLoop.h"
#include <algorithm>

MainGameLoopDriver::MainGameLoopDriver(): numberOfPlayers(0)
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
	vector<int> orderOfPlay = getOrderOfPlay(getRandomNumberOfPlayers()); // simulates parts 1 and 2
	vector<Player> riskPlayers;

	MainGameLoop gameLoop(riskPlayers, orderOfPlay);
	gameLoop.openingAnnouncement();
	gameLoop.playGame();
}

int MainGameLoopDriver::getRandomNumberOfPlayers()
{
	int randNum = rand() % 5 + 2;
	numberOfPlayers = randNum;
	return numberOfPlayers;
}

vector<int> MainGameLoopDriver::getOrderOfPlay(int num) const // simulates parts 1 and 2
{
	vector<int> order;
	for (int i = 0; i < num; i++)
		order.push_back(i);
	random_shuffle(order.begin(), order.end());
	return order;
}
