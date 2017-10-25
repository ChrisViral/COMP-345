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

#pragma once

#include "../RiskMap.h"

using std::string;

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
