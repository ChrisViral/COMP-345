#include "Tournament.h"
#include <fstream>
#include <iostream>
#include "../Player/AggressiveAI.h"
#include "../Player/PassiveAI.h"
#include "../Map/MapLoader/MapLoader.h"


Tournament::Tournament()
{
	
}

void Tournament::chooseMaps()
{
	std::vector<std::string> fileNames = readFileNames();

	std::string choice;

	do
	{
		std::cout << "Choose a map" << std::endl;

		//Display the map names
		for (int i = 0; i < fileNames.size(); i++)
		{
			std::cout << i + 1 << ") " << fileNames[i] << std::endl;
		}

		//Get input from the user for the map number
		int mapNumber;
		std::cin >> mapNumber;

		while (mapNumber <= 0 || mapNumber > fileNames.size() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Please enter a valid number" << std::endl;
			std::cout << "Select a map from the list. Enter the map's number" << std::endl;

			std::cin >> mapNumber;
		}

		listOfMaps.push_back(fileNames[mapNumber - 1]);
		fileNames.erase(fileNames.begin() + mapNumber - 1);

		if (fileNames.size() != 0)
		{
			std::cout << "\n\nDo you want to choose another map (Y or N)" << std::endl;
			std::cin >> choice;
		}		

	} while (choice != "N" && choice != "n" && fileNames.size() != 0);
}

void Tournament::chooseComputers()
{
	std::vector<std::string> listOfAi;
	listOfAi.push_back("Aggressive");
	listOfAi.push_back("Random");
	listOfAi.push_back("Cheater");
	listOfAi.push_back("Passive");

	std::string choice;

	do
	{
		std::cout << "Choose a computer:" << std::endl;

		//Display the ai names
		for (int i = 0; i < listOfAi.size(); i++)
		{
			std::cout << i + 1 << ") " << listOfAi[i] << std::endl;
		}

		//Get input from the user for the map number
		int aiNumber;
		std::cin >> aiNumber;

		while (aiNumber <= 0 || aiNumber > listOfAi.size() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Please enter a valid number" << std::endl;
			std::cout << "Select an ai from the list. Enter the ai's number" << std::endl;

			std::cin >> aiNumber;
		}

		if(listOfAi[aiNumber-1] == "Aggressive")
			computers.push_back("Aggressive");
		else if(listOfAi[aiNumber - 1] == "Passive")
			computers.push_back("Passive");
		//else if(listOfAi[aiNumber - 1] == "Random")
		//	computers.push_back("Random");
		//else if(listOfAi[aiNumber - 1] == "Cheater")
		//	computers.push_back("Cheater");

		listOfAi.erase(listOfAi.begin() + aiNumber - 1);

		if (listOfAi.size() != 0)
		{
			std::cout << "\n\nDo you want to choose another computer (Y or N)" << std::endl;
			std::cin >> choice;
		}

	} while ((choice != "N" && choice != "n" && listOfAi.size() != 0) || computers.size() < 2);

}

void Tournament::chooseNumberOfGames()
{
	std::cout << "Choose number of games to be played on each map (1-5)" << std::endl;

	int choice;
	std::cin >> choice;

	while (choice <= 0 || choice > 5 || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a valid number" << std::endl;

		std::cin >> choice;
	}

	numberOfGames = choice;
}

void Tournament::chooseNumberOfTurns()
{
	std::cout << "Choose number of turns to be played on each map (10-50)" << std::endl;

	int choice;
	std::cin >> choice;

	while (choice < 10 || choice > 50 || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a valid number" << std::endl;

		std::cin >> choice;
	}

	numberOfTurnsPerGame = choice;
}

void Tournament::displayChoices()
{
	std::cout << std::endl;
	std::cout << std::endl;

	std::string maps = listOfMaps[0];
	for (int i = 1; i < listOfMaps.size(); i++)
	{
		maps += ", " + listOfMaps[i];
	}

	std::string comps = computers[0];
	for (int i = 1; i < computers.size(); i++)
	{
		comps += ", " + computers[i];
	}



	std::cout << "M: " << maps << std::endl;
	std::cout << "P: " << comps << std::endl;
	std::cout << "G: " << numberOfGames << std::endl;
	std::cout << "D: " << numberOfTurnsPerGame << std::endl;


}

void Tournament::displayTable()
{
	for (int i = 0; i < results.size(); i++)
	{
		info info = results[i];
		std::cout << "Map name: " << info.mapName << "  Game: " << info.game << "  Winner: " << info.winner << std::endl;
	}
}

//Return a vector with the file names. If you add a new map to the folder, the list.txt file needs to be updated.
std::vector<std::string> Tournament::readFileNames()
{
	std::vector<std::string> mapNames;

	//Open the file
	std::ifstream input;
	input.open("mapfiles/list.txt");

	//Push all the file names in the vector
	std::string map;
	while (getline(input, map))
	{
		mapNames.push_back(map);
	}

	return mapNames;
}

std::vector<Player*>* Tournament::createComps()
{
	std::vector<Player*>* c = new std::vector<Player*>;

	for (int i = 0; i < computers.size(); i++)
	{
		if (computers[i] == "Aggressive")
			c->push_back(new Player("Aggressive", DiceRoller(), std::vector<Country*>(), Hand(), new AggressiveAI()));
		else if(computers[i] == "Passive")
			c->push_back(new Player("Passive", DiceRoller(), std::vector<Country*>(), Hand(), new PassiveAI()));
		//else if (computers[i] == "Random")
		//	c->push_back(new Player("Random", DiceRoller(), std::vector<Country*>(), Hand(), new RandomAI()));
		//else if (computers[i] == "Cheater")
		//	c->push_back(new Player("Cheater", DiceRoller(), std::vector<Country*>(), Hand(), new CheaterAI()));
	}

	return c;
}

void Tournament::runTournament()
{
	std::vector<std::string> list = listOfMaps;

	do
	{		
		std::string currentmap = list[0];
		list.erase(list.begin() );

		RiskMap* map = new RiskMap();
		MapLoader loader("mapfiles/" + currentmap + ".map");
		loader.tryParseMap(map);

		std::vector<Player*>* comps = createComps();

		Game game(comps, map);

		game.setup();
		
		gameLoop(currentmap, game);

		delete map;
		delete comps;
		
		for (int i = 0; i < comps->size(); i++)
		{
			delete comps->at(i);
		}
		

	} while (list.size() != 0);
}

void Tournament::gameLoop(std::string mapName, Game game)
{
	int currentTurn = 1;
	int gameNumber = 1;
		
	while (gameNumber <= numberOfGames)
	{
		std::cout << "\n*** Map: " << mapName << " Game: " << gameNumber << " ***\n" << std::endl;

		std::pair<bool, Player*> pair = checkWin(game);
		while (pair.first == false && currentTurn <= numberOfTurnsPerGame)
		{
			std::cout << "\n*** Current Turn: " << currentTurn << " ***\n"<< std::endl;

			for (int i = 0; i < game.getPlayers()->size(); i++)
			{
				std::cout << "\n" << (*game.getPlayers())[i]->getName() << " turn"  << std::endl;
				(*game.getPlayers())[i]->executeStrategy();
			}

			pair = checkWin(game);
			currentTurn++;
		}
		
		info info;
		info.mapName = mapName;
		info.game = gameNumber;
		if (pair.second == NULL)
			info.winner = "Draw";
		else
			info.winner = pair.second->getName();

		results.push_back(info);

		gameNumber++;
	}	
}


std::pair<bool, Player*> Tournament::checkWin(Game game) const
{
	for (int i = 0; i < game.getPlayers()->size(); i++)
	{
		if (game.getPlayers()->at(i)->getCountries().size() == game.getMap()->size())
		{
			return std::pair<bool, Player*>(true, game.getPlayers()->at(i));
		}
	}

	return std::pair<bool, Player*>(false, nullptr);
}