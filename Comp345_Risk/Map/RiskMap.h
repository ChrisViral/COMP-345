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

#include "../Base/RiskObject.h"
#include "Country.h"
#include "Continent.h"
#include <unordered_map>


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
	bool addEdge(std::string targetCountry, Country& newCountry);
	std::pair<Country*, bool> addCountry(std::string countryName, std::string continentName);
	std::pair<Country*, bool> addCountry(std::string countryName, std::string continentName, int x, int y);
	bool addContinent(std::string continentName, int controlVal);
	Continent& getContinent(std::string continentName);
	Country* getCountry(std::string countrytName);
	Country* getCountry(int index);
	void traverseMap();
	bool RiskMap::isReachable(Country& source, Country& destination);
	bool RiskMap::isReachable(Player* p, Country& source, Country& destination);
	Node& getNodeFromMap(std::string countrytName);
	void clearMap();
	bool RiskMap::addCountriesToContinents();
	int size() const;
	int continentSize() const;
	bool isInitialized() const;
	void setInitialized(bool init);
	std::unordered_map<std::string, Continent> getContinents();
	void printMapArmyInfo();


private:
	bool initialized;
	std::unordered_map<std::string, Country*> auxStorage;
	std::unordered_map<std::string, Continent> continents;
	std::vector<Node> map;
};
