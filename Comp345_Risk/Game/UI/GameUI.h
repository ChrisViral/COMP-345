#pragma once
#include "../../Patterns/Observer/Observer.h"

class GameUI : public Observer 
{
public:
	virtual ~GameUI();
	virtual void update();
protected:
	GameUI();

};

