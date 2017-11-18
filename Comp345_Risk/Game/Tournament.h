#pragma once


#include "../Base/RiskObject.h"
#include "../Player/Player.h"

#include <vector>
#include <string>
#include <utility>

struct info
{
	std::string mapName;
	int game;
	std::string winner;
};

class Tournament : public RiskObject
{
public:
	Tournament();
	void runTournament();
	void chooseMaps();
	void chooseComputers();
	void chooseNumberOfGames();
	void chooseNumberOfTurns();
	std::vector<std::string> readFileNames();
	void displayChoices();
	void displayTable();
	std::vector<Player*>* createComps();
	
	void gameLoop();
	std::pair<bool, Player*> checkWin() const;

private:
	std::vector<std::string> computers;	
	int numberOfTurnsPerGame;
	int numberOfGames;
	std::vector<std::string> listOfMaps;
	std::vector<info> results;

	int currentTurn;
};