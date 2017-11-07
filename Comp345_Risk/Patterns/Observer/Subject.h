#pragma once
#include <vector>
#include "Observer.h"




class Subject
{
public:
	Subject();
	~Subject();
	virtual void registerObserver(Observer* o);
	virtual void unregisterObserver(Observer* o);
	virtual void notify();
private:
	std::vector<Observer*> observers;
};

