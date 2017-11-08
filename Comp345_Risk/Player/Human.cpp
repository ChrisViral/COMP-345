// ==============================
//           COMP-345 D
//          Assignment 2
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

void Human::playTurn(Player * player)
{
	//reinforce(player);
	attack(player);
	//TODO: Might have to modify this function a bit to select the countries inside the function, instead of being passed in.
	//Or call a function before running fortify, that returns a source and target and then pass it in.
	//fortify(player);
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
	game->logAction(player->getName() + " owns " + std::to_string(player->getCountries().size()) + " territories, therefore he can reinforce with " + std::to_string(total) +" armies.");

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
		Country* source = chooseSourceCountry(player);
		Country* target = chooseTargetCountry(player, *source);
		attack(player, *source, *target, false);

		//prompts user if they would like to attack again.
		std::cout << std::endl << "Would you like to attack another country? (Y/N): ";
		std::string cont;
		while (true)
		{
			
			
			std::getline(std::cin, cont);

			if (stringToLower(cont) == "n")
			{
				return;
			}
			else if (stringToLower(cont) =="y") {
				break;
			}
		}
	}
	TypeOfPlayer::attack(player, skip);
}

void Human::attack(Player* player, Country&source, Country& target, bool skip)
{

	TypeOfPlayer::attack(player, skip);
	while (source.getArmies()>1 && target.getArmies() > 0 && !skip)
	{
		int a;
		std::cout << "--------------------ATTACKING PLAYER------------------" << std::endl;
		//if the source country has 2 armies, you can only roll with one die.
		if (source.getArmies() - 1 == 1)
		{
			a = 1;
		}
		//if there are more than 3 armies on the source country you can roll with up to 3 dice.
		else if (source.getArmies() > 3)
		{

			std::cout << "How many Dice would you like to roll?" <<
				std::endl << "Enter a number between 1 and 3: ";
			std::cin >> a;
			while (a < 1 || a > 3)
			{
				std::cout << std::endl << "Invalid entry! Please enter a valid value: ";
				std::cin >> a;
			}
		}
		//if there are 3 armies you can roll with up to 2 dice.
		else if (source.getArmies() - 1 == 2)
		{
			std::cout << "How many Dice would you like to roll?" <<
				std::endl << "Enter either 1 or 2: ";
			std::cin >> a;
			while (a < 1 || a > 2)
			{
				std::cout << std::endl << "Invalid entry! Please enter a valid value: ";
				std::cin >> a;
			}
		}
		//if there is less than 2 armies, the source country doesn't have enough armies to attack, so the attack phase ends.
		else
		{
			std::cout << "There aren't enough armies on this country to perform an attack!" << std::endl
				<< "Skipping your attack phase..." << std::endl;
			skip = true;
		}
		if (!skip) {
			std::cout << "ATTACKING with " << a << " Dice..." << std::endl;
			int attackRoll = player->getDiceRoller().roll(a);


			int b;
			std::cout << "--------------------DEFENDING PLAYER------------------" << std::endl;
			//if the target country has 1 army, you can only roll with 1 die.
			if (target.getArmies() == 1) {
				b = 1;
			}
			//if there are 2 or more armies on the target country you can roll with up to 2 dice.
			else if (source.getArmies() >= 2) {

				std::cout << "How many Dice would you like to roll?" <<
					std::endl << "Enter either 1 or 2: ";
				std::cin >> b;
				while (b < 1 || b > 2) {
					std::cout << std::endl << "Invalid entry! Please enter a valid value: ";
					std::cin >> b;
				}
			}
			std::cout << "DEFENDING with " << b << " Dice..." << std::endl;
			int defendRoll = (*(target.getOwner())).getDiceRoller().roll(b);
			int a1, a2, a3;
			//since attackRoll is a 3 digit integer, we can seperate the digits by modulo operations.
			a1 = attackRoll % 10; //takes last digit of attackRoll
			a2 = (attackRoll % 100) / 10; //middle digit
			a3 = attackRoll / 100; //first digit
			int b1, b2;
			b1 = defendRoll % 10;
			b2 = (defendRoll % 100) / 10;

			std::cout << "ATTACK ROLLS:\n\tRoll 1: " << a1 << "\n\tRoll 2: " << a2 << "\n\tRoll 3: " << a3 << std::endl
				<< "DEFENSE ROLLS:\n\tRoll 1: " << b1 << "\n\tRoll 2: " << b2 << std::endl;
			//START OF ROLL CHECKING

			//if b2 = zero, only one defending die was used.
			if (b2 == 0) {
				//if any attacking dice is greater than the defending die, remove an army from the defending country.
				if (a1 > b1 || a2 > b1 || a3 > b1) {
					target.removeArmies(1);
				} else {
					source.removeArmies(1);
				}
			}



			//TODO: if a1 a2 a3 are equal, the ifs will trigger multiple times.

			//otherwise the defending country is rolling 2 dice.
			else {
				//if b1 is the strongest defending dice...
				if (b1 >= b2) {
					//if a1 is the strongest attacking dice...
					if (a1 >= a2 && a1 >= a3) {
						//attack wins
						if (a1 > b1) {
							//if a2 is the second strongest attacking dice
							if (a2 >= a3) {
								//attack wins
								if (a2 > b2) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else {
								//attack wins
								if (a3 > b2) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else {
							//a2 is the second strongest dice.
							if (a2 >= a3) {
								//attack wins
								if (a2 > b2) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else {
								//attack wins
								if (a3 > b2) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
						}

					}
					//if a2 is the strongest attacking dice...
					else if (a2 >= a1 && a2 >= a3) {
						//attack wins
						if (a2 > b1) {
							//if a1 is the second strongest attacking dice
							if (a1 >= a3) {
								//attack wins
								if (a1 > b2) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else {
								//attack wins
								if (a3 > b2) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else {
							//a1 is the second strongest dice.
							if (a1 >= a3) {
								//attack wins
								if (a1 > b2) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else {
								//attack wins
								if (a3 > b2) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
						}

					}
					//if a3 is the strongest attacking dice...
					if (a3 >= a1 && a3 >= a2) {
						//attack wins
						if (a3 > b1) {
							//if a1 is the second strongest attacking dice
							if (a1 >= a2) {
								//attack wins
								if (a1 > b2) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a2 is the second strongest
							else {
								//attack wins
								if (a2 > b2) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else {
							//a2 is the second strongest dice.
							if (a2 >= a1) {
								//attack wins
								if (a2 > b2) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
							//a1 is the second strongest dice.
							else {
								//attack wins
								if (a1 > b2) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
						}

					}
				}

				//b2 is the stronger defending die.
				else {
					//if a1 is the strongest attacking dice...
					if (a1 >= a2 && a1 >= a3) {
						//attack wins
						if (a1 > b2) {
							//if a2 is the second strongest attacking dice
							if (a2 >= a3) {
								//attack wins
								if (a2 > b1) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else {
								//attack wins
								if (a3 > b1) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else {
							//a2 is the second strongest dice.
							if (a2 >= a3) {
								//attack wins
								if (a2 > b1) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else {
								//attack wins
								if (a3 > b1) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
						}

					}
					//if a2 is the strongest attacking dice...
					else if (a2 >= a1 && a2 >= a3) {
						//attack wins
						if (a2 > b2) {
							//if a1 is the second strongest attacking dice
							if (a1 >= a3) {
								//attack wins
								if (a1 > b1) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a3 is the second strongest
							else {
								//attack wins
								if (a3 > b1) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else {
							//a1 is the second strongest dice.
							if (a1 >= a3) {
								//attack wins
								if (a1 > b1) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
							//a3 is the second strongest dice.
							else {
								//attack wins
								if (a3 > b1) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a3 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
						}

					}
					//if a3 is the strongest attacking dice...
					else if (a3 >= a1 && a3 >= a2) {
						//attack wins
						if (a3 > b2) {
							//if a1 is the second strongest attacking dice
							if (a1 >= a1) {
								//attack wins
								if (a1 > b1) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
							//else a2 is the second strongest
							else {
								//attack wins
								if (a2 > b1) {
									target.removeArmies(2);
								}
								//defense wins
								else {
									target.removeArmies(1);
									source.removeArmies(1);
								}
							}
						}
						//defense wins
						else {
							//a2 is the second strongest dice.
							if (a2 >= a1) {
								//attack wins
								if (a2 > b1) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a2 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
							//a1 is the second strongest dice.
							else {
								//attack wins
								if (a1 > b1) {
									target.removeArmies(1);
									source.removeArmies(1);
								}
								//defense wins
								else {
									//make sure that a second highest dice has been rolled before losing 2 armies.
									if (a1 == 0) {
										source.removeArmies(1);
									} else {
										source.removeArmies(2);
									}
								}
							}
						}
					}
				}
			}
			//END OF ROLL CHECKING
			std::cout << "SOURCE COUNTRY:\n\tName: " << source.getName() << "\tArmies: " << source.getArmies() << std::endl;
			std::cout << "TARGET COUNTRY:\n\tName: " << target.getName() << "\tArmies: " << target.getArmies() << std::endl;

			if (target.getArmies() > 0) {

				char cont;
				std::cout << std::endl << "Would you like to attack again? (Y/N): ";
				

				std::cin >> cont;

				cont = tolower(cont);
				if (cont == 'n')
				{
					skip = true;
				}
				else if(cont == 'y') {
					continue;
				}
			}
		}
	//The loop will exit if:
		//the attacking country only has 1 army left
		//the target country has no armies left
		//or the player decides to end his turn (skip is true)
	}
	
	//if the target country has been won, take ownership.
	if (target.getArmies()<=0)
	{
		source.getOwner()->addCountry(&target);
		target.getOwner()->removeCountry(&target);
		target.setOwner(player);
		std::cout << target.getName() << " has been conquered!" << std::endl
			<< "How many armies would you like to move to " << target.getName() << ": ";
		int armiesMoved;
		
		do{
			
			//std::cout << std::endl << "Invalid entry! Please enter a valid value: ";
			std::cin >> armiesMoved;
		} while (armiesMoved < 1 || armiesMoved > (source.getArmies() - 1));
		target.addArmies(armiesMoved);
		source.removeArmies(armiesMoved);
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
	else
	{
		return false;
	}
}

Country* Human::chooseSourceCountry(Player* player)
{
	std::cout << "Countries you can attack from:" << std::endl;
	vector<Country*> validCountries;
	for (Country* country : player->getCountries())
	{
		if ((country->getArmies() > 1) && (hasAdjUnOwnedCountry(player, *country))) {
			validCountries.push_back(country);
			std::cout << "\tName: " << country->getName() << "\tArmies: " << country->getArmies() << endl;
		}
	}

	string inputCountryName;
	std::cout << "Which Country would you like to attack from: ";
	while (true)
	{

		std::getline(std::cin, inputCountryName);
		inputCountryName = stringToLower(inputCountryName);
		for (Country* country : validCountries)
		{
			if (stringToLower(country->getName()) == inputCountryName)
				return country;
		}

	}
	std::cout << "Invalid Country Name, Please Try Again." << std::endl;
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

Country* Human::chooseTargetCountry(Player* player, Country& source) {
	std::cout << "Countries you can attack:" << std::endl;
	vector<Country*> adj = getAdjUnOwnedCountryList(player, source);
	for (Country* country : adj)
	{
		if (country->getArmies() > 0) {
			std::cout << "\tName: " << country->getName() << "\tArmies: " << country->getArmies() << endl;
		}
	}
	string inputCountryName;
	std::cout << "Which Country would you like to attack: ";
	while (true)
	{


		std::getline(std::cin, inputCountryName);
		inputCountryName = stringToLower(inputCountryName);
		for (Country* country : adj)
		{
			if (stringToLower(country->getName()) == inputCountryName)
			{
				return country;
			}

		}
		std::cout << "Invalid Country Name, Please Try Again." << std::endl;
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