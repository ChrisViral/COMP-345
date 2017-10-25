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

#pragma once
#include "../Base/Driver.h"

class GameStartDriver: public Driver
{
public:
	GameStartDriver();
	~GameStartDriver();
	string getOpeningMessage() override;
	string getClosingMessage() override;
	void run() override;
};
