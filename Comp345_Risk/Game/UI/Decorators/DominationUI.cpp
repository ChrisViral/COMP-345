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

#include "DominationUI.h"
#include "../../../Player/Player.h"
#include <iostream>
#include "UIOutputDecorator.h"

using std::cout;
using std::endl;
using std::string;


DominationUI::~DominationUI()
{
}

int DominationUI::getDecoratorUiEnum()
{
	return DominationUIDecorator;
}

void DominationUI::update()
{
	decoratedUi->update();
	if (!enabled) return;

	cout << "------------------------------" << endl;
	cout << "Domination UI" << endl;

	//Get armies info
	vector<Player*>* players = game->getPlayers();
	int count = players->size();
	vector<int> controlled(count);
	double total = static_cast<double>(game->getMap()->size());
	for (int i = 0; i < count; i++)
	{
		controlled[i] = players->at(i)->getCountries().size();
	}

	for (int i = 0; i < count; i++)
	{
		Player* p = players->at(i);
		cout << p->getName() << " owns " << controlled[i] << " countries." << endl;
	}

	cout << endl;
	cout << "Owned (%)|    5    10   15   20   25   30   35   40   45   50   55   60   65   70   75   80   85   90   95   100" << endl;
	for (int i = 0; i < count; i++)
	{
		Player* p = players->at(i);
		cout << p->getName() << " |" << string(static_cast<int>((controlled[i] / total) * 100.0), '*') << endl;
	}
	cout << endl;

	cout << "------------------------------" << endl;
}
