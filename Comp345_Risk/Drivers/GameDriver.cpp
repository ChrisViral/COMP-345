#include "GameDriver.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Game/Game.h"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

GameDriver::GameDriver()
{
}

GameDriver::~GameDriver()
{
}

void GameDriver::run()
{
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	vector<Player*>* players = new vector<Player*>(4);
	players->push_back(new Player("Player 1", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 2", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 3", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 4", DiceRoller(), vector<Country>(), Hand()));

	Game game(players, map);
	game.setup();

	for (int i = 0; i < map->size(); i++)
	{
		Country* c = map->getCountry(i);
		cout << c->getName() << "'s owner is " << c->getOwner()->getName() << endl;
		cout << "There are " << c->getArmies() << " armies stationed in " << c->getName();
	}

	for (int i = 0; i < 4; i++)
	{
		Player* p = players->at(i);
		vector<Country> countries = p->getCountries();

		cout << p->getName() << " owns " << countries.size() << " countries" << endl;

		int armies = 0;
		for (Country c : countries)
		{
			armies += c.getArmies();
		}

		cout << p->getName() << " has a total of " << armies << " placed on the board" << endl;
		cout << "This means " << p->getName() << " has placed a total of " << (armies - countries.size()) << " armies on the board during the setup phase." << endl;
	}

	delete map;
	map = nullptr;

	delete players->at(0);
	delete players->at(1);
	delete players->at(2);
	delete players->at(3);
	players->clear();

	delete players;
	players = nullptr;
}

string GameDriver::getOpeningMessage()
{
	return "Starting Game driver";
}

string GameDriver::getClosingMessage()
{
	return "Ending Game driver";
}
