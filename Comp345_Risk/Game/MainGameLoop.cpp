#include "MainGameLoop.h"
#include "RiskObject.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
#include <ctime>

MainGameLoop::MainGameLoop()
{

}

MainGameLoop::MainGameLoop(std::vector<Player> riskPlayerVector, std::vector<int> orderOfPlayVector)
{
	int count = 0;
	for (unsigned int i = 0; i < riskPlayerVector.size(); i++)
	{
		count = i + 1;
	}
	numOfPlayers = count;
	riskPlayers = riskPlayerVector;
	orderOfPlay = orderOfPlayVector;
}

void MainGameLoop::openingAnnouncement()
{
	std::cout << "...Part 3: Game play: main game loop...\n" << std::endl;
	std::cout << "This game of risk will have " << numOfPlayers <<
		" players, determined randomly from a choice of 2-6 players (only one human)." << std::endl;
	std::cout << "\nHere are all the players and what they have: " << std::endl;
	for (unsigned int i = 0; i < riskPlayers.size(); i++)
	{
		std::cout << std::endl;
		riskPlayers[i].displayInfo();
	}
	std::cout << "\nHere is the order of play, determined randomly: " << std::endl;
	std::cout << std::endl;
	for (unsigned int i = 0; i < orderOfPlay.size(); i++)
	{
		std::cout << (i + 1) << ": ";
		std::cout << riskPlayers[orderOfPlay[i]].getName() << std::endl;
	}
}

void MainGameLoop::playGame()
{
	bool gameOver = false;
	int gameOverCount = 0;
	int winner = 0;

	std::cout << "\n=============== Start of Risk Game ===============\n" << std::endl;

	while (gameOver == false) {
		for (unsigned int i = 0; i < orderOfPlay.size(); i++)
		{
			std::cout << "It's ";									//Displays whose turn it is.
			std::cout << riskPlayers[orderOfPlay[i]].getName();		
			std::cout << "'s turn to play!\n" << std::endl;			

			if (riskPlayers[orderOfPlay[i]].getName() == "Human Player") {					//Human player interface. Functions will be completed in parts 4, 5 and 6
				std::cout << "You can now reinforce your territories!" << std::endl;
				riskPlayers[orderOfPlay[i]].reinforce();
				std::cout << "\nPress Enter to Continue on to Attack phase!\n";
				std::cin.ignore();
				std::cout << "You can now attack!" << std::endl;
				riskPlayers[orderOfPlay[i]].attack();
				std::cout << "\nPress Enter to Continue on to Fortify phase!\n";
				std::cin.ignore();
				std::cout << "You can now fortify your territories!" << std::endl;
				riskPlayers[orderOfPlay[i]].fortify();
				std::cout << "\nYour turn is over. Press Enter to allow your opponents to play.\n";
				std::cout << "-----------------------------------------------------------------";
				std::cin.ignore();
			}
			else {
				riskPlayers[orderOfPlay[i]].reinforce();	//Summary of computer bot actions. Functions will be completed in parts 4, 5 and 6
				riskPlayers[orderOfPlay[i]].attack();
				riskPlayers[orderOfPlay[i]].fortify();
				std::cout << std::endl;
			}

			std::cout << "End Game Now? If yes, the program will give someone all the territories and declare him winner. (y/n) " << std::endl;
			char endGame;
			std::cin >> endGame;
			if (endGame == 'y' || endGame == 'Y') {			//User choice: can end game manually if he wants. Program assigns a random winner by setting all other players' territories owned to 0.

				srand(unsigned(time(0)));					//Get a random winner
				int randomWinner = rand() % numOfPlayers;

				std::cout << "Number of territories each player has left: " << std::endl;		//To check for end of game. The game WILL end because program assigns a random winner by setting all other players' territories owned to 0.
				for (int i = 0; i < numOfPlayers; i++) {
					int numberOfTerritories;
					if (i == randomWinner) {
						numberOfTerritories = riskPlayers[i].getNumberOfTerritories();
						std::cout << riskPlayers[i].getName();
						std::cout << ": ";
						std::cout << numberOfTerritories << std::endl;
					}
					else {
						numberOfTerritories = 0;
						std::cout << riskPlayers[i].getName();
						std::cout << ": ";
						std::cout << numberOfTerritories << std::endl;
					}
					if (numberOfTerritories == 0)
						gameOverCount++;
					else
						winner = i;
				}
			}
			else {
				std::cout << "Number of territories each player has left: " << std::endl;		//To check for end of game normally, when user does NOT want to end the game early.
				for (int i = 0; i < numOfPlayers; i++) {
					int numberOfTerritories;
					numberOfTerritories = riskPlayers[i].getNumberOfTerritories();
					std::cout << riskPlayers[i].getName();
					std::cout << ": ";
					std::cout << numberOfTerritories << std::endl;

					if (numberOfTerritories == 0)
						gameOverCount++;
					else
						winner = i;
				}
			}
			
			if (gameOverCount == (numOfPlayers - 1)) {
				std::cout << "---------------------------------------" << std::endl;
				std::cout << "     GAME OVER! Winner is ";
				std::cout << riskPlayers[winner].getName() << std::endl;
				std::cout << "---------------------------------------" << std::endl;
				gameOver = true;
				std::cout << "\n================...End of Risk Game. Press Enter to Close...=================" << std::endl;
				std::cin.ignore();
			}
			else {
				gameOver = false;
				gameOverCount = 0;
				std::cout << "\nPress Enter to Continue\n";
				std::cin.ignore();
				std::cin.ignore();
			}

			if (gameOver == true)
				break;
		}
	}
}

MainGameLoop::~MainGameLoop()
{
}
