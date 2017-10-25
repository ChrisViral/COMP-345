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

#include "Game.h"

#include <ctime>
#include <algorithm>


Game::Game(vector<Player*>& players, RiskMap* map) : players(players), map(map)
{
}

Game::~Game()
{
	for (Player* p : players)
	{
		delete p;
	}
	players.clear();

	delete map;
}

void Game::setup()
{
	//Original random seed, only needs to be done once in whole game execution
	srand(time(nullptr));

	//Shuffle the order of the players
	random_shuffle(players.begin(), players.end());

	//Create a vector of countries not distributed yet
	vector<int> remaining(map->size());
	for (int i = 0; i < map->size(); i++)
	{
		remaining.push_back(i);
	}

	//Assign a remaining country to each player, one by one
	for (int i = 0; i < map->size(); i++)
	{
		//Get random member of remaining, obtain it's index value, then remove it
		int j = rand() % remaining.size();
		int index = remaining[j];
		remaining.erase(remaining.begin() + j);

		//Find the country at the given index and set it's new owner
		map->getCountry(index)->setOwner(players[i % players.size()]);
	}

	int armies = 40 - (players.size() - 2) * 5;

	//Each player places the same total amount of armies
	for (int i = 0; i < armies; i++)
	{
		//Players place one army at a time in the regular play order
		for (Player* p : players)
		{
			p->reinforce(1);
		}
	}
}
