Design Notes


If you are using visual studio

Please create new folders when you know there will be a collection of classes that have similar functionality.
Don't create folders based on the assignment number.
Visual Studio has this thing called filters. Avoid filters and instead create folders.
https://msdn.microsoft.com/en-us/library/cc294731.aspx


How to Git


Please work on your own code in your own branch, when you are done with your code, 
submit a pull request, and we'll review it over as a team and merge it.

You can call the branch whatever you want, but a good rule of thumb is to call it something like firstname-what-you-are-working-on
Example:
joe-map-loading
mary-serialization


--------------------------------------------------------------------------------------

For assignment 1, some classes we'll need are


The driver file is Comp345_risk.cpp in the Comp345_Risk folder


RiskMap
	- Stores a map file as an object with connections
	- The connections are stored using a hashmap instead of using pointer to pointer connections
		this is for fast lookup and avoid depth first search runtimes
		this is subject to change and currently being worked on and thought out
MapLoader
	- Loads a map file and create a RiskMap
Continent
	- Stores continent name
	- Stores set of child countries it owns
Country
	- Stores country name
	- does not store adjacent countrys
	- Might store parent continent. Will look into this

Dice
	- Rolls a number between 1 and 6
DiceRoller
	- Composed of 3 dice objects

Player
	- A player owns a collection of countries = use std::set<Country> over vector or array
	- player owns a hand of Risk cards = Hand Object
	- A player has his own dice rolling facility object = DiceRoller Object
	- reinforce(), attack(), fortify() methods which are empty for now


Card
	- CardType as Enum {infantry, artillery, cavalry}
	- Do not create Infrantry,artillery,cavalry as seperate sub classes


Hand
	- The hand object is a collection of cards
	- has an exchange() method that allows the player to exchange cards in return for a certain number of armies

Deck
	- The deck object is composed of as many cards as there are countries in the map
	- The deck must have a draw() method that allows a player to draw a card at random from the cards remaining in the deckand place it in his hand of cards
	- composed of an equal share of infantry, artillery and cavalry cards by drawing all the cards and counting each sort drawn




A lot of this structure/layout may change will we work on it, but this is a good base to start off.









--------------------------------------------------------------------------------------
Things to note about c++


All new game classes/objects should extend from RiskObject.h

This way in the future if we need common functionality, we just add to this.
For example when we need to serialize data, we can do it through this interface


Also, while inheritance is nice, favor composition over inheritance
https://en.wikipedia.org/wiki/Composition_over_inheritance

In c++ you can do multiple inheritance, while this is nice, it might to lead to nasy problems in the future
this is called the diamond problem. We will learn this later in the semester.

Overall, use composition over inheritance.


--------------------------------------------------------------------------------------
Since in the end we need to save/load a state of the game, a lot of our objects will be serialized.

- Avoid raw pointers and dynamic memory as much as possible
most of the objects can be created on the stack. 

Lets say you needed a Player Object

Do
{
	Player p;
	p.callMethod();
	....


	// At the end of this scope, the Player object p will automatically be deleted
}


Don't
{
	Player *p = new Player();
	...

	// make sure to delete
	delete p;
	// While this works you might end up forgetting to call delete
	// This will cause a bunch of memory leaks
}


If you really need a pointer, use smart pointers
like std::shared_ptr or std::unique_ptr
Example:
{

	std::shared_ptr<Player> p;

	// At the end of this scope, the Player object p will automatically be deleted
}


--------------------------------------------------------------------------------------

Always pass objects into functions as const references unless that function will modify the object.
const reference is good for read only data, and most of the time it will be

https://isocpp.org/wiki/faq/const-correctness

3 different ways to pass parameters
void f1(std::string s);             // Pass by value // this will copy the object on pass, not very good
void f2(const std::string* sptr);   // Pass by pointer-to-const // this will pass a pointer to a parameter, this is fine, but very dangerous
void f3(const std::string& s);      // Pass by reference-to-const // this is the best way to do it


Example

{

	Player p;
	void readPlayerData(const Player& player) {
		
	}

	// if you need to modify the player object 
	void modifyPlayerData(Player& player) {
		player.name = "Joe Doe";
	}

}

--------------------------------------------------------------------------------------

Don't use "using namespace"
It pollutes the scope with a bunch of variables and functions we dont need


Do
Example {
	//always put std:: in front of it
	std::string str;
}

Dont
Example {
	using namespace std;
	string str;

	// This pollutes the scope
}

--------------------------------------------------------------------------------------

Avoid arrays, use std::vector instead
Only use arrays when you need performance. For our project we don't need it
Arrays will cause more problems in the end

Example {
	// Good. Like arraylist in java, grows dyanmically
	std::vector<std::string> listOfStrings;

	// Avoid
	// You have to manually specify the size
	std::string listOfStrings2[10];
}

--------------------------------------------------------------------------------------

Avoid pointer arithmetic unless you know what you are doing
when using stl containers such as std::vectors, there is no need for pointer arithmetic

--------------------------------------------------------------------------------------
 
 Use structs if objects don't need to have functions.
 Usually structs are good for storing data objects

--------------------------------------------------------------------------------------

