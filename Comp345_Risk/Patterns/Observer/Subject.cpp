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
	auto observerIteratorIndex = std::find(observers.begin(), observers.end(), o);
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
