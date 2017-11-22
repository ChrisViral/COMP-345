// ==============================
//           COMP-345 D
//          Assignment 3
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#include "Base/Driver.h";
#include <iostream>
#include <vector>
#include "Drivers/TournamentDriver.h"
#include "Drivers/StrategyDriver.h"


using std::cout;
using std::vector;

//Comp345_Risk.cpp : Defines the entry point for the console application.
int main()
{
	vector<Driver*> drivers;

	TournamentDriver tournament;
	StrategyDriver strategy;

	const string endll = "\n\n";

	//Run drivers individually

	Driver* d = &strategy;
	cout << d->getOpeningMessage() << endll;
	d->run();
	cout << std::endl << d->getClosingMessage() << endll;

	/*
	//Batch run, run all drivers
	drivers.push_back(&tournament);
	drivers.push_back(&strategy);
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
	*/

	cout << "Press any key to exit...";
	getchar();

	return 0;
}
