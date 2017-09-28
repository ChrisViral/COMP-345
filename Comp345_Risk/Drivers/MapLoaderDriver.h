#pragma once
#include "Driver.h"

class MapLoaderDriver
	: public Driver
{
public:
	MapLoaderDriver();
	~MapLoaderDriver();
	void run() override;
};
