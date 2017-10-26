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
#include "../Map/MapLoader/MapLoader.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"
#include "../Player/Player.h"
#include <ctime>
#include <algorithm>
#include <iostream>

void transferCountries(Player* player, RiskMap* map);

Game::Game() : owned(true), numPlayers(0)
{
	//Original random seed, only needs to be done once in whole game execution
	srand(time(nullptr));

	map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	players = new vector<Player*>();

	players->push_back(new Player("Player 1", DiceRoller(), vector<Country*>(), Hand()));
	players->push_back(new Player("Player 2", DiceRoller(), vector<Country*>(), Hand()));
	players->push_back(new Player("Player 3", DiceRoller(), vector<Country*>(), Hand()));
}

Game::Game(vector<Player*>* players, RiskMap* map) : owned(false), numPlayers(players->size()), players(players), map(map)
{
	//Set the players to the current game
	for (int i = 0; i < players->size(); i++)
	{
		players->at(i)->setGame(this);
	}

	//Original random seed, only needs to be done once in whole game execution
	srand(time(nullptr));
}

Game::~Game()
{
	if (owned)
	{
		delete map;
		for (int i = 0; i < players->size(); i++)
		{
			delete players->at(i);
		}
		players->clear();
		delete players;
	}

	players = nullptr;
	map = nullptr;
}

void Game::setup()
{
	//Shuffle the order of the players
	random_shuffle(players->begin(), players->end());

	//Create a vector of countries not distributed yet
	vector<int> remaining;
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
		Country* country = map->getCountry(index);
		Player* p = players->at(i % numPlayers);
		country->addArmies(1);
		country->setOwner(p);
		p->addCountry(country);
		
	}

	//Get amount of armies to give place for each player						
	int armies = 40 - (numPlayers - 2) * 5;

	//Each player places the same total amount of armies
	for (int i = 0; i < armies; i++)
	{
		//Players place one army at a time in the regular play order
		for (int j = 0; j < numPlayers; j++)
		{
			players->at(j)->addRandomArmy();
		}
	}
}

RiskMap* Game::getMap() const
{
	return map;
}

void Game::gameLoop() const
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
			transferCountries(players->at(0), map);
		}

		counter++;
	}

	std::cout << "Player 1 won" << std::endl;
}

bool Game::checkWin() const
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
		player->addCountry((map->getCountry(i)));
	}
}