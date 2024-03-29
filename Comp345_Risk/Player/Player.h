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
#include "Card/Hand.h"
#include "DiceRoller.h"
#include "../Map/Country.h"
#include "../Game/Game.h"


class TypeOfPlayer;
class Game;
using std::vector;

class Player : public RiskObject, public Subject
{
public:
	Player();
	~Player();
	Player(DiceRoller diceRoller, vector<Country*> playersTerritories, Hand playersCards);
	Player(std::string name, DiceRoller diceRoller, vector<Country*> playersTerritories, Hand playersCards, TypeOfPlayer* typePlayer);

	//All Player's assests are displayed
	void displayInfo();

	// Return the countries that this player owns
	const vector<Country*>& getCountries() const;

	void addCountry(Country* country);
	void removeCountry(Country* country);

	std::string getName() const;
	int controlled() const;
	void setGame(Game* currentGame);
	Game* getGame() const { return game; }
	void addRandomArmy();
	DiceRoller& getDiceRoller();
	Hand& getHand();
	void printPlayerArmyInfo();
	void setStrategy(TypeOfPlayer* typePlayer);
	void executeStrategy();
	TypeOfPlayer* getTypeOfPlayer() const { return typeOfPlayer; }


	//These methods can be used for specific testing/demo purposes. But in reality executeStrategy should be used.
	void executeAttack(bool skip = false);
	void executeReinforce(bool skip = false);
	void executeFortify(Country& source, Country& target, int amount, bool skip = false);


	// Used for setting the output statistics
	int outputOctalFlag;

private:
	std::string name;
	DiceRoller diceRoller;
	vector<Country*> playersTerritories;
	Hand playersCards;
	Game* game;
	TypeOfPlayer* typeOfPlayer;
};
