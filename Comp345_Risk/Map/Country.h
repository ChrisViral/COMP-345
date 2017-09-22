#pragma once

#include "../Base/RiskObject.h"
#include <string>

class Country : public RiskObject {
public:
	Country();
	~Country();
private:

	std::string name;
	int x;
	int y;
	
};

