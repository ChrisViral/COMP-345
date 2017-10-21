// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include <cstdio>
#include <iostream>
#include <vector>
#include "Base/Driver.h";

//Comp345_Risk.cpp : Defines the entry point for the console application.
int main()
{
	std::vector<Driver*> drivers(6);

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

	return 0;
}
