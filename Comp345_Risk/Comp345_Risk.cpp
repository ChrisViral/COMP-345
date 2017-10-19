// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#include "Base/Driver.h";

#include <cstdio>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

//Comp345_Risk.cpp : Defines the entry point for the console application.
int main()
{
	vector<Driver*> drivers(6);

	const std::string endll = "\n\n";

	//Batch run, run all drivers
	cout << "Beginning driver tests" << endll;
	for (Driver* d : drivers)
	{
		cout << "=====================================================================" << endll;
		cout << d->getOpeningMessage() << endll;
		d->run();
		cout << std::endl << d->getClosingMessage() << endll;
	}
	cout << "=====================================================================" << endll;
	cout << "Ended driver tests" << endll;

	cout << "Press any key to exit...";
	getchar();

	return 0;
}
