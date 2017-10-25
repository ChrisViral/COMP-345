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

#include "RiskMap.h"
#include <iostream>
#include <list>

RiskMap::RiskMap() : initialized(false)
{
}

RiskMap::~RiskMap()
{
}

int RiskMap::size() const
{
	return map.size();
}

int RiskMap::continentSize() const
{
	return continents.size();
}

bool RiskMap::isInitialized() const
{
	return initialized;
}

void RiskMap::setInitialized(bool init)
{
	initialized = init;
}

//Search through the map for a country by name, then add a new edge to that country.
bool RiskMap::addEdge(std::string targetCountry, Country& newCountry)
{
	//TODO: We should probably store the country's node in the object then use auxStorage to get the country here instead.
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].country->getName() == targetCountry)
		{
			Edge e;
			e.country = newCountry;
			map[i].adjList.push_back(e);
			return true;
		}
	}
	return false;
}

std::pair<Country, bool> RiskMap::addCountry(std::string countryName, std::string continentName)
{
	//inserts into the aux storage
	Country c(countryName, getContinent(continentName));
	std::pair<std::string, Country> pair(countryName, c);
	if (!auxStorage.insert(pair).second)
	{
		return std::make_pair(c, false);
	}

	//Push node into map
	//Chris: why not just use c above?
	Node n;
	n.country = &getCountry(countryName);
	map.push_back(n);

	return std::make_pair(c, true);
}

std::pair<Country, bool> RiskMap::addCountry(std::string countryName, std::string continentName, int x, int y)
{
	//inserts into the aux storage
	Country c(countryName, getContinent(continentName), x, y);
	std::pair<std::string, Country> pair(countryName, c);
	if (!auxStorage.insert(pair).second)
	{
		return std::make_pair(c, false);
	}

	//Push node into map
	Node n;
	n.country = &getCountry(countryName);
	map.push_back(n);

	return std::make_pair(c, true);
}

bool RiskMap::addContinent(std::string continentName, int controlVal)
{
	Continent continent = Continent(continentName, controlVal);
	std::pair<std::string, Continent> pair(continent.getName(), continent);
	return continents.insert(pair).second;
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

Country* RiskMap::getCountry(int index)
{
	return map[index].country;
}

void RiskMap::traverseMap()
{
	for (int i = 0; i < map.size(); i++)
	{
		std::cout << map[i].country->getName() << " (" << map[i].country->getContinent()->getName() << ")" << std::endl;

		for (int j = 0; j < map[i].adjList.size(); j++)
		{
			std::cout << "\t" << map[i].adjList[j].country.getName() << " (" << map[i].adjList[j].country.getContinent()->getName() << ")" << std::endl;
		}

		std::cout << std::endl;
	}
}

//A test to see if a source country can reach a destinatation country
bool RiskMap::isReachable(Country& source, Country& destination)
{
	if (source.getName() == destination.getName())
		return true;

	// Keep track of visited countries.
	std::unordered_map<std::string, bool> visited;

	//initialize them all to false
	std::unordered_map<std::string, Country>::iterator beg = auxStorage.begin();
	for (beg; beg != auxStorage.end(); ++beg)
	{
		std::pair<std::string, bool> pair(beg->first, false);
		visited.insert(pair);
	}

	//Create a queue and mark the source as visited
	std::list<std::string> queue;
	visited[source.getName()] = true;
	queue.push_back(source.getName());

	while (!queue.empty())
	{
		std::string name = queue.front();
		queue.pop_front();

		//Get edges 
		std::vector<Edge>::iterator i = getNodeFromMap(name).adjList.begin();
		for (i; i != getNodeFromMap(name).adjList.end(); ++i)
		{
			// If this adjacent node is the destination node, then 
			// return true
			if (i->country.getName() == destination.getName())
				return true;

			if (!visited[i->country.getName()])
			{
				visited[i->country.getName()] = true;
				queue.push_back(i->country.getName());
			}
		}
	}

	return false;
}

//Search the map for a Node by name of the country
Node& RiskMap::getNodeFromMap(std::string countrytName)
{
	//TODO: There should be a final return statement here, this isn't best practice
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i].country->getName() == countrytName)
		{
			return map[i];
		}
	}
}

void RiskMap::clearMap()
{
	map.clear();
	auxStorage.clear();
	continents.clear();
}

bool RiskMap::addCountriesToContinents()
{
	for (Node n : map)
	{
		std::string name = n.country->getContinent()->getName();
		if (!continents.count(name))
		{
			return false;
		}
		getContinent(name).addCountry(n);
	}
	return true;
}

/* This already exists (RiskMap::size())
int RiskMap::getCountryCount()
{
return auxStorage.size();
}
*/
