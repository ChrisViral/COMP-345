#pragma once
#include "../Player/Card/Hand.h"
#include "Driver.h"

class CardDriver : public Driver
{
public:
	CardDriver();
	~CardDriver();
	void run() override;
	static void printExchangement(Exchangement& ex);
};



