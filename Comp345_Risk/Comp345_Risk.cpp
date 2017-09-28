#include <cstdio>
#include <iostream>
#include <vector>
#include "Drivers/Driver.h";
#include "Drivers/CardDriver.h"
#include "Drivers/MapLoaderDriver.h"
#include "Drivers/MapDriver.h"
#include "Drivers/DiceDriver.h"
#include "Drivers/PlayerDriver.h"

//Comp345_Risk.cpp : Defines the entry point for the console application.
int main()
{
	MapDriver map;
	MapLoaderDriver loader;
	CardDriver card;
	DiceDriver dice;
	PlayerDriver player;
	std::vector<Driver*> drivers(5);
	drivers[0] = &map;
	drivers[1] = &loader;
	drivers[2] = &card;
	drivers[3] = &dice;
	drivers[4] = &player;

	const std::string endll = "\n\n";

	//Batch run, run all drivers
	std::cout << "Beginning driver tests" << endll;
	for (Driver* d : drivers)
	{
		std::cout << "=====================================================================" << endll;
		std::cout << d->getOpeningMessage() << endll;
		d->run();
		std::cout << std::endl << d->getClosingMessage() << endll;
	}
	std::cout << "=====================================================================" << endll;
	std::cout << "Ended driver tests" << endll;

	std::cout << "Press any key to exit...";
	getchar();

	//Unique run, uncomment to run a specific driver
	//map.run();
	//loader.run();
	//card.run();
	//dice.run();
	//player.run();

	return 0;
}
