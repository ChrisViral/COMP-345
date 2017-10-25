#include "GameStartDriver.h"
#include <iostream>
#include "../Player/Player.h"
#include "../Player/Card/Deck.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Game/GameStart.h"

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
	GameStart gamestart;

	gamestart.askForMap();

	std::string mapString = "mapfiles/" + gamestart.getMapNames()[gamestart.getMapNumber() - 1] + ".map";

	RiskMap* map = new RiskMap();
	MapLoader mapLoader(mapString);

	MapLoader::LoaderResults results = mapLoader.tryParseMap(map);

	while (!results.success)
	{
		std::cout << std::endl;
		std::cout << "The map could not be parsed sucessfully" << std::endl;
		gamestart.askForMap();

		mapString = "mapfiles/" + gamestart.getMapNames()[gamestart.getMapNumber() - 1] + ".map";

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

	//Create the deck
	Deck deck(map->size());

	std::cout << std::endl;

	//Get input from the user for the number of players
	gamestart.askForPlayers();

	//Create the players
	std::vector<Player> players;
	for (int i = 0; i < gamestart.getNumberOfPlayers(); i++)
	{
		players.push_back(Player(DiceRoller(), std::vector<Country>(), Hand()));
	}

	std::cout << "The number of countries in the map: " << map->size() << std::endl;
	std::cout << "The number of cards in the deck: " << deck.getDeckSize() << std::endl;
	std::cout << "The number of players in the game: " << players.size() << std::endl;

	delete map;
}
