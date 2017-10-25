#include "RiskObject.h"
#include "Player.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

RiskObject::RiskObject()
{

}
int RiskObject::getRandomNumberOfPlayers()
{
	srand(unsigned(time(0)));
	int randNum = rand() % 5 + 2;
	numberOfPlayers = randNum;
	return numberOfPlayers;
}
std::vector<Player> RiskObject::getRiskPlayers()	// simulates parts 1 and 2
{
	std::vector<std::string> humanPlayerTerritories;
	humanPlayerTerritories.push_back("[Human Player's Territories]");
	Player newPlayer("Human Player", "[Human Player's Dice Roller]", humanPlayerTerritories, "[Human Player's Cards]");
	riskPlayers.push_back(newPlayer);
	for (int i = 2; i <= numberOfPlayers; i++)
	{
		if (i == 2)
		{
			std::vector<std::string> botATerritories;
			botATerritories.push_back("[Bot A's Territories]");
			Player newPlayer("Bot A", "[Bot A's Dice Roller]", botATerritories, "[Bot A's Cards]");
			riskPlayers.push_back(newPlayer);
		}
		if (i == 3)
		{
			std::vector<std::string> botBTerritories;
			botBTerritories.push_back("[Bot B's Territories]");
			Player newPlayer("Bot B", "[Bot B's Dice Roller]", botBTerritories, "[Bot B's Cards]");
			riskPlayers.push_back(newPlayer);
		}
		if (i == 4)
		{
			std::vector<std::string> botCTerritories;
			botCTerritories.push_back("[Bot C's Territories]");
			Player newPlayer("Bot C", "[Bot C's Dice Roller]", botCTerritories, "[Bot C's Cards]");
			riskPlayers.push_back(newPlayer);
		}
		if (i == 5)
		{
			std::vector<std::string> botDTerritories;
			botDTerritories.push_back("[Bot D's Territories]");
			Player newPlayer("Bot D", "[Bot D's Dice Roller]", botDTerritories, "[Bot D's Cards]");
			riskPlayers.push_back(newPlayer);
		}
		if (i == 6)
		{
			std::vector<std::string> botETerritories;
			botETerritories.push_back("[Bot E's Territories]");
			Player newPlayer("Bot E", "[Bot E's Dice Roller]", botETerritories, "[Bot E's Cards]");
			riskPlayers.push_back(newPlayer);
		}
	}
	return riskPlayers;
}

std::vector<int> RiskObject::getOrderOfPlay(int num)	// simulates parts 1 and 2
{
	std::vector<int> order;
	for (int i = 0; i < num; i++)
		order.push_back(i);
	std::random_shuffle(order.begin(), order.end());
	return order;
}

RiskObject::~RiskObject()
{
}
