// ==============================
//           COMP-345 D
//          Assignment 3
//  ----------------------------
//  Christophe Savard,  40017812
//  David Di Feo,       27539800
//  Paul Weber,         27057938
//  Steven Tucci,       40006014
//  Adriano Monteclavo, 40009257
// ==============================

#include "PassiveAI.h"
#include "../Player/Player.h"
#include <iostream>
#include <algorithm>
#include <math.h>

void PassiveAI::playTurn(Player* player)
{
	reinforce(player);
	Country* c = getFirstCountryWithExistingPath(player, weakestCountry);
	if (c != nullptr)
	{
		int armies = c->getArmies() - 1;
		armies = armies / 2;
		if (armies == 0) armies = 1;
		fortify(player, *weakestCountry, *c, armies);
	}
	else
		player->getGame()->logAction("There is no path that exists with the weakest country to another country that has more than 1 army, so fortify cannot be done.");
}

void PassiveAI::reinforce(Player* player, bool skip)
{
	Game* game = player->getGame();
	//Find the weakest country
	weakestCountry = player->getCountries()[0];
	for (int i = 1; i < player->getCountries().size(); i++)
	{
		if (weakestCountry->getArmies() > player->getCountries()[i]->getArmies())
		{
			weakestCountry = player->getCountries()[i];
		}
	}


	game->logAction("Weakest country " + weakestCountry->getName());
	game->logAction("Weakest country has " + std::to_string(weakestCountry->getArmies()) + " armies");


	int total = std::max(3, int(player->getCountries().size() / 3));
	game->logAction(player->getName() + " owns " + std::to_string(player->getCountries().size()) + " territories, therefore he can reinforce with " + std::to_string(total) + " armies.");


	std::unordered_map<std::string, Continent> continents = player->getGame()->getMap()->getContinents();
	for (std::pair<std::string, Continent> p : continents)
	{
		Continent c = p.second;
		if (c.ownedBy(player))
		{
			game->logAction(player->getName() + " owns all of " + c.getName() + " therefore he gets an extra " + std::to_string(c.getControlValue()) + " armies.");

			total += p.second.getControlValue();
		}
	}

	Exchangement exchange = player->getHand().exchangeAll();
	if (exchange.successfullyExchanged)
	{
		game->logAction(player->getName() + " exchanged the following cards to get " + std::to_string(exchange.armies) + " armies.");
		for (Card c : exchange.cardsExchanged)
		{
			game->logAction(cardTypeEnumToString(c.getCardType()));
		}
		total += exchange.armies;
	}

	weakestCountry->addArmies(total);

	game->logAction(player->getName() + " therefore has a final total of " + std::to_string(total) + " armies to place on " + weakestCountry->getName());
	game->logAction("Weakest country now has " + std::to_string(weakestCountry->getArmies()) + " armies");

	game->logAction("All reinforcements distributed!\n");

	TypeOfPlayer::reinforce(player, skip);
}

bool PassiveAI::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	Game* game = player->getGame();

	if (skip)
	{
		TypeOfPlayer::fortify(player, source, target, amount, skip);
		return true;
	}

	if (&target != nullptr)
	{
		game->logAction("\n" + source.getName() + " currently has " + std::to_string(source.getArmies()) + " armies");
		game->logAction(target.getName() + " currently has " + std::to_string(target.getArmies()) + " armies");
		game->logAction("Adding " + std::to_string(amount) + " armies from " + target.getName() + " to " + source.getName());

		weakestCountry->addArmies(amount);
		target.removeArmies(amount);

		game->logAction(weakestCountry->getName() + " now has " + std::to_string(weakestCountry->getArmies()) + " armies");
		game->logAction(target.getName() + " now has " + std::to_string(target.getArmies()) + " armies");

		TypeOfPlayer::fortify(player, source, target, amount, skip);
		return true;
	}

	TypeOfPlayer::fortify(player, source, target, amount, skip);
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

	return nullptr;
}
