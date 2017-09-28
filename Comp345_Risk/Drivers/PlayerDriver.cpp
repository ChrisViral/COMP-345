//This is the application file PlayerDriver.cpp. This program
//demonstrates the implementation of the Player.cpp class.

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Dice.h"
#include "Territories.h"

using namespace std;

int main() {
	
	//Sample Dice, Territory and Card objects are created to demonstrate the Player object class.
	Dice playerDice;
	Territories playerTerritories("EASTERN UNITED STATES, CENTRAL AMERICA, NORTHERN EUROPE, MADAGASCAR, INDONESIA");
	Cards playersCards("MISSION CARD, TERRITORY CARD - CAVALRY, WILD CARD, TERRITORY CARD - INFANTRY");
	
	//Player is initialized and given his dice, territories and cards (in sample form)
	Player newPlayer(playerDice, playerTerritories, playersCards);

	//Player assets are displayed using function in Player class.
	newPlayer.displayInfo();

	//Player's reinforce, attack and fortify functions are shown.
	newPlayer.reinforce();
	newPlayer.attack();
	newPlayer.fortify();

	cout << "\n...Hitting Enter ends Player's turn..." << endl;
	cin.get();
	return 0;
}