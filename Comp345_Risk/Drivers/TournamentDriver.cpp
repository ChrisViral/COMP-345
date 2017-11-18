// ==============================
//           COMP-345 D
//          Assignment 3
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
	//Load the basic map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	//Player* human = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), new Human);
	//Player* aggressiveAI = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);
	//Player* passiveAI = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(), new PassiveAI);



	//Load a game with the above info and run the setup
	//Game game(players, map);
	//We want to know how this affected the players and map
	//game.setup();


	Tournament tournament;
	tournament.chooseMaps();
	tournament.chooseComputers();
	tournament.chooseNumberOfGames();
	tournament.chooseNumberOfTurns();

	tournament.displayChoices();



	//Clear memory
	delete map;
	map = nullptr;

	//delete players->at(0);
	//delete players->at(1);
	//delete players->at(2);
	//players->clear();

	//delete players;
	//players = nullptr;
}

string TournamentDriver::getOpeningMessage()
{
	return "Starting Tournament driver";
}

string TournamentDriver::getClosingMessage()
{
	return "Ending Tournament driver";
}
