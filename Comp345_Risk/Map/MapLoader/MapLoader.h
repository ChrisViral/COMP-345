#pragma once
#include "../RiskMap.h"

class MapLoader
{
public:
	explicit MapLoader(const std::string& location);
	~MapLoader();
	bool tryParseMap(RiskMap& result);

	std::string getLocation() const
	{
		return location;
	}
	RiskMap getMap() const
	{
		return riskMap;
	}
	bool successfullyParsed() const
	{
		return success;
	}

private:
	RiskMap riskMap;
	std::string location;
	std::string current;
	bool success;
	bool parseMetaBlock(std::ifstream& stream);
	bool parseContinentBlock(std::ifstream& stream);
	bool parseCountryBlock(std::ifstream& stream);
};
