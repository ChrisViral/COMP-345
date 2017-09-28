#include "MapLoader.h"

#include <fstream>
#include <map>

#include "..\..\Base\Utils.h"
#include "..\RiskMap.h";


MapLoader::MapLoader(const string& location)
{
	this->location = location;
	success = true;
}

MapLoader::~MapLoader() { }

bool MapLoader::tryParseMap(RiskMap& result)
{
	ifstream stream(location);

	//If anything goes wrong, prevents crash, simply fail parse.
	try
	{
		success = parseMetaBlock(stream) && parseContinentBlock(stream) && parseCountryBlock(stream);
	}
	catch (exception)
	{
		success = false;
	}

	if (success)
	{
		//Finish map setup and pass to out pointer parameter
		riskMap.addCountriesToContinents();
		result = riskMap;
	}

	stream.close();
	return success;
}

bool MapLoader::parseMetaBlock(ifstream& stream)
{
	getline(stream, current);
	if (current != "[Map]") { return false; }

	while (getline(stream, current)  && current != "[Continents]")
	{
		vector<string> splits = split(current, '=');

		if (splits.size() != 2) { return false; }

		if (splits[0] == "author")
		{
			riskMap.metadata.author = splits[1];
		}
		if (splits[0] == "image")
		{
			riskMap.metadata.image = splits[1];
		}
		if (splits[0] == "wrap")
		{
			riskMap.metadata.wrap = boolFromYesNo(splits[1]);
		}
		if (splits[0] == "scroll")
		{
			riskMap.metadata.scroll = splits[1];
		}
		if (splits[0] == "warn")
		{
			riskMap.metadata.warn = boolFromYesNo(splits[1]);
		}
	}

	return true;
}

bool MapLoader::parseContinentBlock(ifstream& stream)
{
	while (getline(stream, current ) && current != "[Territories]")
	{
		vector<string> splits = split(current, '=');

		if (splits.size() != 2) { return false; }
		riskMap.addContinent(splits[0], stoi(splits[1]));
	}

	return true;
}

bool MapLoader::parseCountryBlock(ifstream& stream)
{
	while (getline(stream, current))
	{
		vector<string> splits = split(current, ',');

		//There should at lease be a name, two coordinates, a continent, and one adjacent country
		if (splits.size() < 5) { return false; }

		Country country = riskMap.addCountry(splits[0], splits[3], stoi(splits[1]), stoi(splits[2]));
		
		for (int i = 4; i < splits.size(); i++)
		{
			riskMap.addEdge(splits[i], country);
		}
	}
	return true;
}
