
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "DecoratedStatisticsDriver.h"
#include "../Game/Game.h"
#include "../Game/UI/GameUI.h"
#include "../Game/UI/Decorators/PlayerHandUi.h"
#include "../Player/AggressiveAI.h"
#include "../Game/UI/Decorators/DominationUI.h"
#include "../Game/UI/Decorators/ContinentControlUi.h"
#include "../UIOutput.h"
#include "../Game/UI/Decorators/TextBasedUI.h"


DecoratedStatisticsDriver::DecoratedStatisticsDriver()
{
}


DecoratedStatisticsDriver::~DecoratedStatisticsDriver()
{
}

void DecoratedStatisticsDriver::run()
{
	RiskMap map;
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(&map);

	Player* human = new Player("Player 1", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);
	Player* aggressiveAI = new Player("Player 2", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);
	Player* passiveAI = new Player("Player 3", DiceRoller(), vector<Country*>(), Hand(), new AggressiveAI);

	//Create four players at random
	vector<Player*>* players = new vector<Player*>;
	players->push_back(human);
	players->push_back(aggressiveAI);
	players->push_back(passiveAI);

	//Load a game with the above info and run the setup
	Game game(players, &map);
	//We want to know how this affected the players and map
	game.setup();

	UIOutput output(&game);

	output.setDecoratorEnabled(UIDecorator::PlayerHandUIDecorator, true);
	output.setDecoratorEnabled(UIDecorator::ContinentControlUIDecorator, true);
	output.setDecoratorEnabled(UIDecorator::DominationUIDecorator, true);

	

	//GameUI* ui = new TextBasedUI(&game);
	//ui = new PlayerHandUi(ui);
	//ui = new ContinentControlUi(ui);
	//ui = new DominationUI(ui);
	//


	GameUI* ui = output.getUi();
	
	game.registerObserver(ui);
	players->at(0)->registerObserver(ui);
	players->at(1)->registerObserver(ui);
	players->at(2)->registerObserver(ui);


	game.gameLoop();


	//Clear memory
	
	

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
