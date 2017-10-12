#include "GameStartDriver.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "../Player/Player.h"
#include "../Player/Card/Deck.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"

std::vector<std::string> readFileNames();
void askForMap(int&,std::vector<std::string>);

GameStartDriver::GameStartDriver()
{

}

GameStartDriver::~GameStartDriver()
{

}

std::string GameStartDriver::getOpeningMessage()
{
	return "Starting Game Start driver";
}

std::string GameStartDriver::getClosingMessage()
{
	return "Ending Game Start driver";
}

void GameStartDriver::run()
{
	int numOfPlayers;
	int mapNumber;
	std::vector<std::string> list = readFileNames();

	askForMap(mapNumber,list);

	std::string mapString = "mapfiles/" + list[mapNumber - 1] + ".map";
	
	RiskMap* map = new RiskMap();
	MapLoader mapLoader(mapString);	

	bool success = mapLoader.tryParseMap(map);

	while (!success)
	{
		std::cout << std::endl;
		std::cout << "The map could not be parsed sucessfully" << std::endl;
		askForMap(mapNumber, list);

		mapString = "mapfiles/" + list[mapNumber - 1] + ".map";

		//Delete the bad map object and create a new one
		delete map;
		map = new RiskMap();
		mapLoader = MapLoader(mapString);
		success = mapLoader.tryParseMap(map);
	}

	if (success)
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

	//Create the deck
	Deck deck(map->size());	

	std::cout << std::endl;
	std::cout << "Enter the number of players (from 2 - 6)" << std::endl;

	//Get input from the user for the number of players
	std::cin >> numOfPlayers;

	//Keep looping until the enter a valid number of players
	while (numOfPlayers < 2 || numOfPlayers > 6)
	{
		std::cout << "You entered the wrong number of players. Enter between 2 - 6" << std::endl;
		std::cin >> numOfPlayers;
	}

	//Create the players with
	std::vector<Player> players;
	for (int i = 0; i < numOfPlayers; i++)
	{		
		players.push_back(Player(DiceRoller(), std::vector<Country>(), Hand()));
	}

	std::cout << "The number of countries in the map: " << map->size() << std::endl;
	std::cout << "The number of cards in the deck: " << deck.getDeckSize() << std::endl;
	std::cout << "The number of players in the game: " << players.size() << std::endl;
	
	delete map;
}

//Return a vector with the file names. If you add a new map to the folder, the list.txt file needs to be updated.
std::vector<std::string> readFileNames()
{
	//Open the file
	std::ifstream input;
	input.open("mapfiles/list.txt");
	
	//Push all the file names in the vector
	std::vector<std::string> list;
	std::string map;
	while (getline(input, map))
	{
		list.push_back(map);
	}

	return list;
}

void askForMap(int& mapNumber,std::vector<std::string> list)
{
	std::cout << "Select a map from the list. Enter the map's number" << std::endl;

	//Display the map names
	for (int i = 0; i < list.size(); i++)
	{
		std::cout << i + 1 << ") " << list[i] << std::endl;
	}	

	//Get input from the user for the map number
	std::cin >> mapNumber;	

	while (mapNumber <= 0 || mapNumber > list.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a valid number" << std::endl;
		std::cout << "Select a map from the list. Enter the map's number" << std::endl;

		std::cin >> mapNumber;
	}
}