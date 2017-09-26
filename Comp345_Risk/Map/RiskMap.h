#pragma once

#include <string>
#include <unordered_map>
#include "../Base/RiskObject.h"
#include "../Map/Country.h"
#include "../Map/Continent.h"

struct MapMetaData
{
	std::string author;
	std::string image;
	bool wrap;
	std::string scroll;
	bool warn;
};

struct Edge
{
	Country* country;
};

struct Node
{
	Country* country;
	std::vector<Edge> adjList;
};

class RiskMap : public RiskObject
{
public:
	MapMetaData metadata;

	RiskMap();
	~RiskMap();
	void addEdge(std::string targetCountry, Country& newCountry);
	void addCountry(std::string countryName, std::string continentName);
	void addContinent(std::string continentName, int controlVal);
	Continent& getContinent(std::string continentName);
	Country& getCountry(std::string countrytName);
	void traverseMap();
private:
	std::unordered_map<std::string, Country> auxStorage;
	std::unordered_map<std::string, Continent> continents;
	std::vector<Node> map;
};

