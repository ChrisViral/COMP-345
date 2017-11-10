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

#include "Human.h"
#include <string>
#include <iostream>
#include <vector>
#include "../Map/Country.h"
#include <functional>
#include <algorithm>
#include "Card/Hand.h"
#include <cctype>
#include "../Base/Utils.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

Human::Human()
{
}

Human::~Human()
{
}

void Human::playTurn(Player* player)
{
	reinforce(player);
	attack(player);
	//TODO: Might have to modify this function a bit to select the countries inside the function, instead of being passed in.
	//Or call a function before running fortify, that returns a source and target and then pass it in.
	fortify(player);
}

void Human::reinforce(Player* player, bool skip)
{
	//Temporary override for GameLoop purpose
	if (skip)
	{
		TypeOfPlayer::reinforce(player, skip);
		return;
	}

	Game* game = player->getGame();

	int total = std::max(3, int(player->getCountries().size() / 3));
	game->logAction(player->getName() + " owns " + std::to_string(player->getCountries().size()) + " territories, therefore he can reinforce with " + std::to_string(total) + " armies.");

	std::unordered_map<string, Continent> continents = player->getGame()->getMap()->getContinents();
	for (std::pair<string, Continent> p : continents)
	{
		Continent c = p.second;
		if (c.ownedBy(player))
		{
			game->logAction(player->getName() + " owns all of " + c.getName() + " therefore he gets an extra " + std::to_string(c.getControlValue()) + " armies.");
			total += p.second.getControlValue();
		}
	}

	Exchangement exchange = player->getHand().exchange();
	if (exchange.successfullyExchanged)
	{
		game->logAction(player->getName() + " exchanged the following cards to get " + std::to_string(exchange.armies) + " armies.");

		for (Card c : exchange.cardsExchanged)
		{
			cout << cardTypeEnumToString(c.getCardType()) << endl;
		}
		total += exchange.armies;
	}

	game->logAction(player->getName() + " therefore has a final total of " + std::to_string(total) + " armies to place");


	for (int i = 0; i < total; i++)
	{
		Country* c = player->getCountries()[rand() % player->getCountries().size()];
		c->addArmies(1);
		game->logAction("Adding one army to " + c->getName());
	}

	game->logAction("All reinforcements distributed!");
	TypeOfPlayer::reinforce(player, skip);
}

void Human::attack(Player* player, bool skip)
{
	//Temporary override for GameLoop purpose. Just for testing
	if (skip)
	{
		TypeOfPlayer::attack(player, skip);
		return;
	}

	//Loops the attack phase until the user tells the program to stop.
	while (true)
	{
		Country* source = chooseAttackSourceCountry(player);
		if (source == nullptr)
		{
			cout << "There are no possible countries to attack from..." << endl;
			return;
		}
		Country* target = chooseAttackTargetCountry(player, *source);
		attack(player, *source, *target, false);

		//prompts user if they would like to attack again.
		cout << endl << "Would you like to attack another country? (Y/N): ";
		string cont;
		while (true)
		{
			getline(std::cin, cont);

			if (stringToLower(cont) == "n")
			{
				return;
			}
			if (stringToLower(cont) == "y")
			{
				break;
			}
		}
	}
	TypeOfPlayer::attack(player, skip);
}

void Human::attack(Player* player, Country& source, Country& target, bool skip)
{
	TypeOfPlayer::attack(player, skip);
	while (source.getArmies() > 1 && target.getArmies() > 0 && !skip)
	{
		int a;
		cout << "--------------------ATTACKING PLAYER------------------" << endl;
		//if the source country has 2 armies, you can only roll with one die.
		if (source.getArmies() - 1 == 1)
		{
			a = 1;
		}
		//if there are more than 3 armies on the source country you can roll with up to 3 dice.
		else if (source.getArmies() > 3)
		{
			cout << "How many Dice would you like to roll?" <<
				endl << "Enter a number between 1 and 3: ";
			std::cin >> a;
			while (a < 1 || a > 3)
			{
				cout << endl << "Invalid entry! Please enter a valid value: ";
				std::cin >> a;
			}
		}
		//if there are 3 armies you can roll with up to 2 dice.
		else if (source.getArmies() - 1 == 2)
		{
			cout << "How many Dice would you like to roll?" <<
				endl << "Enter either 1 or 2: ";
			std::cin >> a;
			while (a < 1 || a > 2)
			{
				cout << endl << "Invalid entry! Please enter a valid value: ";
				std::cin >> a;
			}
		}
		//if there is less than 2 armies, the source country doesn't have enough armies to attack, so the attack phase ends.
		else
		{
			cout << "There aren't enough armies on this country to perform an attack!" << endl
				<< "Skipping your attack phase..." << endl;
			skip = true;
		}
		if (!skip)
		{
			cout << "ATTACKING with " << a << " Dice..." << endl;
			int attackRoll = player->getDiceRoller().roll(a);


			int b;
			cout << "--------------------DEFENDING PLAYER------------------" << endl;
			//if the target country has 1 army, you can only roll with 1 die.
			if (target.getArmies() == 1)
			{
				b = 1;
			}
			//if there are 2 or more armies on the target country you can roll with up to 2 dice.
			else if (target.getArmies() >= 2)
			{
				if (dynamic_cast<Human*>((target.getOwner())->getTypeOfPlayer()))
				{
					cout << "How many Dice would you like to roll?" <<
						endl << "Enter either 1 or 2: ";
					std::cin >> b;
					while (b < 1 || b > 2)
					{
						cout << endl << "Invalid entry! Please enter a valid value: ";
						std::cin >> b;
					}
				}
				else
				{
					b = 2;
				}
			}
			cout << "DEFENDING with " << b << " Dice..." << endl;
			int defendRoll = (*(target.getOwner())).getDiceRoller().roll(b);
			int a1, a2, a3;
			//since attackRoll is a 3 digit integer, we can seperate the digits by modulo operations.
			a1 = attackRoll % 10; //takes last digit of attackRoll
			a2 = (attackRoll % 100) / 10; //middle digit
			a3 = attackRoll / 100; //first digit
			int b1, b2;
			b1 = defendRoll % 10;
			b2 = (defendRoll % 100) / 10;

			cout << "ATTACK ROLLS:\n\tRoll 1: " << a1 << "\n\tRoll 2: " << a2 << "\n\tRoll 3: " << a3 << endl
				<< "DEFENSE ROLLS:\n\tRoll 1: " << b1 << "\n\tRoll 2: " << b2 << endl;
			//START OF ROLL CHECKING

			//if b2 = zero, only one defending die was used.
			if (b2 == 0)
			{
				//if any attacking dice is greater than the defending die, remove an army from the defending country.
				if (a1 > b1 || a2 > b1 || a3 > b1)
				{
					target.removeArmies(1);
				}
				else
				{
					source.removeArmies(1);
				}
			}


			//TODO: if a1 a2 a3 are equal, the ifs will trigger multiple times.

			//otherwise the defending country is rolling 2 dice.
			else
			{
				//if b1 is the strongest defending dice...
				if (b1 >= b2)
				{
					//if a1 is the strongest attacking dice...
					if (a1 >= a2 && a1 >= a3)
					{
						//attack wins
						if (a1 > b1)
						{
							//if a2 is the second strongest attacking dice
							if (a2 >= a3)
							{
								//attack wins
								if (a2 > b2)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else
							{
								//attack wins
								if (a3 > b2)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else
						{
							//a2 is the second strongest dice.
							if (a2 >= a3)
							{
								//attack wins
								if (a2 > b2)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else
							{
								//attack wins
								if (a3 > b2)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
						}
					}
					//if a2 is the strongest attacking dice...
					else if (a2 >= a1 && a2 >= a3)
					{
						//attack wins
						if (a2 > b1)
						{
							//if a1 is the second strongest attacking dice
							if (a1 >= a3)
							{
								//attack wins
								if (a1 > b2)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else
							{
								//attack wins
								if (a3 > b2)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else
						{
							//a1 is the second strongest dice.
							if (a1 >= a3)
							{
								//attack wins
								if (a1 > b2)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else
							{
								//attack wins
								if (a3 > b2)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
						}
					}
					//if a3 is the strongest attacking dice...
					if (a3 >= a1 && a3 >= a2)
					{
						//attack wins
						if (a3 > b1)
						{
							//if a1 is the second strongest attacking dice
							if (a1 >= a2)
							{
								//attack wins
								if (a1 > b2)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a2 is the second strongest
							else
							{
								//attack wins
								if (a2 > b2)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else
						{
							//a2 is the second strongest dice.
							if (a2 >= a1)
							{
								//attack wins
								if (a2 > b2)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
							//a1 is the second strongest dice.
							else
							{
								//attack wins
								if (a1 > b2)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
						}
					}
				}

				//b2 is the stronger defending die.
				else
				{
					//if a1 is the strongest attacking dice...
					if (a1 >= a2 && a1 >= a3)
					{
						//attack wins
						if (a1 > b2)
						{
							//if a2 is the second strongest attacking dice
							if (a2 >= a3)
							{
								//attack wins
								if (a2 > b1)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else
							{
								//attack wins
								if (a3 > b1)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else
						{
							//a2 is the second strongest dice.
							if (a2 >= a3)
							{
								//attack wins
								if (a2 > b1)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else
							{
								//attack wins
								if (a3 > b1)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
						}
					}
					//if a2 is the strongest attacking dice...
					else if (a2 >= a1 && a2 >= a3)
					{
						//attack wins
						if (a2 > b2)
						{
							//if a1 is the second strongest attacking dice
							if (a1 >= a3)
							{
								//attack wins
								if (a1 > b1)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else
							{
								//attack wins
								if (a3 > b1)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else
						{
							//a1 is the second strongest dice.
							if (a1 >= a3)
							{
								//attack wins
								if (a1 > b1)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else
							{
								//attack wins
								if (a3 > b1)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
						}
					}
					//if a3 is the strongest attacking dice...
					else if (a3 >= a1 && a3 >= a2)
					{
						//attack wins
						if (a3 > b2)
						{
							//if a1 is the second strongest attacking dice
							if (a1 >= a1)
							{
								//attack wins
								if (a1 > b1)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a2 is the second strongest
							else
							{
								//attack wins
								if (a2 > b1)
								{
									target.removeArmies(2);
								}
								//defense wins
								else
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else
						{
							//a2 is the second strongest dice.
							if (a2 >= a1)
							{
								//attack wins
								if (a2 > b1)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
							//a1 is the second strongest dice.
							else
							{
								//attack wins
								if (a1 > b1)
								{
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else
								{
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0)
									{
										source.removeArmies(1);
									}
									else
									{
										source.removeArmies(2);
									}
								}
							}
						}
					}
				}
			}
			//END OF ROLL CHECKING
			cout << "SOURCE COUNTRY:\n\tName: " << source.getName() << "\tArmies: " << source.getArmies() << endl;
			cout << "TARGET COUNTRY:\n\tName: " << target.getName() << "\tArmies: " << target.getArmies() << endl;

			if (target.getArmies() > 0)
			{
				char cont;
				cout << endl << "Would you like to attack again? (Y/N): ";


				std::cin >> cont;

				cont = tolower(cont);
				if (cont == 'n')
				{
					skip = true;
				}
				else if (cont == 'y')
				{
				}
			}
		}
		//The loop will exit if:
		//the attacking country only has 1 army left
		//the target country has no armies left
		//or the player decides to end his turn (skip is true)
	}

	//if the target country has been won, take ownership.
	if (target.getArmies() <= 0)
	{
		source.getOwner()->addCountry(&target);
		target.getOwner()->removeCountry(&target);
		target.setOwner(player);
		cout << target.getName() << " has been conquered!" << endl
			<< "How many armies would you like to move to " << target.getName() << ": ";
		int armiesMoved;

		do
		{
			//std::cout << std::endl << "Invalid entry! Please enter a valid value: ";
			std::cin >> armiesMoved;
		}
		while (armiesMoved < 1 || armiesMoved > (source.getArmies() - 1));
		target.addArmies(armiesMoved);
		source.removeArmies(armiesMoved);
	}
}

void Human::fortify(Player* player)
{
	cout << "===========================================" << endl;
	while (true)
	{
		Country* source = chooseFortifySourceCountry(player);
		Country* target = chooseFortifyTargetCountry(player, *source);
		int amount;
		cout << source->getName() << " has " << source->getArmies() << " armies" << endl;
		cout << target->getName() << " has " << target->getArmies() << " armies" << endl << endl;
		cout << "How many armies would you like to move from " << source->getName() << " to " << target->getName() << ": ";
		while (true)
		{
			std::cin >> amount;
			if (amount < source->getArmies() - 1 || amount >= 0)
			{
				break;
			}
			cout << "Invalid entry, please be sure to leave at least 1 army on " << source->getName() << "...";
		}
	std:cout << "Moving " << amount << " armies from " << source->getName() << " to " << target->getName() << "..." << endl << endl;
		fortify(player, *source, *target, amount);
		cout << source->getName() << " now has " << source->getArmies() << " armies" << endl;
		cout << target->getName() << " now has " << target->getArmies() << " armies" << endl << endl;

		cout << endl << "Would you like to fortify another country? (Y/N): ";
		string cont;
		while (true)
		{
			getline(std::cin, cont);

			if (stringToLower(cont) == "n")
			{
				return;
			}
			if (stringToLower(cont) == "y")
			{
				break;
			}
		}
	}
}

bool Human::fortify(Player* player, Country& source, Country& target, int amount, bool skip)
{
	TypeOfPlayer::fortify(player, source, target, amount, skip);
	if (skip)
	{
		return true;
	}


	//std::cout << "\nPlayer can fortify a territory of his choice:" << std::endl;
	//std::cout << " -- Exact fortify() function implementation has yet to be determined! -- " << std::endl;


	// check to see if this player owns the source and target country

	if (ownsCountry(player, source) && ownsCountry(player, target))
	{
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

Country* Human::chooseAttackSourceCountry(Player* player)
{
	cout << "Countries you can attack from:" << endl;
	vector<Country*> validCountries;
	for (Country* country : player->getCountries())
	{
		if ((country->getArmies() > 1) && (hasAdjUnOwnedCountry(player, *country)))
		{
			validCountries.push_back(country);
			cout << "\tName: " << country->getName() << "\tArmies: " << country->getArmies() << endl;
		}
	}
	if (validCountries.empty())
	{
		return nullptr;
	}
	string inputCountryName;
	cout << "Which Country would you like to attack from: ";
	while (true)
	{
		getline(std::cin, inputCountryName);
		inputCountryName = stringToLower(inputCountryName);
		for (Country* country : validCountries)
		{
			if (stringToLower(country->getName()) == inputCountryName)
				return country;
		}
		cout << "Invalid Country Name, Please Try Again." << endl;
	}
}

bool Human::hasAdjUnOwnedCountry(Player* player, const Country& source)
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

bool Human::ownsCountry(Player* player, const Country& country) const
{
	return (player == country.getOwner());
}

Country* Human::chooseAttackTargetCountry(Player* player, Country& source)
{
	cout << "Countries you can attack:" << endl;
	vector<Country*> adj = getAdjUnOwnedCountryList(player, source);
	for (Country* country : adj)
	{
		if (country->getArmies() > 0)
		{
			cout << "\tName: " << country->getName() << "\tArmies: " << country->getArmies() << endl;
		}
	}
	string inputCountryName;
	cout << "Which Country would you like to attack: ";
	while (true)
	{
		getline(std::cin, inputCountryName);
		inputCountryName = stringToLower(inputCountryName);
		for (Country* country : adj)
		{
			if (stringToLower(country->getName()) == inputCountryName)
			{
				return country;
			}
		}
		cout << "Invalid Country Name, Please Try Again." << endl;
	}
}

vector<Country*> Human::getAdjUnOwnedCountryList(Player* player, const Country& source)
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

Country* Human::chooseFortifySourceCountry(Player* player)
{
	cout << "Countries you can move armies from:" << endl;
	vector<Country*> validCountries;
	for (Country* country : player->getCountries())
	{
		if ((country->getArmies() > 1) && !(getConnectedOwnedCountryList(player, *country).empty()))
		{
			validCountries.push_back(country);
			cout << "\tName: " << country->getName() << "\tArmies: " << country->getArmies() << endl;
		}
	}
	if (validCountries.empty())
	{
		return nullptr;
	}
	string inputCountryName;
	cout << "Which Country would you like to move armies from: ";
	while (true)
	{
		getline(std::cin, inputCountryName);
		inputCountryName = stringToLower(inputCountryName);
		for (Country* country : validCountries)
		{
			if (stringToLower(country->getName()) == inputCountryName)
				return country;
		}
		cout << "Invalid Country Name, Please Try Again." << endl;
	}
}

vector<Country*> Human::getConnectedOwnedCountryList(Player* player, Country& source)
{
	vector<Country*> connectedCountries;
	RiskMap& map = *player->getGame()->getMap();
	for (Country* country : player->getCountries())
	{
		if (!(country == &source))
		{
			if (map.isReachable(player, source, *country))
			{
				connectedCountries.push_back(country);
			}
		}
	}
	return connectedCountries;
}

Country* Human::chooseFortifyTargetCountry(Player* player, Country& source)
{
	cout << "Countries you can fortify:" << endl;
	vector<Country*> adj = getConnectedOwnedCountryList(player, source);
	for (Country* country : adj)
	{
		if (country->getArmies() > 0)
		{
			cout << "\tName: " << country->getName() << "\tArmies: " << country->getArmies() << endl;
		}
	}
	string inputCountryName;
	cout << "Which Country would you like to fortify: ";
	while (true)
	{
		getline(std::cin, inputCountryName);
		inputCountryName = stringToLower(inputCountryName);
		for (Country* country : adj)
		{
			if (stringToLower(country->getName()) == inputCountryName)
			{
				return country;
			}
		}
		cout << "Invalid Country Name, Please Try Again." << endl;
	}
}
