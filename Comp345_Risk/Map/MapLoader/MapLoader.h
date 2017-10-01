// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include "../RiskMap.h"

class MapLoader
{
public:
	explicit MapLoader(const std::string& location);
	~MapLoader();
	bool tryParseMap(RiskMap* result);

	std::string getLocation() const
	{
		return location;
	}

	inline void setLocation(std::string loc)
	{
		location = loc;
	}

	RiskMap getMap() const
	{
		return *riskMap;
	}

	bool successfullyParsed() const
	{
		return success;
	}

private:
	RiskMap* riskMap;
	std::string location;
	std::string current;
	bool success;
	bool parseMetaBlock(std::ifstream& stream);
	bool parseContinentBlock(std::ifstream& stream);
	bool parseCountryBlock(std::ifstream& stream);
};
