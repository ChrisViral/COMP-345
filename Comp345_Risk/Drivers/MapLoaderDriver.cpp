#include "MapLoaderDriver.h"
#include "../Map/MapLoader/MapLoader.h"
#include <string>
#include <iostream>

MapLoaderDriver::MapLoaderDriver() { }

MapLoaderDriver::~MapLoaderDriver() { }

std::string MapLoaderDriver::getOpeningMessage()
{
	return "Starting Map Loader driver";
}

std::string MapLoaderDriver::getClosingMessage()
{
	return "Ending Map Loader driver";
}

void MapLoaderDriver::run()
{
	std::cout << "Loading World.map" << std::endl;
	loadMap("mapfiles/World.map");

	std::cout << "Loading Lord of the Rings.map" << std::endl;
	loadMap("mapfiles/Lord of the Rings.map");

	std::cout << "Broken.map" << std::endl;
	loadMap("mapfiles/broken.map");
}

void MapLoaderDriver::loadMap(const std::string path)
{
	MapLoader loader(path);
	RiskMap* map = new RiskMap();
	bool success = loader.tryParseMap(map);

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
	else
	{
		std::cout << "The map could not be parsed sucessfully" << std::endl << std::endl;
	}

	delete map;
}
