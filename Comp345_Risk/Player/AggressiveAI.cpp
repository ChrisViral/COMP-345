#include "AggressiveAI.h"
#include <iostream>
#include "../Map/Country.h"
#include "../Player/Player.h"
#include <algorithm>

int defend(Country* country);
void handleBattle(Country* strongestCountry, Country* defendingCountry, int attackerRoll, int defenderRoll);
Country* getFirstCountryWithExistingPath(Player* player, Country* strongestCountry);
bool sortAlg(int i, int j) { return (i>j); }

AggressiveAI::~AggressiveAI()
{
}

void AggressiveAI::playTurn(Player * player)
{
	reinforce(player);
	attack(player);
	Country* c = getFirstCountryWithExistingPath(player, strongestCountry);
	fortify(player, *strongestCountry, *c, c->getArmies()-1);
}

void AggressiveAI::reinforce(Player* player, bool skip)
{	
	//Temporary override for GameLoop purpose
	if (skip)
	{
		std::cout << "\nReinForce Method" << std::endl;
		return;
	}

	//Find the strongest country
	strongestCountry = player->getCountries()[0];
	for (int i = 1; i < player->getCountries().size(); i++)
	{
		if (strongestCountry->getArmies() < player->getCountries()[i]->getArmies())
		{
			strongestCountry = player->getCountries()[i];
		}
	}

	std::cout << "Strongest country " << strongestCountry->getName() << std::endl;
	std::cout << "Strongest country has " << strongestCountry->getArmies() << " armies" << std::endl;

	int total = std::max(3, int(player->getCountries().size() / 3));
	std::cout << player->getName() << " owns " << player->getCountries().size() << " territories, therefore he can reinforce with " << total << " armies." << std::endl;

	std::unordered_map<std::string, Continent> continents = player->getGame()->getMap()->getContinents();
	for (std::pair<std::string, Continent> p : continents)
	{
		Continent c = p.second;
		if (c.ownedBy(player))
		{
			std::cout << player->getName() << " owns all of " << c.getName() << " therefore he gets an extra " << c.getControlValue() << " armies." << std::endl;
			total += p.second.getControlValue();
		}
	}

	Exchangement exchange = player->getHand().exchange();
	if (exchange.successfullyExchanged)
	{
		std::cout << player->getName() << " exchanged the following cards to get " << exchange.armies << " armies." << std::endl;
		for (Card c : exchange.cardsExchanged)
		{
			std::cout << cardTypeEnumToString(c.getCardType()) << std::endl;
		}
		total += exchange.armies;
	}

	strongestCountry->addArmies(total);

	std::cout << player->getName() << " therefore has a final total of " << total << " armies to place on " << strongestCountry->getName() << std::endl;
	std::cout << "Strongest country now has " << strongestCountry->getArmies() << " armies" << std::endl;

	std::cout << "All reinforcements distributed!" << std::endl << std::endl;
}

void AggressiveAI::attack(Player* player, bool skip)
{
	vector<Country*> adjList = getAdjUnOwnedCountryList(player, *strongestCountry);
	Country* defendingCountry = adjList[0];
	adjList.erase(adjList.begin());
	
	//keep attack a untill it cannot do so anymore
	while (strongestCountry->getArmies() >= 2 && adjList.size() != 0)
	{
		std::cout << "\n" << strongestCountry->getName() << "has " << strongestCountry->getArmies() << " armies" << std::endl;
		std::cout << defendingCountry->getName() << "has " << defendingCountry->getArmies() << " armies" << std::endl;

		if (strongestCountry->getArmies() == 2)
		{
			std::cout << "Attacker is rolling 1 dice. The rolls are:" << std::endl;
			int attackerRoll = player->getDiceRoller().roll(1);
			std::cout << "Defender is rolling " << defend(defendingCountry) << " dice. The rolls are:"  << std::endl;			
			int defenderRoll = defendingCountry->getOwner()->getDiceRoller().roll(defend(defendingCountry));

			handleBattle(strongestCountry, defendingCountry, attackerRoll, defenderRoll);

			std::cout << "After the attack " << strongestCountry->getName() << " Now has " << strongestCountry->getArmies() << " armies" << std::endl;
			std::cout << "After the attack " << defendingCountry->getName() << " Now has " << defendingCountry->getArmies() << " armies" << std::endl;
		}

		else if (strongestCountry->getArmies() == 3)
		{
			std::cout << "Attacker is rolling 2 dice. The rolls are:" << std::endl;
			int attackerRoll = player->getDiceRoller().roll(2);
			std::cout << "Defender is rolling " << defend(defendingCountry) << " dice. The rolls are:" << std::endl;
			int defenderRoll = defendingCountry->getOwner()->getDiceRoller().roll(defend(defendingCountry));

			handleBattle(strongestCountry, defendingCountry, attackerRoll, defenderRoll);

			std::cout << strongestCountry->getName() << " Now has " << strongestCountry->getArmies() << " armies" << std::endl;
			std::cout << defendingCountry->getName() << " Now has " << defendingCountry->getArmies() << " armies" << std::endl;
		}

		else
		{
			std::cout << "Attacker is rolling 3 dice. The rolls are:" << std::endl;
			int attackerRoll = player->getDiceRoller().roll(3);
			std::cout << "Defender is rolling " << defend(defendingCountry) << " dice. The rolls are:" << std::endl;
			int defenderRoll = defendingCountry->getOwner()->getDiceRoller().roll(defend(defendingCountry));

			handleBattle(strongestCountry, defendingCountry, attackerRoll, defenderRoll);

			std::cout << strongestCountry->getName() << " Now has " << strongestCountry->getArmies() << " armies" << std::endl;
			std::cout << defendingCountry->getName() << " Now has " << defendingCountry->getArmies() << " armies" << std::endl;
		}

		if (defendingCountry->getArmies() <= 0)
		{
			strongestCountry->getOwner()->addCountry(defendingCountry);
			defendingCountry->getOwner()->removeCountry(defendingCountry);
			defendingCountry->setOwner(strongestCountry->getOwner());

			defendingCountry = adjList[0];
			adjList.erase(adjList.begin());
		}
	}
}

bool AggressiveAI::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	if (skip)
	{
		std::cout << "\nFortify Method" << std::endl;
		return true;
	}

	if (&target != NULL)
	{
		std::cout << "\n" << source.getName() << " currently has " << source.getArmies() << " armies" << std::endl;
		std::cout << target.getName() << " currently has " << target.getArmies() << " armies" << std::endl;
		std::cout << "Adding " << amount << " armies from " << target.getName() << " to " << source.getName() << std::endl;

		strongestCountry->addArmies(amount);
		target.removeArmies(amount);
				
		std::cout << strongestCountry->getName() << " now has " << strongestCountry->getArmies() << " armies" << std::endl;
		std::cout << target.getName() << " now has " << target.getArmies() << " armies" << std::endl;


		return true;
	}

	return false;
}

vector<Country*> AggressiveAI::getAdjUnOwnedCountryList(Player* player, const Country& source)
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

bool AggressiveAI::ownsCountry(Player* player, const Country& country) const
{

	// TODO: figure out in the end if are keeping the getOwner() and a pointer to the owner in the player
	return (player == country.getOwner());

	// If we don't keep a pointer to the player owner, then use the bottom implementation

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
int defend(Country* country)
{
	if (country->getArmies() >= 2)
		return 2;
	else
		return 1;
}

//Handles the comparing and removing of armies
void handleBattle(Country* strongestCountry, Country* defendingCountry, int attackerRoll, int defenderRoll)
{
	int a1 = attackerRoll % 10; //takes last digit of attackRoll
	int a2 = (attackerRoll % 100) / 10; //middle digit
	int a3 = attackerRoll / 100; //first digit			
	int b1 = defenderRoll % 10;
	int b2 = (defenderRoll % 100) / 10;

	std::vector<int> attackerRollList;
	std::vector<int> defenderRollList;

	attackerRollList.push_back(a1);
	attackerRollList.push_back(a2);
	attackerRollList.push_back(a3);

	defenderRollList.push_back(b1);
	defenderRollList.push_back(b2);

	std::sort(attackerRollList.begin(), attackerRollList.end(), sortAlg);
	std::sort(defenderRollList.begin(), defenderRollList.end(), sortAlg);

	while (defenderRollList.size() != 0)
	{
		int attack = attackerRollList[0];
		attackerRollList.erase(attackerRollList.begin());

		int defend = defenderRollList[0];
		defenderRollList.erase(defenderRollList.begin());

		if (defend >= attack)
			strongestCountry->removeArmies(1);
		else
			defendingCountry->removeArmies(1);
	}
}

Country* getFirstCountryWithExistingPath(Player* player, Country* strongestCountry)
{
	for (int i = 0; i < player->getCountries().size(); i++)
	{
		if (player->getCountries()[i]->getArmies() > 1 && player->getGame()->getMap()->isReachable(player, *strongestCountry, *player->getCountries()[i]))
		{
			return player->getCountries()[i];
		}
	}

	return NULL;
}
