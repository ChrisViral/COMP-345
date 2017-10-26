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
#include <iostream>

void transferCountries(Player* player, RiskMap* map);

Game::Game()
{
	map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	players = new std::vector<Player*>();

	players->push_back(new Player(DiceRoller(), std::vector<Country>(), Hand()));
	players->push_back(new Player(DiceRoller(), std::vector<Country>(), Hand()));
	players->push_back(new Player(DiceRoller(), std::vector<Country>(), Hand()));	
}


Game::Game(int numPlayers, RiskMap* map) : numPlayers(numPlayers), map(map)
{

}

Game::~Game()
{
	//Clear local information
	for (int i = 0; i < players->size(); i++)
	{
		delete players->at(i);
	}
	players->clear();

	delete players;
	players = nullptr;

	map = nullptr;
}

void Game::setup()
{
	//Original random seed, only needs to be done once in whole game execution
	srand(time(nullptr));

	//Create the vector of empty players
	players = new std::vector<Player*>(numPlayers);
	for (int i = 0; i < numPlayers; i++)
	{
		players->push_back(new Player("Player " + i, DiceRoller(), std::vector<Country>(), Hand()));
	}

	//Shuffle the order of the players
	random_shuffle(players->begin(), players->end());

	//Create a vector of countries not distributed yet
	std::vector<int> remaining(map->size());
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
		map->getCountry(index)->setOwner(players->at(i % numPlayers));
	}

	int armies = 40 - (numPlayers - 2) * 5;

	//Each player places the same total amount of armies
	for (int i = 0; i < armies; i++)
	{
		//Players place one army at a time in the regular play order
		for (int j = 0; j < numPlayers; j++)
		{
			players->at(j)->reinforce(1);
		}
	}
}

void Game::gameLoop()
{
	int counter = 1;
	while (!checkWin())
	{
		for (int i = 0; i < players->size(); i++)
		{
			std::cout << "Player " << i + 1 << std::endl;
			(*players)[i]->reinforce(true);
			(*players)[i]->attack(true);
			(*players)[i]->fortify(Country(), Country(), 0, true); //Dummy arguements for this part
			std::cout << std::endl;
		}

		if (counter > 3)
		{
			transferCountries((*players)[0], map);
		}

		counter++;
	}

	std::cout << "Player 1 won" << std::endl;
}

bool Game::checkWin()
{
	for (int i = 0; i < players->size(); i++)
	{
		if (players->at(i)->getCountries().size() == map->size())
			return true;
	}

	return false;
}

//Free function to transfer countries to a player
void transferCountries(Player* player, RiskMap* map)
{
	std::cout << "Transfering Countries to player 1" << std::endl;

	for (int i = 0; i < map->size(); i++)
	{
		player->addCountry(*map->getCountry(i));
	}
}