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

#pragma once
#include <vector>
#include "Observer.h"


class Subject
{
public:
	Subject();
	virtual ~Subject();
	virtual void registerObserver(Observer* o);
	virtual void unregisterObserver(Observer* o);
	virtual void notify();
protected:
	int observersCount() const;
private:
	std::vector<Observer*> observers;
};
