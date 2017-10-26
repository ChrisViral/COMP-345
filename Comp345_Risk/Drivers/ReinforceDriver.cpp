#include "ReinforceDriver.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Game/Game.h"
#include "../Player/Player.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"

ReinforceDriver::ReinforceDriver()
{
}

ReinforceDriver::~ReinforceDriver()
{
}

void ReinforceDriver::run()
{
	//Setting up a Game and Map
	RiskMap* map = new RiskMap();
	MapLoader loader("mapfiles/World.map");
	loader.tryParseMap(map);
	vector<Player*>* players = new vector<Player*>();
	players->push_back(new Player("Player 1", DiceRoller(), vector<Country*>(), Hand()));
	players->push_back(new Player("Player 2", DiceRoller(), vector<Country*>(), Hand()));
	players->push_back(new Player("Player 3", DiceRoller(), vector<Country*>(), Hand()));
	Game game(players, map);
	game.setup();

	//Get a player
	Player* p = players->at(0);

	//Test 1: basic reinforce
	p->reinforce();

	//Print map and player army info
	map->printMapArmyInfo();
	p->printPlayerArmyInfo();

	//Test 2: reinforce with a whole continent being owned
	Continent continent = map->getContinents().begin()->second;
	for (Node* n : continent.getCountries())
	{
		n->country->setOwner(p);
	}

	p->reinforce();

	//Print map and player army info
	map->printMapArmyInfo();
	p->printPlayerArmyInfo();

	//Test 3: exchange cards
	p->getHand().addCard(Card(infantry));
	p->getHand().addCard(Card(cavalry));
	p->getHand().addCard(Card(artillery));

	p->reinforce();

	//Print map and player army info
	map->printMapArmyInfo();
	p->printPlayerArmyInfo();

	//Clear memory
	delete map;
	map = nullptr;

	delete players->at(0);
	delete players->at(1);
	delete players->at(2);
	players->clear();

	delete players;
	players = nullptr;
}

string ReinforceDriver::getOpeningMessage()
{
	return "Starting Reinforce driver";
}

string ReinforceDriver::getClosingMessage()
{
	return "Ending Reinforce driver";
}
