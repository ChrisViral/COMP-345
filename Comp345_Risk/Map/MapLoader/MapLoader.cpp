// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "MapLoader.h"

#include <fstream>
#include <map>

#include "../../Base/Utils.h"
#include "../RiskMap.h";


MapLoader::MapLoader(const std::string& location): riskMap(nullptr)
{
	this->location = location;
	success = true;
	current = "";
}

MapLoader::~MapLoader()
{
}

bool MapLoader::tryParseMap(RiskMap* result)
{
	std::ifstream stream(location);
	riskMap = result;
	//If anything goes wrong, prevents crash, simply fail parse.
	try
	{
		success = parseMetaBlock(stream) && parseContinentBlock(stream) && parseCountryBlock(stream);
	}
	catch (std::exception)
	{
		success = false;
	}


	stream.close();
	return success && riskMap->size() > 0 && riskMap->continentSize() > 0;
}

bool MapLoader::parseMetaBlock(std::ifstream& stream)
{
	while (current.size() == 0) { getline(stream, current); }
	if (current != "[Map]") { return false; }

	while (getline(stream, current) && current != "[Continents]")
	{
		if (current.size() == 0) { continue; }

		std::vector<std::string> splits = split(current, '=');
		if (splits.size() != 2) { return false; }

		if (splits[0] == "author")
		{
			riskMap->metadata.author = splits[1];
		}
		else if (splits[0] == "image")
		{
			riskMap->metadata.image = splits[1];
		}
		else if (splits[0] == "wrap")
		{
			riskMap->metadata.wrap = boolFromYesNo(splits[1]);
		}
		else if (splits[0] == "scroll")
		{
			riskMap->metadata.scroll = splits[1];
		}
		else if (splits[0] == "warn")
		{
			riskMap->metadata.warn = boolFromYesNo(splits[1]);
		}
	}

	return current == "[Continents]";
}

bool MapLoader::parseContinentBlock(std::ifstream& stream)
{
	while (getline(stream, current) && current != "[Territories]")
	{
		if (current.size() == 0) { continue; }
		std::vector<std::string> splits = split(current, '=');

		if (splits.size() != 2) { return false; }
		riskMap->addContinent(splits[0], stoi(splits[1]));
	}

	return current == "[Territories]";
}

bool MapLoader::parseCountryBlock(std::ifstream& stream)
{
	std::vector<std::pair<std::string, Country>> edges;
	while (getline(stream, current))
	{
		if (current.size() == 0) { continue; }
		std::vector<std::string> splits = split(current, ',');

		//There should at lease be a name, two coordinates, a continent, and one adjacent country
		if (splits.size() < 5) { return false; }

		Country country = riskMap->addCountry(splits[0], splits[3], stoi(splits[1]), stoi(splits[2]));

		for (int i = 4; i < splits.size(); i++)
		{
			edges.push_back(make_pair(splits[i], country));
		}
	}

	//Setup edges and continents
	for (std::pair<std::string, Country> p : edges)
	{
		if (!riskMap->addEdge(p.first, p.second))
		{
			return false;
		}
	}
	riskMap->addCountriesToContinents();
	return true;
}
