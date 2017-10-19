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
	struct LoaderResults
	{
		RiskMap* riskMap;
		bool success;
		string failureMessage;
	};

	explicit MapLoader(const string& location);
	~MapLoader();
	LoaderResults tryParseMap(RiskMap* result);
	RiskMap* getMap() const;

private:
	RiskMap* riskMap;
	string location;
	string current;
	string error;
	int line;
	bool success;
	bool parseMetaBlock(std::ifstream& stream);
	bool parseContinentBlock(std::ifstream& stream);
	bool parseCountryBlock(std::ifstream& stream);
};