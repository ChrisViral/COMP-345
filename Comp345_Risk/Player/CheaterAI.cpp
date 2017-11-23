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

#include "../Map/Country.h"
#include "CheaterAI.h"
#include <set>


CheaterAI::~CheaterAI()
{
}

void CheaterAI::playTurn(Player* player)
{
	reinforce(player);
	attack(player);
	fortify(player, *((player->getCountries()).front()), *((player->getCountries()).front()), 0, false);
	player->getHand().addCard(player->getGame()->getDeck()->draw());
}

void CheaterAI::reinforce(Player* player, bool skip)
{ //Temporary override for GameLoop purpose
	if (skip)
	{
		TypeOfPlayer::reinforce(player, skip);
		return;
	}

	Game* game = player->getGame();

	//******CHEATER DOUBLES ALL THE ARMIES ON ITS COUNTRIES******
	for (Country* country: player->getCountries())
	{
		game->logAction("Doubling armies on " + country->getName());
		country->addArmies(country->getArmies());
	}

	game->logAction("All reinforcements distributed!");
	TypeOfPlayer::reinforce(player, skip);
}

void CheaterAI::attack(Player* player, bool skip)
{
	Game* game = player->getGame();

	int preTotalCountries = player->getCountries().size();
	vector<Country*> targets = getTargets(player);
	for (Country* target : targets)
	{
		target->setArmies(0);
		target->setOwner(player);
		player->addCountry(target);
		game->logAction(target->getName() + " has been conquered");
	}
	redistributeArmiesToFringes(player, getFringeCountries(player), preTotalCountries);
	game->logAction("\nFinished attacking");
	TypeOfPlayer::attack(player, this);
}

bool CheaterAI::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	Game* game = player->getGame();

	if (skip)
	{
		TypeOfPlayer::fortify(player, source, target, amount, skip);
		return true;
	}

	for (Country* fringe : getFringeCountries(player))
	{
		fringe->addArmies(fringe->getArmies());
		game->logAction("Doubled armies on " + fringe->getName());
	}

	TypeOfPlayer::fortify(player, source, target, amount, skip);
	return true;
}

vector<Country*> CheaterAI::getAdjUnOwnedCountryList(Player* player, const Country& source) const
{
	vector<Country*> adjCountries;
	Node& node = player->getGame()->getMap()->getNodeFromMap(source.getName());
	vector<Edge> adj = node.adjList;
	for (Edge& e : adj)
	{
		Country* c = player->getGame()->getMap()->getCountry(e.country->getName());

		if (!ownsCountry(player, *c))
		{
			adjCountries.push_back(c);
		}
	}
	return adjCountries;
}

bool CheaterAI::hasAdjUnOwnedCountry(Player* player, const Country& source) const
{
	Node& node = player->getGame()->getMap()->getNodeFromMap(source.getName());
	vector<Edge> adj = node.adjList;
	for (Edge& e : adj)
	{
		if (!ownsCountry(player, *e.country))
		{
			return true;
		}
	}
	return false;
}

bool CheaterAI::ownsCountry(Player* player, const Country& country) const
{
	// TODO: figure out in the end if are keeping the getOwner() and a pointer to the owner in the currentPlayerTurn
	return (player == country.getOwner());

	// If we don't keep a pointer to the currentPlayerTurn owner, then use the bottom implementation

	/*
	for (const Country& c : playersTerritories)
	{
	if (c.getName() == country.getName())
	{
	return true;
	}
	}
	return false;*/
}


//Returns how many dice they should roll
int CheaterAI::defend(Country* country) const
{
	if (country->getArmies() >= 2)
		return 2;
	return 1;
}

int CheaterAI::getTotalArmies(Player* player) const
{
	int totalArmies = 0;
	for (Country* country : player->getCountries())
	{
		totalArmies += country->getArmies();
	}
	return totalArmies;
}

vector<Country*> CheaterAI::getFringeCountries(Player* player) const
{
	vector<Country*> validCountries;
	for (Country* country : player->getCountries())
	{
		if (hasAdjUnOwnedCountry(player, *country))
		{
			validCountries.push_back(country);
		}
	}
	return validCountries;
}


//redistributes the total amount of armies to maximize the armies placed on the newly conquered countries.
void CheaterAI::redistributeArmiesToFringes(Player* player, vector<Country*> fringes, int totalCountries) const
{
	int totalArmies = getTotalArmies(player);
	if (totalArmies < totalCountries)
	{
		totalArmies = totalCountries;
	}
	//fringeTotal is the number of armies to be allocated to fringe countries.
	int fringeTotal = totalArmies - (totalCountries - fringes.size());
	for (Country* country: player->getCountries())
	{
		country->setArmies(1);
	}
	for (Country* fringe: fringes)
	{
		fringe->setArmies(fringeTotal / fringes.size()); //this leaves a remainder...
	}
	if (fringes.size() > 0)
	{
		int remainder = fringeTotal - ((fringeTotal / fringes.size()) * fringes.size());
		while (remainder > 0)
		{
			for (Country* fringe : fringes)
			{
				fringe->addArmies(1);
				remainder--;
			}
		}
	}
}

//returns a vector of all countries that will be taken over during the attack phase.
vector<Country*> CheaterAI::getTargets(Player* player) const
{
	std::set<Country*> temp;
	for (const Country* source : getFringeCountries(player))
	{
		vector<Country*> adj = getAdjUnOwnedCountryList(player, *source);
		for (Country* country : adj)
		{
			temp.insert(country);
		}
	}
	vector<Country*> targets(temp.begin(), temp.end());
	return targets;
}
