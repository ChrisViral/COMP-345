#include "ContinentControlUi.h"
#include <iostream>


void ContinentControlUi::update()
{
	decoratedUi->update();
	if (!enabled) return;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Continent Control UI" << std::endl;
	// TODO: custom decoration output for the continent control
	std::cout << "------------------------------" << std::endl;
}

int ContinentControlUi::getDecoratorUiEnum()
{
	return UIDecorator::ContinentControlUIDecorator;
}

ContinentControlUi::~ContinentControlUi()
{
}

