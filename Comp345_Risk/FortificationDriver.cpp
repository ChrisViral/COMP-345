#include "FortificationDriver.h"
#include "Player/Player.h"
#include "Map/RiskMap.h"
#include "Map/MapLoader/MapLoader.h"
#include "Player/Card/Deck.h"


FortificationDriver::FortificationDriver()
{
}


FortificationDriver::~FortificationDriver()
{
}

void FortificationDriver::run()
{



	
	std::string mapFile = "mapfiles/World.map";
	RiskMap map;
	MapLoader mapLoader(mapFile);
	MapLoader::LoaderResults results = mapLoader.tryParseMap(&map);

	Deck d(map.size());

	//Country& c1 = map.getCountry("");
	//Country& c2 = map.getCountry("");


	
	DiceRoller roller;
	std::vector<Country> playersTerritories;

	Hand h;

	while (!d.isEmpty()) {
		h.addCard(d.draw());
	}

	Player p(roller, playersTerritories, h);

	
}

std::string FortificationDriver::getOpeningMessage()
{
	return "Starting Fortification driver";
}

std::string FortificationDriver::getClosingMessage()
{
	return "Ending Fortification driver";
}


