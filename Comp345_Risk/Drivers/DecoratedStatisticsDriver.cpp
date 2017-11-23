#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "DecoratedStatisticsDriver.h"
#include "../Game/Game.h"
#include "../Game/UI/GameUI.h"
#include "../Player/AggressiveAI.h"
#include "../Game/UI/Decorators/UIOutputDecorator.h"
#include "../Player/Human.h"
#include <iostream>


DecoratedStatisticsDriver::DecoratedStatisticsDriver()
{
}


DecoratedStatisticsDriver::~DecoratedStatisticsDriver()
{
}




void DecoratedStatisticsDriver::run()
{
	RiskMap* map = new RiskMap();;
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);
	Deck* deck = new Deck(map->size());

	Player* human = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), new Human);
	Player* aggressiveAI = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);
	Player* passiveAI = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(human);
	players->push_back(aggressiveAI);
	players->push_back(passiveAI);

	//Load a game with the above info and run the setup
	Game game(players, map, deck);
	//We want to know how this affected the players and map
	game.setup();


	UIOutputDecorator output(&game);
	

	output.setDecoratorEnabled(UIDecorator::PlayerHandUIDecorator, false);
	output.setDecoratorEnabled(UIDecorator::ContinentControlUIDecorator, false);
	output.setDecoratorEnabled(UIDecorator::DominationUIDecorator, false);



	GameUI* ui = output.getUi();
	
	game.registerObserver(ui);
	players->at(0)->registerObserver(ui);
	players->at(1)->registerObserver(ui);
	players->at(2)->registerObserver(ui);


	game.gameLoop();


	//Clear memory
	
	delete map;
	map = nullptr;
	delete deck;
	deck = nullptr;

	delete players->at(0);
	delete players->at(1);
	delete players->at(2);
	players->clear();

	delete players;
	players = nullptr;

	
	
	

	




}

std::string DecoratedStatisticsDriver::getOpeningMessage()
{
	return "Starting Decorated Statistics Driver";
}

std::string DecoratedStatisticsDriver::getClosingMessage()
{
	return "Ending Decorated Statistics Driver";
}
