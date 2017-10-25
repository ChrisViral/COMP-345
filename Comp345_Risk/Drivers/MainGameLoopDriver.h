#pragma once

#include "../Base/Driver.h"
#include "../Player/Player.h"

using std::vector;

class MainGameLoopDriver : public Driver
{
public:
	MainGameLoopDriver();
	~MainGameLoopDriver();
	string getOpeningMessage() override;
	string getClosingMessage() override;
	void run() override;
private:
	int getRandomNumberOfPlayers();
	vector<int> getOrderOfPlay(int num) const;
	int numberOfPlayers;
	vector<Player> riskPlayers;
	vector<int> orderOfPlay;
};
