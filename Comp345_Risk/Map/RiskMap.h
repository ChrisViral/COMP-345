#pragma once

#include <string>
#include "../Base/RiskObject.h"


struct MapMetaData {
	std::string author;
	std::string image;
	bool wrap;
	std::string scroll;
	bool warn;
};


class RiskMap : public RiskObject {
public:
	RiskMap();
	~RiskMap();

	MapMetaData metadata;
	//std::set<Continent> continents;
	//std::unordered_map<Country, std::set<Country>> connections;
};

