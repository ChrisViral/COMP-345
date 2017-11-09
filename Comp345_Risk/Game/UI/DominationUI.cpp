#include "DominationUI.h"
#include "../Game.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

DominationUI::DominationUI(Game* game) : GameUI(game)
{
}

DominationUI::~DominationUI()
{
}

void DominationUI::update()
{
	//Get armies info
	vector<Player*>* players = game->getPlayers();
	int count = players->size();
	vector<int> controlled(count);
	double total = static_cast<double>(game->getMap()->size());
	for (int i = 0; i < count; i++)
	{
		controlled[i] = players->at(i)->getCountries().size();
		total += controlled[i];
	}

	cout << "Owned (%)|    5    10   15   20   25   30   35   40   45   50   55   60   65   70   75   80   85   90   95   100" << endl;
	for (int i = 0; i < count; i++)
	{
		Player* p = players->at(i);
		cout << p->getName() << " |" << string(static_cast<int>((controlled[i] / total) * 100.0), '*');
	}
}
