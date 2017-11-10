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

#include "Subject.h"


Subject::Subject()
{
}


Subject::~Subject()
{
}


void Subject::registerObserver(Observer* o)
{
	observers.push_back(o);
}

void Subject::unregisterObserver(Observer* o)
{
	auto observerIteratorIndex = find(observers.begin(), observers.end(), o);
	observers.erase(observerIteratorIndex);
}

void Subject::notify()
{
	for (auto const& observer : observers)
	{
		observer->update();
	}
}

int Subject::observersCount() const
{
	return observers.size();
}
