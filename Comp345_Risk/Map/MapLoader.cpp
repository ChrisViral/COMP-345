#include "MapLoader.h"

#include <fstream>
#include <map>

#include "../Base/Utils.h"
#include "RiskMap.h"


MapLoader::MapLoader() {
	successfullyParsed = true;
}


MapLoader::~MapLoader() {
}

std::pair<bool, RiskMap> MapLoader::loadFromMapFile(const std::string& map) {
	
	std::ifstream mapstream(map);
	

	std::string line;

	getline(mapstream, line);
	// TODO: write ur parser using a fsm
	if (line == "[Map]") {
		parseMetaBlock(mapstream, line);
	}
	else if (line == "[Continents]") {
		parseContinentBlock(mapstream, line);
	}
	else if (line == "[Territories]") {
		parseCountryBlock(mapstream, line);
	}
	else {
		// The map file is not formatted properly
		successfullyParsed = false;
	}
	
		
	mapstream.close();
	return std::make_pair(successfullyParsed, riskMap);
}

void MapLoader::parseMetaBlock(std::ifstream& stream, std::string& line) {
	while (std::getline(stream, line)) {
		if (line == "[Continents]") {
			parseContinentBlock(stream, line);
		} else {
			if (startsWith(line, "author")) {
				std::vector<std::string> row = split(line, '=');
				riskMap.metadata.author = row[1];
			}
			if (startsWith(line, "image")) {
				std::vector<std::string> row = split(line, '=');
				riskMap.metadata.image = row[1];
			}
			if (startsWith(line, "wrap")) {
				std::vector<std::string> row = split(line, '=');
				riskMap.metadata.wrap = boolFromYesNo(row[1]);
			}
			if (startsWith(line, "scroll")) {
				std::vector<std::string> row = split(line, '=');
				riskMap.metadata.scroll = row[1];
			}
			if (startsWith(line, "warn")) {
				std::vector<std::string> row = split(line, '=');
				riskMap.metadata.warn = boolFromYesNo(row[1]);
			}
		}

	}

}

void MapLoader::parseContinentBlock(std::ifstream& stream, std::string& line) {
	while (std::getline(stream, line)) {
		if (line == "[Territories]") {
			parseCountryBlock(stream, line);
		} else {
			std::vector<std::string> row = split(line, '=');
			
		}
	}
}

void MapLoader::parseCountryBlock(std::ifstream& stream, std::string& line) {
}

void MapLoader::parseCountryRow(std::ifstream& stream, std::string& line) {
}



