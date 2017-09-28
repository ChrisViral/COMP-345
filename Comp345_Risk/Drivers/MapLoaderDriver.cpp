#include "MapLoaderDriver.h"
#include <string>

MapLoaderDriver::MapLoaderDriver() { }

MapLoaderDriver::~MapLoaderDriver() { }

std::string MapLoaderDriver::getOpeningMessage()
{
	return "Starting Map Loader driver";
}

std::string MapLoaderDriver::getClosingMessage()
{
	return "Ending Map Loader driver";
}

void MapLoaderDriver::run()
{

}