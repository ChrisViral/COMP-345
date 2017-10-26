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
#include <iostream>

void transferCountries(Player* player, RiskMap* map);

Game::Game()
{
	map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	players.push_back(new Player(DiceRoller(), std::vector<Country>(), Hand()));
	players.push_back(new Player(DiceRoller(), std::vector<Country>(), Hand()));
	players.push_back(new Player(DiceRoller(), std::vector<Country>(), Hand()));
}

Game::~Game()
{
}

void Game::gameLoop()
{
	int counter = 1;
	while (!checkWin(players, map))
	{
		for (int i = 0; i < players.size(); i++)
		{
			std::cout << "Player " << i + 1 << std::endl;
			players[i]->reinforce(true);
			players[i]->attack(true);
			players[i]->fortify(Country(), Country(), 0, true); //Dummy arguements for this part
			std::cout << std::endl;
		}

		if (counter > 3)
		{
			transferCountries(players[0], map);
		}

		counter++;
	}

	std::cout << "Player 1 won" << std::endl;
}

bool Game::checkWin(std::vector<Player*> players, RiskMap* map)
{
	for each (Player* player in players)
	{
		if (player->getCountries().size() == map->size())
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