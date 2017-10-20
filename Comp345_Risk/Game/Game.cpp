#include "Game.h"
#include <ctime>
#include <algorithm>


Game::Game(vector<Player*> players, RiskMap* map) : players(players), map(map)
{
}

Game::~Game()
{
}

void Game::setup()
{
	//Original random seed, only needs to be done once in whole program execution
	srand(time(nullptr));

	//Shuffle the order of the players
	random_shuffle(players.begin(), players.end());

	//Create a vector of countried not distributed yet
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
}