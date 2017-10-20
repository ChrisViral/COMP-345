// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include <string>
using std::string;

class Driver
{
public:
	Driver();
	virtual ~Driver() = 0;
	virtual void run() = 0;
	virtual string getOpeningMessage() = 0;
	virtual string getClosingMessage() = 0;
};
