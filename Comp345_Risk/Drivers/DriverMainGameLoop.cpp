#include "MainGameLoop.h"
#include "RiskObject.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>

int main()
{
	RiskObject newGame;																			//
	std::vector<int> orderOfPlay = newGame.getOrderOfPlay(newGame.getRandomNumberOfPlayers());	// simulates parts 1 and 2
	std::vector<Player> riskPlayers = newGame.getRiskPlayers();									//

	MainGameLoop gameLoop(riskPlayers, orderOfPlay);
	gameLoop.openingAnnouncement();
	gameLoop.playGame();
	std::cin.get();
	return 0;
}

