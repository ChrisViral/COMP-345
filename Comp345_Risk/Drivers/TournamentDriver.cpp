// ==============================
//           COMP-345 D
//          Assignment 4
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#include "TournamentDriver.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Game/Game.h"
#include <iostream>
#include "../Game/Tournament.h"


using std::vector;
using std::cout;
using std::endl;

TournamentDriver::TournamentDriver()
{
}

TournamentDriver::~TournamentDriver()
{
}

void TournamentDriver::run()
{
	Tournament tournament;
	tournament.chooseMaps();
	tournament.chooseComputers();
	tournament.chooseNumberOfGames();
	tournament.chooseNumberOfTurns();

	tournament.runTournament();

	tournament.displayChoices();
	tournament.displayTable();
}

string TournamentDriver::getOpeningMessage()
{
	return "Starting Tournament driver";
}

string TournamentDriver::getClosingMessage()
{
	return "Ending Tournament driver";
}
