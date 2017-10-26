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
	//Load the basic map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>(4);
	players->push_back(new Player("Player 1", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 2", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 3", DiceRoller(), vector<Country>(), Hand()));
	players->push_back(new Player("Player 4", DiceRoller(), vector<Country>(), Hand()));

	//Load a game with the above info and run the setup
	Game game(players, map);
	game.setup();				//We want to know how this affected the players and map


	//Look at all the countries
	for (int i = 0; i < map->size(); i++)
	{
		//See who owns the country and how many armies are stationed there
		Country* c = map->getCountry(i);
		cout << c->getName() << "'s owner is " << c->getOwner()->getName() << endl;
		cout << "There are " << c->getArmies() << " armies stationed in " << c->getName();
	}

	//Look at all the players
	for (int i = 0; i < 4; i++)
	{
		Player* p = players->at(i);
		vector<Country> countries = p->getCountries();

		//See how many countries they own
		cout << p->getName() << " owns " << countries.size() << " countries" << endl;

		//Count player's armies
		int armies = 0;
		for (Country c : countries)
		{
			//See what country the player owns
			cout << p->getName() << " owns " << c.getName() << " and has " << c.getArmies() << " armies stationed there" << endl;
			armies += c.getArmies();
		}

		//See total amount of armies owned by a player
		cout << p->getName() << " has a total of " << armies << " placed on the board" << endl;
		cout << "This means " << p->getName() << " has placed a total of " << (armies - countries.size()) << " armies on the board during the setup phase" << endl;
	}

	//Clear memory
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