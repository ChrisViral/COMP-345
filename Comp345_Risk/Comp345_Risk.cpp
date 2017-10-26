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

#include "Base/Driver.h";

#include <cstdio>
#include <iostream>
#include <vector>
#include "Drivers/GameStartDriver.h"
#include "Drivers/GameDriver.h"
#include "Drivers/MainGameLoopDriver.h"
#include "Drivers/ReinforceDriver.h"
#include "Drivers/FortificationDriver.h"

using std::cout;
using std::vector;

//Comp345_Risk.cpp : Defines the entry point for the console application.
int main()
{
	vector<Driver*> drivers;
	GameStartDriver start;
	GameDriver game;
	MainGameLoopDriver loop;
	ReinforceDriver reinforce;
	//AttackDriver attack;		//Adriano implementation
	FortificationDriver fortify;

	drivers.push_back(&start);
	drivers.push_back(&game);
	drivers.push_back(&loop);
	drivers.push_back(&reinforce);
	//drivers.push_back(&attack); //Adriano implementation
	drivers.push_back(&fortify);

	const string endll = "\n\n";

	//Run drivers individually
	Driver* d = &game;
	cout << d->getOpeningMessage() << endll;
	d->run();
	cout << std::endl << d->getClosingMessage() << endll;

	/*
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
	*/

	cout << "Press any key to exit...";
	getchar();

	return 0;
}
