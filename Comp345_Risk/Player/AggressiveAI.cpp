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

#include "AggressiveAI.h"
#include "../Map/Country.h"
#include "../Player/Player.h"
#include <algorithm>
#include <sstream>


AggressiveAI::~AggressiveAI()
{
}

void AggressiveAI::playTurn(Player* player)
{
	captured = false;
	Game* game = player->getGame();
	reinforce(player);
	attack(player);
	Country* c = getFirstCountryWithExistingPath(player, strongestCountry);
	if (c != nullptr)
		fortify(player, *strongestCountry, *c, c->getArmies() - 1);
	else
	{
		game->logAction("There is no path that exists with the strongest country to another country that has more than 1 army, so fortify cannot be done.");
		fortify(player, *strongestCountry, *strongestCountry, 0, true);
	}
	if (captured)
	{
		player->getHand().addCard(player->getGame()->getDeck()->draw());
	}
}

void AggressiveAI::reinforce(Player* player, bool skip)
{
	Game* game = player->getGame();


	//Temporary override for GameLoop purpose
	if (skip)
	{
		TypeOfPlayer::attack(player, this);
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


	game->logAction("Strongest country " + strongestCountry->getName());
	game->logAction("Strongest country has " + std::to_string(strongestCountry->getArmies()) + " armies");


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

	strongestCountry->addArmies(total);

	game->logAction(player->getName() + " therefore has a final total of " + std::to_string(total) + " armies to place on " + strongestCountry->getName());
	game->logAction("Strongest country now has " + std::to_string(strongestCountry->getArmies()) + " armies");

	game->logAction("All reinforcements distributed!");
	TypeOfPlayer::reinforce(player, this);
}

void AggressiveAI::attack(Player* player, bool skip)
{
	Game* game = player->getGame();

	vector<Country*> adjList = getAdjUnOwnedCountryList(player, *strongestCountry);
	Country* defendingCountry;
	if (adjList.size() != 0)
	{
		defendingCountry = adjList[0];
		adjList.erase(adjList.begin());
	}

	//keep attack a untill it cannot do so anymore
	while (strongestCountry->getArmies() >= 2 && adjList.size() != 0)
	{
		game->logAction("\n" + strongestCountry->getName() + " has " + std::to_string(strongestCountry->getArmies()) + " armies");
		game->logAction(defendingCountry->getName() + " has " + std::to_string(defendingCountry->getArmies()) + " armies");


		if (strongestCountry->getArmies() == 2)
		{
			int attackerRoll = player->getDiceRoller().roll(1);
			game->logAction("Attacker is rolling 1 dice. The rolls are:\n" + player->getDiceRoller().getLastRoll().getOutputForNumberOfDice());


			int defenderRoll = defendingCountry->getOwner()->getDiceRoller().roll(defend(defendingCountry));
			game->logAction("Defender is rolling " + std::to_string(defend(defendingCountry)) + " dice. The rolls are:\n" + defendingCountry->getOwner()->getDiceRoller().getLastRoll().getOutputForNumberOfDice());


			handleBattle(strongestCountry, defendingCountry, attackerRoll, defenderRoll);

			game->logAction("After the attack " + strongestCountry->getName() + " Now has " + std::to_string(strongestCountry->getArmies()) + " armies");
			game->logAction("After the attack " + defendingCountry->getName() + " Now has " + std::to_string(defendingCountry->getArmies()) + " armies");
		}

		else if (strongestCountry->getArmies() == 3)
		{
			int attackerRoll = player->getDiceRoller().roll(2);
			game->logAction("Attacker is rolling 2 dice. The rolls are:\n" + player->getDiceRoller().getLastRoll().getOutputForNumberOfDice());


			int defenderRoll = defendingCountry->getOwner()->getDiceRoller().roll(defend(defendingCountry));
			game->logAction("Defender is rolling " + std::to_string(defend(defendingCountry)) + " dice. The rolls are:\n" + defendingCountry->getOwner()->getDiceRoller().getLastRoll().getOutputForNumberOfDice());


			handleBattle(strongestCountry, defendingCountry, attackerRoll, defenderRoll);

			game->logAction(strongestCountry->getName() + " Now has " + std::to_string(strongestCountry->getArmies()) + " armies");
			game->logAction(defendingCountry->getName() + " Now has " + std::to_string(defendingCountry->getArmies()) + " armies");
		}

		else
		{
			int attackerRoll = player->getDiceRoller().roll(3);

			game->logAction("Attacker is rolling 3 dice. The rolls are:\n" + player->getDiceRoller().getLastRoll().getOutputForNumberOfDice());


			int defenderRoll = defendingCountry->getOwner()->getDiceRoller().roll(defend(defendingCountry));

			game->logAction("Defender is rolling " + std::to_string(defend(defendingCountry)) + " dice. The rolls are:\n" + defendingCountry->getOwner()->getDiceRoller().getLastRoll().getOutputForNumberOfDice());


			handleBattle(strongestCountry, defendingCountry, attackerRoll, defenderRoll);

			game->logAction(strongestCountry->getName() + " Now has " + std::to_string(strongestCountry->getArmies()) + " armies");
			game->logAction(defendingCountry->getName() + " Now has " + std::to_string(defendingCountry->getArmies()) + " armies");
		}

		if (defendingCountry->getArmies() <= 0)
		{
			captured = true;
			strongestCountry->getOwner()->addCountry(defendingCountry);
			defendingCountry->getOwner()->removeCountry(defendingCountry);
			defendingCountry->setOwner(strongestCountry->getOwner());

			defendingCountry->addArmies(1);
			strongestCountry->removeArmies(1);

			if (adjList.size() != 0)
			{
				defendingCountry = adjList[0];
				adjList.erase(adjList.begin());
			}
		}
	}

	game->logAction("\nNo more countries to attack");
	TypeOfPlayer::attack(player, this);
}

bool AggressiveAI::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
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

		strongestCountry->addArmies(amount);
		target.removeArmies(amount);

		game->logAction(strongestCountry->getName() + " now has " + std::to_string(strongestCountry->getArmies()) + " armies");
		game->logAction(target.getName() + " now has " + std::to_string(target.getArmies()) + " armies");


		TypeOfPlayer::fortify(player, source, target, amount, skip);
		return true;
	}

	TypeOfPlayer::fortify(player, source, target, amount, skip);
	return false;
}

vector<Country*> AggressiveAI::getAdjUnOwnedCountryList(Player* player, const Country& source) const
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
int AggressiveAI::defend(Country* country) const
{
	if (country->getArmies() >= 2)
		return 2;
	return 1;
}

bool sortAlg(int i, int j) { return (i > j); }

//Handles the comparing and removing of armies
void AggressiveAI::handleBattle(Country* strongestCountry, Country* defendingCountry, int attackerRoll, int defenderRoll) const
{
	int a1 = attackerRoll % 10; //takes last digit of attackRoll
	int a2 = (attackerRoll % 100) / 10; //middle digit
	int a3 = attackerRoll / 100; //first digit			
	int b1 = defenderRoll % 10;
	int b2 = (defenderRoll % 100) / 10;

	vector<int> attackerRollList;
	vector<int> defenderRollList;

	if (a1 != 0) attackerRollList.push_back(a1);
	if (a2 != 0) attackerRollList.push_back(a2);
	if (a3 != 0) attackerRollList.push_back(a3);


	if (b1 != 0) defenderRollList.push_back(b1);
	if (b2 != 0) defenderRollList.push_back(b2);

	sort(attackerRollList.begin(), attackerRollList.end(), sortAlg);
	sort(defenderRollList.begin(), defenderRollList.end(), sortAlg);

	while (defenderRollList.size() != 0 && attackerRollList.size() != 0)
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

//Looks for the first country that has a path from the strongest country and returns it so it can take its armies.
Country* AggressiveAI::getFirstCountryWithExistingPath(Player* player, Country* strongestCountry) const
{
	for (int i = 0; i < player->getCountries().size(); i++)
	{
		if (player->getCountries()[i]->getArmies() > 1 && player->getGame()->getMap()->isReachable(player, *strongestCountry, *player->getCountries()[i])
			&& strongestCountry->getName() != player->getCountries()[i]->getName())
		{
			return player->getCountries()[i];
		}
	}

	return nullptr;
}
