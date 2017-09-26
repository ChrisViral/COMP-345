#include "RiskMap.h"
#include <iostream>

RiskMap::RiskMap()
{
}

RiskMap::~RiskMap()
{
}

//Search through the map for a country by name, then add a new edge to that country.
void RiskMap::addEdge(std::string targetCountry, Country& newCountry)
{
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].country->getName() == targetCountry)
		{
			Edge e;
			e.country = &newCountry;
			map[i].adjList.push_back(e);			
		}
	}
}

void RiskMap::addCountry(std::string countryName, std::string continentName)
{	
	//inserts into the aux storage
	std::pair<std::string, Country> pair(countryName, Country(countryName, getContinent(continentName)));
	auxStorage.insert(pair);

	Node n;
	n.country = &getCountry(countryName);
	map.push_back(n);
}

void RiskMap::addContinent(std::string continentName, int controlVal)
{
	Continent continent = Continent(continentName,controlVal);
	std::pair<std::string, Continent> pair (continent.getName(), continent);
	continents.insert(pair);
}

Continent& RiskMap::getContinent(std::string continentName)
{
	std::unordered_map<std::string, Continent>::iterator found = continents.find(continentName);

	return found->second;
}

Country& RiskMap::getCountry(std::string countrytName)
{
	std::unordered_map<std::string, Country>::iterator found = auxStorage.find(countrytName);
	
	return found->second;
}

void RiskMap::traverseMap()
{
	for (int i = 0; i < map.size(); i++)
	{
		std::cout << map[i].country->getName() << " (" << map[i].country->getContinent()->getName() << ")" << std::endl;

		for (int j = 0; j < map[i].adjList.size(); j++)
		{
			std::cout << "\t" << map[i].adjList[j].country->getName() << " (" << map[i].adjList[j].country->getContinent()->getName() << ")" << std::endl;
		}
		
		std::cout << std::endl;
	}	
}