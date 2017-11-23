#pragma once


#include "../Base/RiskObject.h"
#include "../Player/Player.h"

#include <vector>
#include <string>
#include <utility>

class info
{
public:
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
	vector<std::string> readFileNames();
	void displayChoices();
	void displayTable();
	vector<Player*>* createComps(Deck* deck);
	
	void gameLoop(std::string currentmap);
	std::pair<bool, Player*> checkWin(Game game) const;

private:
	vector<std::string> computers;	
	int numberOfTurnsPerGame;
	int numberOfGames;
	vector<std::string> listOfMaps;
	vector<info> results;
};