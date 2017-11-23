// ==============================
//           COMP-345 D
//          Assignment 4
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

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
