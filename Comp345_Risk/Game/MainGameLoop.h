#pragma once
#include "RiskObject.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>

class MainGameLoop
{
public:
	MainGameLoop();
	MainGameLoop(std::vector<Player>, std::vector<int>);
	void MainGameLoop::openingAnnouncement();
	void MainGameLoop::playGame();
	~MainGameLoop();

private:
	int numOfPlayers;
	std::vector<Player> riskPlayers;
	std::vector<int> orderOfPlay;
};
