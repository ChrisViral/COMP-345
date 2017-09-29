// COMP-345
// Assignment #1
// Christophe Savard
// David Di Feo
// Paul Weber
// Steven Tucci
// Adriano Monteclavo

#pragma once
#include "Driver.h"

class MapLoaderDriver : public Driver
{
public:
	MapLoaderDriver();
	~MapLoaderDriver();
	std::string getOpeningMessage() override;
	std::string getClosingMessage() override;
	void run() override;
private:
	static void loadMap(const std::string path);
};
