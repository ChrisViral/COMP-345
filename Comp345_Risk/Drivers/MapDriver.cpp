// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "../Map/RiskMap.h"
#include "MapDriver.h"
#include <iostream>

MapDriver::MapDriver()
{
}

MapDriver::~MapDriver()
{
}

std::string MapDriver::getOpeningMessage()
{
	return "Starting Map driver";
}

std::string MapDriver::getClosingMessage()
{
	return "Ending Map Driver";
}

void MapDriver::run()
{
	RiskMap rm;

	rm.addContinent("North America", 2);
	rm.addContinent("South America", 2);
	rm.addContinent("Europe", 2);

	//Countries in NA Continent
	rm.addCountry("Alberta", "North America");
	rm.addCountry("Ontario", "North America");
	rm.addCountry("Quebec", "North America");

	//Countries in SA Continent
	rm.addCountry("Peru", "South America");
	rm.addCountry("Brazil", "South America");
	rm.addCountry("Argentina", "South America");

	//Countries in EU Continent
	rm.addCountry("Iceland", "Europe");
	rm.addCountry("Scandinavia", "Europe");
	rm.addCountry("Ukraine", "Europe");

	//Add some edges
	rm.addEdge("Alberta", rm.getCountry("Ontario"));
	rm.addEdge("Ontario", rm.getCountry("Alberta"));
	rm.addEdge("Alberta", rm.getCountry("Quebec"));
	rm.addEdge("Quebec", rm.getCountry("Alberta"));
	rm.addEdge("Quebec", rm.getCountry("Peru"));
	rm.addEdge("Peru", rm.getCountry("Quebec"));
	rm.addEdge("Peru", rm.getCountry("Brazil"));
	rm.addEdge("Brazil", rm.getCountry("Peru"));
	rm.addEdge("Peru", rm.getCountry("Argentina"));
	rm.addEdge("Argentina", rm.getCountry("Peru"));
	rm.addEdge("Brazil", rm.getCountry("Argentina"));
	rm.addEdge("Argentina", rm.getCountry("Brazil"));
	rm.addEdge("Brazil", rm.getCountry("Iceland"));
	rm.addEdge("Iceland", rm.getCountry("Brazil"));
	rm.addEdge("Iceland", rm.getCountry("Scandinavia"));
	rm.addEdge("Scandinavia", rm.getCountry("Iceland"));
	rm.addEdge("Scandinavia", rm.getCountry("Ukraine"));
	rm.addEdge("Ukraine", rm.getCountry("Scandinavia"));
	rm.addEdge("Ukraine", rm.getCountry("Iceland"));
	rm.addEdge("Iceland", rm.getCountry("Ukraine"));

	rm.addCountriesToContinents();

	//traverse the map and display all the nodes
	rm.traverseMap();

	//traverse the Continents
	std::cout << "Traversing North America" << std::endl;
	rm.getContinent("North America").traverseCountries();

	std::cout << "Traversing South America" << std::endl;
	rm.getContinent("South America").traverseCountries();

	//A test to show that Alberta is reachable to Iceland.
	std::cout << "Test Path from Alberta to Iceland" << std::endl;
	if (rm.isReachable(rm.getCountry("Alberta"), rm.getCountry("Iceland")))
	{
		std::cout << "Path from Alberta to Iceland is reachable" << std::endl;
	}
	else
	{
		std::cout << "Path from Alberta to Iceland is unreachable" << std::endl;
	}

	//Clear the map for next test
	rm.clearMap();

	//Create Continents and Countries, but this time Continents will not be connected
	//This is a test to display that a map is invalid
	rm.addContinent("North America", 2);
	rm.addContinent("South America", 2);

	//Countries in NA Continent
	rm.addCountry("Alberta", "North America");
	rm.addCountry("Ontario", "North America");
	rm.addCountry("Quebec", "North America");

	//Countries in SA Continent
	rm.addCountry("Peru", "South America");
	rm.addCountry("Argentina", "South America");

	rm.addEdge("Alberta", rm.getCountry("Ontario"));
	rm.addEdge("Ontario", rm.getCountry("Alberta"));
	rm.addEdge("Alberta", rm.getCountry("Quebec"));
	rm.addEdge("Quebec", rm.getCountry("Alberta"));
	rm.addEdge("Peru", rm.getCountry("Argentina"));
	rm.addEdge("Argentina", rm.getCountry("Peru"));

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "-- starting second test to show invalid maps -- ";
	std::cout << std::endl;
	std::cout << std::endl;

	//A test to show that Alberta is not reachable to Peru
	std::cout << "Test Path from Alberta to Peru" << std::endl;
	if (rm.isReachable(rm.getCountry("Alberta"), rm.getCountry("Peru")))
	{
		std::cout << "\nPath from Alberta to Peru is reachable\n" << std::endl;
	}
	else
	{
		std::cout << "\nPath from Alberta to Peru is unreachable\n" << std::endl;
	}
}
