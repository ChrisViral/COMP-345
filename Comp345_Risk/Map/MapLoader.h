#pragma once
#include <string>
#include "RiskMap.h"


class MapLoader {
public:
	MapLoader();
	~MapLoader();
	std::pair<bool, RiskMap> loadFromMapFile(const std::string& mapfile);
	
private:
	RiskMap riskMap;
	bool successfullyParsed;
	void parseMetaBlock(std::ifstream& stream, std::string& line);
	void parseContinentBlock(std::ifstream& stream, std::string& line);
	void parseCountryBlock(std::ifstream& stream, std::string& line);
	void parseCountryRow(std::ifstream& stream, std::string& line);




};

