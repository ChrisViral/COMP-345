#pragma once

#include "../Base/RiskObject.h"

class Continent : public RiskObject {
public:
	Continent();
	~Continent();
private:
	int countryCount;
};

