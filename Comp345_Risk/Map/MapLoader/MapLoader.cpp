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

#include "MapLoader.h"
#include "../../Base/Utils.h"
#include "../RiskMap.h";

#include <fstream>

using std::vector;

/**
* Creates a new MapLoader from a file at a given location in the current working directory
* @param loc String location of the mapfile to load in the memory
*/
MapLoader::MapLoader(const string& loc) : riskMap(nullptr), current(""), error(""), line(0), success(false)
{
	location = loc;
}

/**
* MapLoader destructor
*/
MapLoader::~MapLoader()
{
}

/**
* Returns the current working RiskMap of this MapLoader
* @returns RiskMap being loaded
*/
RiskMap* MapLoader::getMap() const
{
	return riskMap;
}

/**
* Tries to parse a RiskMap from a on disk .map text file
* @param result Pointer to the RiskMap to load into
* @returns Result structure containing information about the loading
*/
MapLoader::LoaderResults MapLoader::tryParseMap(RiskMap* result)
{
	//If the map is already initialized, return immediately
	if (result->isInitialized())
	{
		error = "This map has already been initialized";
	}
	else
	{
		//Setup
		success = true;
		riskMap = result;
		riskMap->setInitialized(true);
		std::ifstream stream(location);

		//If anything goes wrong, prevents crash, simply fail parse.
		try
		{
			//Try and parse the map info
			success = parseMetaBlock(stream) && parseContinentBlock(stream) && parseCountryBlock(stream);
		}
		catch (std::exception e)
		{
			//If an error occurs, the map is considered invalid
			success = false;
			riskMap = nullptr;
			std::stringstream ss;
			ss << "EXCEPTION: " << e.what() << "happened while loading the map, unable to proceed normally.";
			error = ss.str();
		}

		//Close the stream
		stream.close();

		if (success)
		{
			if (riskMap->size() == 0)
			{
				error = "This map contains no countries.";
				success = false;
			}
			else if (riskMap->continentSize() == 0)
			{
				error = "This map contains no continents.";
				success = false;
			}
		}
	}

	//Return a new LoaderResults structure containing the relevant info
	return {riskMap, success, error};
}

/**
* Parses the [Map] block of a .map file
* @param stream File stream to the file being read
* @returns False if an issue arose, true otherwise
*/
bool MapLoader::parseMetaBlock(std::ifstream& stream)
{
	while (current.size() == 0)
	{
		getline(stream, current);
		line++;
	}
	if (current != "[Map]")
	{
		error = "Wrong header block where [Map] is expected @" + line;
		return false;
	}

	for (line++; getline(stream, current) && current != "[Continents]"; line++)
	{
		if (current.size() == 0) { continue; }

		vector<string> splits = split(current, '=');
		if (splits.size() != 2)
		{
			error = "Wrong line format, incorrect amount of equal signs @" + line;
			return false;
		}

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

	if (current != "[Continents]")
	{
		error = "Wrong header block where [Continents] is expected @" + line;
		return false;
	}

	return true;
}

/**
* Parses the [Continents] block of a .map file
* @param stream File stream to the file being read
* @returns False if an issue arose, true otherwise
*/
bool MapLoader::parseContinentBlock(std::ifstream& stream)
{
	for (line++; getline(stream, current) && current != "[Territories]"; line++)
	{
		if (current.size() == 0) { continue; }
		vector<string> splits = split(current, '=');

		if (splits.size() != 2)
		{
			error = "Wrong line format, incorrect amount of equal signs @" + line;
			return false;
		}
		if (!riskMap->addContinent(splits[0], stoi(splits[1])))
		{
			error = "Dupplicate Continent " + splits[0] + " detected @" + std::to_string(line);
			return false;
		}
	}

	if (current != "[Territories]")
	{
		error = "Wrong header block where [Territories] is expected @" + line;
		return false;
	}

	return true;
}

/**
* Parses the [Territories] block of a .map file
* @param stream File stream to the file being read
* @returns False if an issue arose, true otherwise
*/
bool MapLoader::parseCountryBlock(std::ifstream& stream)
{
	vector<std::pair<string, Country*>> edges;
	while (getline(stream, current))
	{
		if (current.size() == 0) { continue; }
		vector<string> splits = split(current, ',');

		//There should at lease be a name, two coordinates, a continent, and one adjacent country
		if (splits.size() < 5)
		{
			error = "Invalid amount of Country data @" + line;
			return false;
		}

		std::pair<Country*, bool> p = riskMap->addCountry(splits[0], splits[3], stoi(splits[1]), stoi(splits[2]));
		if (!p.second)
		{
			error = "Dupplicate Country " + splits[0] + " detected @" + std::to_string(line);
			return false;
		}

		for (int i = 4; i < splits.size(); i++)
		{
			edges.push_back(make_pair(splits[i], p.first));
		}
	}

	//Setup edges and continents
	for (std::pair<string, Country*> p : edges)
	{
		if (!riskMap->addEdge(p.first, *p.second))
		{
			error = "Could not find the adjacent Country " + p.first + " to connect to " + p.second->getName();
			return false;
		}
	}
	if (!riskMap->addCountriesToContinents())
	{
		error = "One of the Countries has an invalid Continent name.";
		return false;
	}
	return true;
}
