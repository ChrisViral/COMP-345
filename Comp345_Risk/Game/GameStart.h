#pragma once
#include "../Base/RiskObject.h"
#include <vector>

class GameStart : public RiskObject
{
public:
	GameStart();
	void askForMap();
	void askForPlayers();
	int getNumberOfPlayers() { return numOfPlayers; }
	int getMapNumber() { return mapNumber; }
	std::vector<std::string> getMapNames() { return mapNames; }

private:
	int numOfPlayers;
	int mapNumber;
	std::vector<std::string> mapNames;
	void readFileNames();
};