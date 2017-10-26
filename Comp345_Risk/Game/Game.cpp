// ==============================
//           COMP-345 D
//          Assignment 2
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#include "Game.h"

#include <ctime>
#include <algorithm>
#include "../Map/MapLoader/MapLoader.h"
#include <iostream>

using std::cout;


Game::Game(int numPlayers, RiskMap* map) : numPlayers(numPlayers), map(map)
{
}

Game::~Game()
{
	//Clear local information
	for (int i = 0; i < players->size(); i++)
	{
		delete players->at(i);
	}
	players->clear();

	delete players;
	players = nullptr;

	map = nullptr;
}

void Game::setup()
{
	//Original random seed, only needs to be done once in whole game execution
	srand(time(nullptr));

	//Create the vector of empty players
	players = new vector<Player*>(numPlayers);
	for (int i = 0; i < numPlayers; i++)
	{
		players->push_back(new Player("Player " + i, DiceRoller(), vector<Country>(), Hand()));
	}

	//Shuffle the order of the players
	random_shuffle(players->begin(), players->end());

	//Create a vector of countries not distributed yet
	vector<int> remaining(map->size());
	for (int i = 0; i < map->size(); i++)
	{
		remaining.push_back(i);
	}

	//Assign a remaining country to each player, one by one
	for (int i = 0; i < map->size(); i++)
	{
		//Get random member of remaining, obtain it's index value, then remove it
		int j = rand() % remaining.size();
		int index = remaining[j];
		remaining.erase(remaining.begin() + j);
		//Find the country at the given index and set it's new owner
		map->getCountry(index)->setOwner(players->at(i % numPlayers));
	}

	int armies = 40 - (numPlayers - 2) * 5;

	//Each player places the same total amount of armies
	for (int i = 0; i < armies; i++)
	{
		//Players place one army at a time in the regular play order
		for (int j = 0; j < numPlayers; j++)
		{
			players->at(j)->reinforce(1);
		}
	}
}

void Game::openingAnnouncement() const
{
	cout << "...Part 3: Game play: main game loop...\n" << std::endl;
	cout << "This game of risk will have " << numPlayers << " players, determined randomly from a choice of 2-6 players (only one human)." << std::endl;
	cout << "\nHere are all the players and what they have: " << std::endl;
	for (int i = 0; i < numPlayers; i++)
	{
		cout << std::endl;
		players->at(i)->displayInfo();
	}

	/*Already shuffled
	std::cout << "\nHere is the order of play, determined randomly: " << std::endl;
	std::cout << std::endl;
	for (unsigned int i = 0; i < orderOfPlay.size(); i++)
	{
		std::cout << (i + 1) << ": ";
		std::cout << riskPlayers[orderOfPlay[i]].getName() << std::endl;
	}
	*/
}

void Game::playGame()
{
	bool gameOver = false;
	int gameOverCount = 0;
	int winner = 0;

	cout << "\n=============== Start of Risk Game ===============\n" << std::endl;

	while (gameOver == false)
	{
		for (int i = 0; i < numPlayers; i++)
		{
			cout << "It's "; //Displays whose turn it is.
			cout << players->at(i)->getName();
			cout << "'s turn to play!\n" << std::endl;

			if (players->at(i)->getName() == "Human Player")
			{ //Human player interface. Functions will be completed in parts 4, 5 and 6
				cout << "You can now reinforce your territories!" << std::endl;
				players->at(i)->reinforce();
				cout << "\nPress Enter to Continue on to Attack phase!\n";
				std::cin.ignore();
				cout << "You can now attack!" << std::endl;
				players->at(i)->attack();
				cout << "\nPress Enter to Continue on to Fortify phase!\n";
				std::cin.ignore();
				cout << "You can now fortify your territories!" << std::endl;
				//TODO: Figure this out
				//players->at(i)->fortify();
				cout << "\nYour turn is over. Press Enter to allow your opponents to play.\n";
				cout << "-----------------------------------------------------------------";
				std::cin.ignore();
			}
			else
			{
				players->at(i)->reinforce(); //Summary of computer bot actions. Functions will be completed in parts 4, 5 and 6
				players->at(i)->attack();
				//TODO: this too
				//players->at(i)->fortify();
				cout << std::endl;
			}

			cout << "End Game Now? If yes, the program will give someone all the territories and declare him winner. (y/n) " << std::endl;
			char endGame;
			std::cin >> endGame;
			if (endGame == 'y' || endGame == 'Y')
			{ 
				//User choice: can end game manually if he wants. Program assigns a random winner by setting all other players' territories owned to 0.
				int randomWinner = rand() % numPlayers;

				cout << "Number of territories each player has left: " << std::endl; //To check for end of game. The game WILL end because program assigns a random winner by setting all other players' territories owned to 0.
				for (int j = 0; j < numPlayers; j++)
				{
					int numberOfTerritories;
					if (j == randomWinner)
					{
						numberOfTerritories = players->at(j)->controlled();
						cout << players->at(j)->getName();
						cout << ": ";
						cout << numberOfTerritories << std::endl;
					}
					else
					{
						numberOfTerritories = 0;
						cout << players->at(j)->getName();
						cout << ": ";
						cout << numberOfTerritories << std::endl;
					}
					if (numberOfTerritories == 0)
						gameOverCount++;
					else
						winner = j;
				}
			}
			else
			{
				cout << "Number of territories each player has left: " << std::endl; //To check for end of game normally, when user does NOT want to end the game early.
				for (int j = 0; j < numPlayers; j++)
				{
					int numberOfTerritories = players->at(j)->controlled();
					cout << players->at(j)->getName();
					cout << ": ";
					cout << numberOfTerritories << std::endl;

					if (numberOfTerritories == 0)
						gameOverCount++;
					else
						winner = j;
				}
			}

			if (gameOverCount == (numPlayers - 1))
			{
				cout << "---------------------------------------" << std::endl;
				cout << "     GAME OVER! Winner is ";
				cout << players->at(winner)->getName() << std::endl;
				cout << "---------------------------------------" << std::endl;
				gameOver = true;
				cout << "\n================...End of Risk Game. Press Enter to Close...=================" << std::endl;
				std::cin.ignore();
			}
			else
			{
				gameOver = false;
				gameOverCount = 0;
				cout << "\nPress Enter to Continue\n";
				std::cin.ignore();
				std::cin.ignore();
			}

			if (gameOver == true)
				break;
		}
	}
}
