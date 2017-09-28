#pragma once
#include "..\RiskMap.h"

using namespace std;

class MapLoader
{
public:
	explicit MapLoader(const string& location);
	~MapLoader();
	bool tryParseMap(RiskMap& result);
	string getLocation() const
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
	string location;
	string current;
	bool success;
	bool parseMetaBlock(ifstream& stream);
	bool parseContinentBlock(ifstream& stream);
	bool parseCountryBlock(ifstream& stream);
};
