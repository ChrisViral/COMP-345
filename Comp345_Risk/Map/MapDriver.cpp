#include "../Map/RiskMap.h"
#include "../Map/Country.h"

void main()
{
	RiskMap rm;	

	rm.addContinent("North America",2);
	rm.addContinent("South America",2);
	rm.addContinent("Europe",2);

	//Countries in NA Continent
	rm.addCountry("Alberta","North America");
	rm.addCountry("Ontario","North America");
	rm.addCountry("Quebec","North America");

	//Countries in SA Continent
	rm.addCountry("Peru","South America");
	rm.addCountry("Brazil", "South America");
	rm.addCountry("Argentina", "South America");

	//Countries in EU Continent
	rm.addCountry("Iceland","Europe");
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

	rm.traverseMap();
}