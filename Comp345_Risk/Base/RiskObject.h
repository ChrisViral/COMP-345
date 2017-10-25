#pragma once
#include "Player.h"
#include <cstdlib>
#include <vector>
#include <iostream>

class RiskObject
{
public:
	RiskObject();
	int getRandomNumberOfPlayers();
	std::vector<Player> getRiskPlayers();
	std::vector<int> getOrderOfPlay(int);
	~RiskObject();
private:
	int numberOfPlayers;
	std::vector<Player> riskPlayers;
	std::vector<int> orderOfPlay;
};

