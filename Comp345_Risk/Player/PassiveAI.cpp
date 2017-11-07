#include "PassiveAI.h"
#include "../Player/Player.h"
#include <iostream>
#include <algorithm>
#include <math.h>

void PassiveAI::playTurn(Player * player)
{
	reinforce(player);
	Country* c = getFirstCountryWithExistingPath(player, weakestCountry);
	if (c != NULL)
	{
		int armies = c->getArmies() - 1;
		armies = armies / 2;
		if (armies == 0) armies = 1;
		fortify(player, *weakestCountry, *c, armies);
	}
	else
		std::cout << "There is no path that exists with the weakest country to another country that has more than 1 army, so fortify cannot be done." << std::endl;
	
}

void PassiveAI::reinforce(Player* player, bool skip)
{
	TypeOfPlayer::reinforce(player, skip);
	//Find the weakest country
	weakestCountry = player->getCountries()[0];
	for (int i = 1; i < player->getCountries().size(); i++)
	{
		if (weakestCountry->getArmies() > player->getCountries()[i]->getArmies())
		{
			weakestCountry = player->getCountries()[i];
		}
	}

	std::cout << "Weakest country " << weakestCountry->getName() << std::endl;
	std::cout << "Weakest country has " << weakestCountry->getArmies() << " armies" << std::endl;

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

	weakestCountry->addArmies(total);

	std::cout << player->getName() << " therefore has a final total of " << total << " armies to place on " << weakestCountry->getName() << std::endl;
	std::cout << "Weakest country now has " << weakestCountry->getArmies() << " armies" << std::endl;

	std::cout << "All reinforcements distributed!" << std::endl << std::endl;

}

bool PassiveAI::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	TypeOfPlayer::fortify(player, source, target, amount, skip);
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

		weakestCountry->addArmies(amount);
		target.removeArmies(amount);

		std::cout << weakestCountry->getName() << " now has " << weakestCountry->getArmies() << " armies" << std::endl;
		std::cout << target.getName() << " now has " << target.getArmies() << " armies" << std::endl;


		return true;
	}

	return false;
}

//Looks for the first country that has a path from the weakeast country and returns it so it can take its armies.
Country* PassiveAI::getFirstCountryWithExistingPath(Player* player, Country* weakestCountry)
{
	for (int i = 0; i < player->getCountries().size(); i++)
	{
		if (player->getCountries()[i]->getArmies() > 1 && player->getGame()->getMap()->isReachable(player, *weakestCountry, *player->getCountries()[i])
			&& weakestCountry->getName() != player->getCountries()[i]->getName())
		{
			return player->getCountries()[i];
		}
	}

	return NULL;
}