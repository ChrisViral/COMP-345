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

#pragma once
#include "../Base/RiskObject.h"
#include "../Player/Player.h"
#include "../Map/RiskMap.h"
#include "../Player/Card/Deck.h"
#include "Game.h"

using std::string;
using std::vector;


class GameStart: public RiskObject
{
public:
	GameStart();
	~GameStart();
	void askForMap();
	void askForPlayers();
	vector<string> getMapNames() const { return mapNames; }
	void createPlayers();
	vector<Player*>* getPlayers() const { return players; }
	void createMap();
	RiskMap* getMap() const { return map; }
	void createDeck();
	Deck getDeck() const { return deck; }
	Game* getGame() const { return game; }
	void startGame();

private:
	int numOfPlayers;
	int mapNumber;
	vector<string> mapNames;
	string mapString;
	void readFileNames();
	RiskMap* map;
	vector<Player*>* players;
	Deck deck;
	Game* game;
};
