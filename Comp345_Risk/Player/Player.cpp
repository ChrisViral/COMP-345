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

#include "Player.h"
#include <string>
#include <iostream>
#include <vector>
#include "../Map/Country.h"
#include <functional>
#include <algorithm>
#include "Card/Hand.h"
#include <cctype>

using std::vector;
using std::string;
using std::cout;
using std::endl;

Player::Player(): game(nullptr)
{
}

Player::~Player()
{
	game = nullptr;
}

Player::Player(DiceRoller aDiceRoller, vector<Country> aPlayersTerritoriesVector, Hand aPlayersCards): game(nullptr)
{
	diceRoller = aDiceRoller;
	playersTerritories = aPlayersTerritoriesVector;
	playersCards = aPlayersCards;
}

Player::Player(string name, DiceRoller diceRoller, vector<Country> playersTerritories, Hand playersCards)
	: name(name), diceRoller(diceRoller), playersTerritories(playersTerritories), playersCards(playersCards), game(nullptr)
{
}

void Player::displayInfo()
{
	cout << "Here is what the Player can access during his turn:" << endl;
	cout << "\n1- Player has a dice roller object: " << endl;
	diceRoller.showRolls();
	cout << " \n2- Player owns one or more territories, Here they are: " << endl;
	for (Country c : playersTerritories)
	{
		cout << c.getName() << endl;
	}
	cout << " \n3- Player has one or more cards in his game, Here they are: " << endl;
	playersCards.displayCards();
}

void Player::reinforce(bool skip)
{
	//Temporary override for GameLoop purpose
	if (skip)
	{
		cout << "\nReinForce Method" << endl;
		return;
	}

	int total = std::max(3, int(playersTerritories.size() / 3));
	cout << name << " owns " << playersTerritories.size() << " territories, therefore he can reinforce with " << total << " armies." << endl;

	std::unordered_map<string, Continent> continents = game->getMap()->getContinents();
	for (std::pair<string, Continent> p : continents)
	{
		Continent c = p.second;
		if (c.ownedBy(this))
		{
			cout << name << " owns all of " << c.getName() << " therefore he gets an extra " << c.getControlValue() << " armies." << endl;
			total += p.second.getControlValue();
		}
	}

	Exchangement exchange = playersCards.exchange();
	if (exchange.successfullyExchanged)
	{
		cout << name << " exchanged the following cards to get " << exchange.armies << " armies." << endl;
		for (Card c : exchange.cardsExchanged)
		{
			cout << cardTypeEnumToString(c.getCardType()) << endl;
		}
		total += exchange.armies;
	}

	cout << name << " therefore has a final total of " << total << " armies to place" << endl;

	for (int i = 0; i < total; i++)
	{
		Country c = playersTerritories[rand() % playersTerritories.size()];
		c.addArmies(1);
		cout << "Adding one army to " << c.getName() << endl;
	}

	cout << "All reinforcements distributed!" << endl << endl;

}

void Player::attack()
{
	Country source = chooseSourceCountry();
	Country target = chooseTargetCountry(source);
	attack(source, target, false);
}

void Player::attack(Country&source, Country& target, bool skip)
{
	if (skip)
	{
		cout << "\nAttack Method" << endl;
		return;
	}

	do {
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
			while (a <= 1 || a >= 3)
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

		std::cout << "ATTACKING with" << a << " Dice..." << std::endl;
		int attackRoll = diceRoller.roll(a);


		int b;
		std::cout << "--------------------DEFENDING PLAYER------------------" << std::endl;
		//if the target country has 1 army, you can only roll with 1 die.
		if (target.getArmies() == 1)
		{
			a = 1;
		}
		//if there are 2 or more armies on the target country you can roll with up to 2 dice.
		else if (source.getArmies() >= 2)
		{

			std::cout << "How many Dice would you like to roll?" <<
				std::endl << "Enter either 1 or 2: ";
			std::cin >> a;
			while (a <= 1 || a >= 2)
			{
				std::cout << std::endl << "Invalid entry! Please enter a valid value: ";
				std::cin >> a;
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
				if (a3 >= a1 && a3 >= a2)
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
		std::cout << "SOURCE COUNTRY:\n\tName: " << source.getName() << "\tArmies: " << source.getArmies() << std::endl;
		std::cout << "TARGET COUNTRY:\n\tName: " << target.getName() << "\tArmies: " << target.getArmies() << std::endl;

		std::cout << std::endl << "Would you like to attack again? (Y/N): ";
		char cont;
		std::cin >> cont;
		if(std::toupper(cont)=='N')
		{
			skip = true;
		}

	//The loop will exit if:
		//the attacking country only has 1 army left
		//the target country has no armies left
		//or the player decides to end his turn (skip is true)
	}while (source.getArmies()>1 || target.getArmies()>0 || !skip);
	
	//if the target country has been won, take ownership.
	if (target.getArmies()<=0)
	{
		target.setOwner(this);
		std::cout << target.getName() << " has been conquered!" << std::endl
			<< "How many armies would you like to move to " << target.getName() << ": ";
		int armiesMoved;
		while (armiesMoved <= 1 || armiesMoved >= (source.getArmies()-1))
		{
			std::cout << std::endl << "Invalid entry! Please enter a valid value: ";
			std::cin >> armiesMoved;
		}
		target.addArmies(armiesMoved);
		source.removeArmies(armiesMoved);
	}
}

bool Player::fortify(Country& source, Country& target, int amount, bool skip)
{
	if (skip)
	{
		cout << "\nFortify Method" << endl;
		return true;
	}


	//std::cout << "\nPlayer can fortify a territory of his choice:" << std::endl;
	//std::cout << " -- Exact fortify() function implementation has yet to be determined! -- " << std::endl;

	

	// check to see if this player owns the source and target country
	
	if (!ownsCountry(source) && !ownsCountry(target))
	{
		// TODO: implement country ownership when handing out countries to the players. right now the owners are null
		// TODO: uncomment this when countries have their owners set
		//return false;
	}

	// TODO: implement some sort of function to check if countries are adjacent to each other.
	// with the new added isReachable this could be solved, but their is no access to the riskmap from inside the player
	// Right now this is pseudo code
	//if (source is not adjacent to target) {
		//return false;
	//}
	
	
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

const vector<Country>& Player::getCountries() const
{
	return playersTerritories;
}

string Player::getName() const
{
	return name;
}

int Player::controlled() const
{
	return playersTerritories.size();
}
bool Player::ownsCountry(const Country& country) const
{

	// TODO: figure out in the end if are keeping the getOwner() and a pointer to the owner in the player
	return (this == country.getOwner());

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
class Country Player::chooseSourceCountry()
{
	std::cout << "Countries you can attack from:" << std::endl;
	for each (Country country in this->getCountries())
	{
		if ((country.getArmies() > 1) && (/*has adjacent country that is not owned*/)) {
			std::cout << "\tName: " << country.getName() << "\tArmies: " << country.getArmies() << endl;
		}
	}
	string inputCountryName;

}

Country Player::chooseTargetCountry(Country source)
{
	std::cout << "Countries you can attack:" << std::endl;
	for each (Country country in /*source.getAdjacentNotOwnedCountries()*/)
	{
		if (country.getArmies() > 0) {
			std::cout << "\tName: " << country.getName() << "\tArmies: " << country.getArmies() << endl;
		}
	}
	string inputCountryName;

}

void Player::addCountry(Country country)
{ 
	playersTerritories.push_back(country); 
}

void Player::setGame(Game* currentGame)
{
	game = currentGame;
}

void Player::addRandomArmy()
{
	playersTerritories[rand() % playersTerritories.size()].addArmies(1);
}

Hand Player::getHand() const
{
	return playersCards;
}

DiceRoller Player::getDiceRoller()
{
	return diceRoller;
}

void Player::printPlayerArmyInfo()
{
	//See how many countries they own
	cout << name << " owns " << playersTerritories.size() << " countries" << endl;

	//Count player's armies
	int armies = 0;
	for (Country c : playersTerritories)
	{
		//See what country the player owns
		cout << name << " owns " << c.getName() << " and has " << c.getArmies() << " armies stationed there" << endl;
		armies += c.getArmies();
	}

	//See total amount of armies owned by a player
	cout << name << " has a total of " << armies << " placed on the board" << endl;
	cout << "This means " << name << " has placed a total of " << (armies - playersTerritories.size()) << " armies on the board during the setup phase" << endl;
}
