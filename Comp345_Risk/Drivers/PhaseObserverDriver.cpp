

#include "PhaseObserverDriver.h"
#include <iostream>
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"
#include "../Player/Human.h"
#include "../Player/AggressiveAI.h"
#include "../Player/PassiveAI.h"
#include "../Game/UI/GameUI.h"
#include "../Game/UI/TextBasedUI.h"


PhaseObserverDriver::PhaseObserverDriver()
{
}


PhaseObserverDriver::~PhaseObserverDriver()
{
}

void PhaseObserverDriver::run()
{

	//Load the basic map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);

	TypeOfPlayer* h = new Human();
	TypeOfPlayer* a = new AggressiveAI();
	TypeOfPlayer* p = new PassiveAI();

	Player* human = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), h);
	Player* aggressiveAI = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), a);
	Player* passiveAI = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(), p);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(human);
	players->push_back(aggressiveAI);
	players->push_back(passiveAI);

	//Load a game with the above info and run the setup
	Game game(players, map);
	//We want to know how this affected the players and map
	game.setup();

	// Create the ui display
	GameUI* ui = new TextBasedUI(&game);
	// Register the ui to the game
	// Everytime a game state changes, the ui will be notified
	game.registerObserver(ui);


	
	game.gameLoop();
	//human->executeStrategy();
 	//aggressiveAI->executeStrategy();
	//passiveAI->executeStrategy();
	

	//Clear memory
	delete map;
	map = nullptr;

	delete players->at(0);
	delete players->at(1);
	delete players->at(2);
	players->clear();

	delete players;
	players = nullptr;

	delete ui;
	ui = nullptr;
}


string PhaseObserverDriver::getOpeningMessage()
{
	return "Starting Phase Observer Driver";
}

string PhaseObserverDriver::getClosingMessage()
{
	return "Ending Phase Observer Driver";
}

