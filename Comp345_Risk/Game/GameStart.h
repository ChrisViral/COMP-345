#pragma once
#include "../Base/RiskObject.h"
#include <vector>
#include "../Player/Player.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Player/Card/Deck.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"
#include "../Game/GameStart.h"
#include "../Player/Card/Deck.h"
#include "../Player/DiceRoller.h"
#include "../Player/Card/Hand.h"

class GameStart: public RiskObject
{
public:
	GameStart();
	~GameStart();
	void askForMap();	
	void askForPlayers();
	std::vector<std::string> getMapNames() { return mapNames; }
	void createPlayers();
	std::vector<Player> getPlayers() { return players; }
	void createMap();
	RiskMap* getMap() { return map; }
	void createDeck();
	Deck getDeck() { return deck; }

private:
	int numOfPlayers;
	int mapNumber;
	std::vector<std::string> mapNames;
	std::string mapString;
	void readFileNames();
	RiskMap* map;
	std::vector<Player> players;
	Deck deck;
};
