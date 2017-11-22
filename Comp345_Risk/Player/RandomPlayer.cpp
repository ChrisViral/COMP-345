#include "RandomPlayer.h"
#include <algorithm>

using std::min;
using std::max;
using std::to_string;
using std::make_pair;
using std::string;

RandomPlayer::~RandomPlayer()
{
}

void RandomPlayer::playTurn(Player* player)
{
	captured = false;
	reinforce(player);
	attack(player);
	fortify(player);

	if (captured)
	{
		//TODO: add cards to the player
	}
}

void RandomPlayer::reinforce(Player* player, bool skip)
{
	if (skip)
	{
		TypeOfPlayer::reinforce(player, this);
		return;
	}

	//Get useful stuff
	Game* game = player->getGame();
	vector<Country*> countries = player->getCountries();

	//Choose a random country to reinforce
	Country* c = countries[randomRange(countries.size())];

	game->logAction("\nThe random country chosent to reinforce is " + c->getName());
	game->logAction(c->getName() + " has " + to_string(c->getArmies()) + " armies");

	//Calculate total reinforcements
	int total = max(3, int(player->getCountries().size() / 3));
	game->logAction(player->getName() + " owns " + to_string(player->getCountries().size()) + " territories, therefore he can reinforce with " + to_string(total) + " armies.");

	//Calculate continent control values
	std::unordered_map<string, Continent> continents = player->getGame()->getMap()->getContinents();
	for (pair<string, Continent> p : continents)
	{
		Continent continent = p.second;
		if (continent.ownedBy(player))
		{
			game->logAction(player->getName() + " owns all of " + continent.getName() + " therefore he gets an extra " + to_string(continent.getControlValue()) + " armies.");

			total += p.second.getControlValue();
		}
	}

	//Try to exchange cards for armies
	Exchangement exchange = player->getHand().exchange();
	if (exchange.successfullyExchanged)
	{
		game->logAction(player->getName() + " exchanged the following cards to get " + to_string(exchange.armies) + " armies.");
		for (Card card : exchange.cardsExchanged)
		{
			game->logAction(cardTypeEnumToString(card.getCardType()));
		}
		total += exchange.armies;
	}

	//Add armiesto country
	c->addArmies(total);

	game->logAction(player->getName() + " therefore has a final total of " + to_string(total) + " armies to place on " + c->getName());
	game->logAction(c->getName() + " now has " + to_string(c->getArmies()) + " armies");

	game->logAction("All reinforcements distributed!");
	TypeOfPlayer::reinforce(player, this);
}

void RandomPlayer::attack(Player* player, bool skip)
{
	if (skip)
	{
		TypeOfPlayer::attack(player, this);
		return;
	}

	//Get some useful stuff
	Game* game = player->getGame();
	RiskMap* map = game->getMap();
	vector<Country*> owned = player->getCountries();
	vector<pair<Country*, Country*>> validCountries;

	//Loop through the owned countries
	for (Country* c : owned)
	{
		//Check if the country has enough armies to attack
		if (c->getArmies() > 1)
		{

			Node& node = map->getNodeFromMap(c->getName());
			//Loop through this countries' adjacent countries
			for (Edge& e : node.adjList)
			{
				//If the country is an enemy country, add it to the list
				if (e.country->getOwner() != player)
				{
					validCountries.push_back(make_pair(c, e.country));
				}
			}
		}
	}

	//Get target
	pair<Country*, Country*> target = validCountries[randomRange(validCountries.size())];
	game->logAction("\nAttacking " + target.second->getName() + " from " + target.first->getName());

	//Keep attacking as long as it is possible
	while (target.first->getArmies() > 1)
	{
		game->logAction(target.first->getName() + " has " + to_string(target.first->getArmies()) + " armies.");
		game->logAction(target.second->getName() + " has " + to_string(target.second->getArmies()) + " armies.");

		//Get random attack dice amount and according defend dice
		int attackDices = randomRange(1, 3);
		int defendDice = min(attackDices, min(2, target.second->getArmies()));

		//Get attack roll
		int attackerRoll = player->getDiceRoller().roll(attackDices);
		game->logAction("Attacker is rolling " + to_string(attackDices) + " dice. The rolls are:\n" + player->getDiceRoller().getLastRoll().getOutputForNumberOfDice());

		//Get defense roll
		int defenderRoll = target.second->getOwner()->getDiceRoller().roll(defendDice);
		game->logAction("Defender is rolling " + to_string(defendDice) + " dice. The rolls are:\n" + target.second->getOwner()->getDiceRoller().getLastRoll().getOutputForNumberOfDice());

		//Simulate battle
		battle(target, attackerRoll, defenderRoll);
		game->logAction("After the attack " + target.first->getName() + " Now has " + to_string(target.first->getArmies()) + " armies");
		game->logAction("After the attack " + target.second->getName() + " Now has " + to_string(target.second->getArmies()) + " armies");

		//Transfer country if needed
		if (target.second->getArmies() <= 0)
		{
			target.first->getOwner()->addCountry(target.second);
			target.second->getOwner()->removeCountry(target.second);
			target.second->setOwner(target.first->getOwner());

			target.second->addArmies(1);
			target.first->removeArmies(1);

			game->logAction(target.second->getName() + " has been overtaken by " + target.first->getName());
			captured = true;
			break;
		}
	}

	TypeOfPlayer::attack(player, this);
}

bool RandomPlayer::fortify(Player* player)
{
	//Get some useful stuff
	Game* game = player->getGame();
	RiskMap* map = game->getMap();
	vector<Country*> owned = player->getCountries();
	vector<pair<Country*, Country*>> validCountries;

	//Loop through the owned countries
	for (Country* source : owned)
	{
		//Check if the country has enough armies to attack
		if (source->getArmies() > 1)
		{
			//Loop through the owned countries again
			for (Country* target : owned)
			{
				//Find all potential targets
				if (target != source && map->isReachable(player, *source, *target))
				{
					validCountries.push_back(make_pair(source, target));
				}
			}
		}
	}

	//Get random source/target pair
	pair<Country*, Country*> p = validCountries[randomRange(validCountries.size())];
	int amount = randomRange(1, p.first->getArmies() - 1);

	//Log
	game->logAction("\n" + p.first->getName() + " currently has " + to_string(p.first->getArmies()) + " armies");
	game->logAction(p.second->getName() + " currently has " + to_string(p.second->getArmies()) + " armies");
	game->logAction("Adding " + to_string(amount) + " armies from " + p.second->getName() + " to " + p.first->getName());

	//Try to fortify
	bool success = fortify(player, *p.first, *p.second, amount);

	//Log
	game->logAction(p.first->getName() + " now has " + to_string(p.first->getArmies()) + " armies");
	game->logAction(p.second->getName() + " now has " + to_string(p.second->getArmies()) + " armies");

	//Return result
	TypeOfPlayer::fortify(player, *p.first, *p.second, amount);
	return success;
}

bool RandomPlayer::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	if (skip)
	{
		TypeOfPlayer::fortify(player, source, target, amount, skip);
		return true;
	}

	if (player == source.getOwner() && player == target.getOwner())
	{
		//Check if the country is reachable
		if (!player->getGame()->getMap()->isReachable(player, source, target))
		{
			return false;
		}

		// We can't exchange negative/more armies then we have from the source country to the target country
		// Also from the official rules, we must leave at least 1 army in the source country
		// We can't pull out all of our armies
		if (amount < 0 || amount > source.getArmies() - 1)
		{
			return false;
		}

		source.removeArmies(amount);
		target.addArmies(amount);
		return true;
	}
	return false;
}

void RandomPlayer::battle(pair<Country*, Country*> countries, int attackerRoll, int defenderRoll)
{
	int a1 = attackerRoll % 10; //takes last digit of attackRoll
	int a2 = (attackerRoll % 100) / 10; //middle digit
	int a3 = attackerRoll / 100; //first digit			
	int b1 = defenderRoll % 10;
	int b2 = (defenderRoll % 100) / 10;

	vector<int> attackerRollList;
	vector<int> defenderRollList;

	if (a1 != 0) { attackerRollList.push_back(a1); }
	if (a2 != 0) { attackerRollList.push_back(a2); }
	if (a3 != 0) { attackerRollList.push_back(a3); }

	if (b1 != 0) { defenderRollList.push_back(b1); }
	if (b2 != 0) { defenderRollList.push_back(b2); }

	auto sortAlg = [](int a, int b) { return a > b; };
	sort(attackerRollList.begin(), attackerRollList.end(), sortAlg);
	sort(defenderRollList.begin(), defenderRollList.end(), sortAlg);

	while (defenderRollList.size() != 0 && attackerRollList.size() != 0)
	{
		int attack = attackerRollList[0];
		attackerRollList.erase(attackerRollList.begin());

		int defend = defenderRollList[0];
		defenderRollList.erase(defenderRollList.begin());

		if (defend >= attack) { countries.first->removeArmies(1); }
		else { countries.second->removeArmies(1); }
	}
}
