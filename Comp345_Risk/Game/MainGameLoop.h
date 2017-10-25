#pragma once

#include <vector>
#include "../Player/Player.h"

using std::vector;

class MainGameLoop
{
public:
	MainGameLoop();
	MainGameLoop(vector<Player>, vector<int>);
	void MainGameLoop::openingAnnouncement();
	void MainGameLoop::playGame();
	~MainGameLoop();

private:
	int numOfPlayers;
	vector<Player> riskPlayers;
	vector<int> orderOfPlay;
};
