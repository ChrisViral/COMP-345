#include "GameStart.h"
#include <fstream>
#include <iostream>
#include <string>
#include "../Map/MapLoader/MapLoader.h"


GameStart::GameStart(): deck(0)  //create a deck of size 0, it will get created with the proper size after the map is selected
{
	readFileNames();
}

GameStart::~GameStart()
{
	delete map;
}

void GameStart::askForMap()
{
	std::cout << "Select a map from the list. Enter the map's number" << std::endl;

	//Display the map names
	for (int i = 0; i < mapNames.size(); i++)
	{
		std::cout << i + 1 << ") " << mapNames[i] << std::endl;
	}

	//Get input from the user for the map number
	std::cin >> mapNumber;

	while (mapNumber <= 0 || mapNumber > mapNames.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a valid number" << std::endl;
		std::cout << "Select a map from the list. Enter the map's number" << std::endl;

		std::cin >> mapNumber;
	}
}

void GameStart::askForPlayers()
{
	std::cout << "Enter the number of players (from 2 - 6)" << std::endl;
	std::cin >> numOfPlayers;

	//Keep looping until the enter a valid number of players
	while (numOfPlayers < 2 || numOfPlayers > 6)
	{
		std::cout << "You entered the wrong number of players. Enter between 2 - 6" << std::endl;
		std::cin >> numOfPlayers;
	}
	
}

//create the players
void GameStart::createPlayers()
{	
	players = new vector<Player*>(numOfPlayers);
	for (int i = 0; i < numOfPlayers; i++)
	{
		players->push_back(new Player("Player " + (i + 1), DiceRoller(), vector<Country>(), Hand()));
	}
}

//Return a vector with the file names. If you add a new map to the folder, the list.txt file needs to be updated.
void GameStart::readFileNames()
{
	//Open the file
	std::ifstream input;
	input.open("mapfiles/list.txt");

	//Push all the file names in the vector
	std::string map;
	while (getline(input, map))
	{
		mapNames.push_back(map);
	}

}

void GameStart::createMap()
{
	map = new RiskMap();
	mapString = "mapfiles/" + getMapNames()[mapNumber - 1] + ".map";
	MapLoader mapLoader(mapString);

	MapLoader::LoaderResults results = mapLoader.tryParseMap(map);

	while (!results.success)
	{
		std::cout << std::endl;
		std::cout << "The map could not be parsed sucessfully" << std::endl;
		askForMap();

		mapString = "mapfiles/" + getMapNames()[mapNumber - 1] + ".map";

		//Delete the bad map object and create a new one
		delete map;
		map = new RiskMap();
		mapLoader = MapLoader(mapString);
		results = mapLoader.tryParseMap(map);
	}

	if (results.success)
	{
		MapMetaData meta = map->metadata;
		std::cout << " ==== METADATA ====" << std::endl;
		std::cout << "Author: " << meta.author << std::endl;
		std::cout << "Image: " << meta.image << std::endl;
		std::cout << "Scroll: " << meta.scroll << std::endl;
		std::cout << "Warn: " << (meta.warn ? "Yes" : "No") << std::endl;
		std::cout << "Wrap: " << (meta.wrap ? "Yes" : "No") << std::endl;

		std::cout << std::endl << " ==== MAP TRAVERSAL ====" << std::endl;
		map->traverseMap();

		std::cout << std::endl;
	}
}

void GameStart::createDeck()
{
	deck = Deck(map->size());
}

void GameStart::startGame()
{
	game = new Game(players, map);
	game->setup();
}

