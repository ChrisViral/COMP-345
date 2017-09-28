#pragma once
#include <string>

class Driver
{
public:
	Driver() { }
	virtual ~Driver() = 0;
	virtual void run() = 0;
	virtual std::string getOpeningMessage() = 0;
	virtual std::string getClosingMessage() = 0;
};
