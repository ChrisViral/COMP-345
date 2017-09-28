// Comp345_Risk.cpp : Defines the entry point for the console application.

#include <iostream>
#include <vector>
#include "Drivers/Driver.h";
#include "Drivers/CardDriver.h"
#include "Drivers/MapDriver.h"
#include "Drivers/MapLoaderDriver.h"

int main()
{
	MapDriver map;
	MapLoaderDriver loader;
	CardDriver card;
	std::vector<Driver*> drivers(3);
	drivers[0] = &map;
	drivers[1] = &loader;
	drivers[2] = &card;

	std::cout << "Beginning driver tests" << std::endl;
	for (Driver* d : drivers)
	{
		std::cout << d->getOpeningMessage() << std::endl;
		d->run();
		std::cout << d->getClosingMessage() << std::endl;
	}
	std::cout << "Ended driver tests" << std::endl;
}
