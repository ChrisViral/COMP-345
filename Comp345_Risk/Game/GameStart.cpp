#include "GameStart.h"
#include <fstream>
#include <iostream>
#include <string>


GameStart::GameStart()
{
	readFileNames();
}

void GameStart::askForMap()
{
	std::cout << "Select a map from the list. Enter the map's number" << std::endl;

	//Display the map names
	for (int i = 0; i < mapNames.size(); i++)
	{
		std::cout << i + 1 << ") " << mapNames[i] << std::endl;
	}

	//Get input from the user for the map number
	std::cin >> mapNumber;

	while (mapNumber <= 0 || mapNumber > mapNames.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a valid number" << std::endl;
		std::cout << "Select a map from the list. Enter the map's number" << std::endl;

		std::cin >> mapNumber;
	}
}

void GameStart::askForPlayers()
{
	std::cout << "Enter the number of players (from 2 - 6)" << std::endl;
	std::cin >> numOfPlayers;

	//Keep looping until the enter a valid number of players
	while (numOfPlayers < 2 || numOfPlayers > 6)
	{
		std::cout << "You entered the wrong number of players. Enter between 2 - 6" << std::endl;
		std::cin >> numOfPlayers;
	}
}

//Return a vector with the file names. If you add a new map to the folder, the list.txt file needs to be updated.
void GameStart::readFileNames()
{
	//Open the file
	std::ifstream input;
	input.open("mapfiles/list.txt");

	//Push all the file names in the vector
	std::string map;
	while (getline(input, map))
	{
		mapNames.push_back(map);
	}

}