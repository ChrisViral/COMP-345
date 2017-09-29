// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include <string>

class Driver
{
public:
	Driver();
	virtual ~Driver() = 0;
	virtual void run() = 0;
	virtual std::string getOpeningMessage() = 0;
	virtual std::string getClosingMessage() = 0;
};
