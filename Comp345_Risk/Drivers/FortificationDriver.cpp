#include "FortificationDriver.h"
#include "../Player/Player.h"
#include "../Map/RiskMap.h"
#include "../Map/MapLoader/MapLoader.h"
#include "../Player/Card/Deck.h"
#include <iostream>


FortificationDriver::FortificationDriver()
{
}


FortificationDriver::~FortificationDriver()
{
}

void FortificationDriver::run()
{


	std::string mapFile = "mapfiles/World.map";
	RiskMap map;
	MapLoader mapLoader(mapFile);
	MapLoader::LoaderResults results = mapLoader.tryParseMap(&map);

	Deck d(map.size());

	// These are adjacent countries
	Country& c1 = map.getCountry("Alaska");
	Country& c2 = map.getCountry("Alberta");
	c1.addArmies(5);
	c2.addArmies(2);

	// These are not adjacent countries
	Country& c3 = map.getCountry("Quebec");
	Country& c4 = map.getCountry("Brazil");
	c3.addArmies(10);
	c4.addArmies(8);


	// They are adjacent, but not owned by the player
	Country& c5 = map.getCountry("Peru");
	Country& c6 = map.getCountry("Argentina");
	c5.addArmies(6);
	c6.addArmies(6);


	
	
	std::cout << c1.getName() << " country count: " << c1.getArmies() << std::endl;
	std::cout << c2.getName() << " country count: " << c2.getArmies() << std::endl;

	std::cout << c3.getName() << " country count: " << c3.getArmies() << std::endl;
	std::cout << c4.getName() << " country count: " << c4.getArmies() << std::endl;


	std::cout << c5.getName() << " country count: " << c5.getArmies() << std::endl;
	std::cout << c6.getName() << " country count: " << c6.getArmies() << std::endl;

	std::cout << std::endl;
	
	
	// TODO: add the countries that this player owns
	std::vector<Country*> playersTerritories;

	
	// Player is owner of
	//Alaska
	// Alberta
	//Quebec
	//Brazil
	//Peru
	playersTerritories.push_back(&c1);
	playersTerritories.push_back(&c2);
	playersTerritories.push_back(&c3);
	playersTerritories.push_back(&c4);
	playersTerritories.push_back(&c5);


	
	
	
	Hand h;

	while (!d.isEmpty())
	{
		h.addCard(d.draw());
	}

	Player p(DiceRoller(), playersTerritories, h);

	std::vector<Player*> players;
	players.push_back(&p);


	c1.setOwner(&p);
	c2.setOwner(&p);
	c3.setOwner(&p);
	c4.setOwner(&p);
	c5.setOwner(&p);

	Game game(&players, &map);
	



	// Testing to see if we can move all the armies from one to another
	// Expected outcome: false
	bool moved = p.fortify(c1, c2, 5);
	std::cout << "Trying to move 5 countries from " << c1.getName() << " to " << c2.getName() << std::endl;
	std::cout << "Expected 0" << std::endl;
	std::cout << "Result " << moved << std::endl;
	std::cout << "Reason: cannot move all of a players armies to another. must keep at least 1" << std::endl;
	std::cout << c1.getName() << " country count: " << c1.getArmies() << std::endl;
	std::cout << c2.getName() << " country count: " << c2.getArmies() << std::endl;

	std::cout << std::endl;

	// Testing to see if we can move a negative amount of armies
	// Expected outcome: false
	moved = p.fortify(c1, c2, -1);
	std::cout << "Trying to move -1 countries from " << c1.getName() << " to " << c2.getName() << std::endl;
	std::cout << "Expected 0" << std::endl;
	std::cout << "Result " << moved << std::endl;
	std::cout << "Reason: cannot move negative amount of armies" << std::endl;
	std::cout << c1.getName() << " country count: " << c1.getArmies() << std::endl;
	std::cout << c2.getName() << " country count: " << c2.getArmies() << std::endl;

	std::cout << std::endl;



	// Testing to see if we can move some amount of armies to another
	// Expected outcome: true
	moved = p.fortify(c1, c2, 4);
	std::cout << "Trying to move 4 countries from " << c1.getName() << " to " << c2.getName() << std::endl;
	std::cout << "Expected 1" << std::endl;
	std::cout << "Result " << moved << std::endl;
	std::cout << c1.getName() << " country count: " << c1.getArmies() << std::endl;
	std::cout << c2.getName() << " country count: " << c2.getArmies() << std::endl;

	std::cout << std::endl;


	// Testing to see if we can move some amount of armies to another
	// Expected outcome: false
	moved = p.fortify(c1, c2, 1);
	std::cout << "Trying to move 1 countries from " << c1.getName() << " to " << c2.getName() << std::endl;
	std::cout << "Expected 0" << std::endl;
	std::cout << "Result " << moved << std::endl;
	std::cout << "Reason: cannot move armies because we have to keep at least 1 army on a country" << std::endl;
	std::cout << c1.getName() << " country count: " << c1.getArmies() << std::endl;
	std::cout << c2.getName() << " country count: " << c2.getArmies() << std::endl;

	std::cout << std::endl;

	// Trying to move armies to a country not adjacent to another
	// Expected outcome: false
	moved = p.fortify(c3, c4, 8);
	std::cout << "Trying to move 8 countries from " << c3.getName() << " to " << c4.getName() << std::endl;
	std::cout << "Expected 0" << std::endl;
	std::cout << "Result " << moved << std::endl;
	std::cout << "Reason: countries are not adjacent to eachother" << std::endl;
	std::cout << c3.getName() << " country count: " << c3.getArmies() << std::endl;
	std::cout << c4.getName() << " country count: " << c4.getArmies() << std::endl;

	std::cout << std::endl;

	// Trying to move armies from a countries not owned by the player
	// Expected outcome: false
	moved = p.fortify(c5, c6, 2);
	std::cout << "Trying to move 2 countries from " << c5.getName() << " to " << c6.getName() << std::endl;
	std::cout << "Expected 0" << std::endl;
	std::cout << "Result " << moved << std::endl;
	std::cout << "Reason: cannot exchange armies with countries not owned by the player" << std::endl;
	std::cout << c5.getName() << " country count: " << c5.getArmies() << std::endl;
	std::cout << c6.getName() << " country count: " << c6.getArmies() << std::endl;


	std::cout << std::endl;
	

}

std::string FortificationDriver::getOpeningMessage()
{
	return "Starting Fortification driver";
}

std::string FortificationDriver::getClosingMessage()
{
	return "Ending Fortification driver";
}


