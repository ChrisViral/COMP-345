// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once

#include <unordered_map>
#include "../Base/RiskObject.h"
#include "Country.h"
#include "Continent.h"

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
	Country country;
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
	bool addEdge(std::string targetCountry, Country& newCountry);
	Country addCountry(std::string countryName, std::string continentName);
	Country addCountry(std::string countryName, std::string continentName, int x, int y);
	void addContinent(std::string continentName, int controlVal);
	Continent& getContinent(std::string continentName);
	Country& getCountry(std::string countrytName);
	void traverseMap();
	bool RiskMap::isReachable(Country& source, Country& destination);
	Node& getNodeFromMap(std::string countrytName);
	void clearMap();
	void RiskMap::addCountriesToContinents();
	int size() const;
	int continentSize() const;

private:
	std::unordered_map<std::string, Country> auxStorage;
	std::unordered_map<std::string, Continent> continents;
	std::vector<Node> map;
};
