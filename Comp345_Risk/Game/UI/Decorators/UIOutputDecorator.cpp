#include "UIOutputDecorator.h"
#include "TextBasedUI.h"
#include "PlayerHandUI.h"
#include "ContinentControlUI.h"
#include "DominationUI.h"
#include "../../../Base/Utils.h"


UIOutputDecorator::UIOutputDecorator(Game* game) {
	this->game = game;
	
	

	// Attempt to not hardcode it
	/*for (int decEnum = UIDecorator::DefaultUIDecorator;
		decEnum != UIDecorator::ContinentControlUIDecorator;
		decEnum++) {
		UIDecorator dec = static_cast<UIDecorator>(decEnum);

		decorators.insert(dec, )
		
	}*/


	// TODO(Steven) I didnt want to hardcode it like this, but there is not enough time to do this properly
	decorators.emplace(UIDecorator::PlayerHandUIDecorator, new PlayerHandUI());
	decorators.emplace(UIDecorator::ContinentControlUIDecorator, new ContinentControlUI());
	decorators.emplace(UIDecorator::DominationUIDecorator, new DominationUI());

	// Just awful
	decoratedUI = new TextBasedUI(game);
	decoratedUI->attachDecorator(this);
	
	decorators[UIDecorator::PlayerHandUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[UIDecorator::PlayerHandUIDecorator];

	decorators[UIDecorator::ContinentControlUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[UIDecorator::ContinentControlUIDecorator];

	decorators[UIDecorator::DominationUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[UIDecorator::DominationUIDecorator];
	
	

	// The above mess is trying to do this with the map
	//GameUI* ui = new TextBasedUI(&game);
	//ui = new PlayerHandUI(ui);
	//ui = new ContinentControlUI(ui);
	//ui = new DominationUI(ui);

	

}

UIOutputDecorator::~UIOutputDecorator()
{


	for (std::unordered_map<UIDecorator, GameStatisticsDecorator*>::value_type dec : decorators)
	{
		delete dec.second;

	}

	//delete decoratedUI;
	decoratedUI = nullptr;
}

void UIOutputDecorator::setDecoratorEnabled(UIDecorator decorator, bool enabled)
{
	decorators[decorator]->enabled = enabled;
}

void UIOutputDecorator::setDecoratorFlags(int octalFlag)
{
	std::string bits = toBinary(octalFlag);
	if (bits.size() == 4) return;
	// DHC
	// See Utils::printOutputOptionFlags()
	
	
	setDecoratorEnabled(UIDecorator::DominationUIDecorator, strBitToBool(bits.substr(0, 1)));
	setDecoratorEnabled(UIDecorator::PlayerHandUIDecorator, strBitToBool(bits.substr(1, 1)));
	setDecoratorEnabled(UIDecorator::ContinentControlUIDecorator, strBitToBool(bits.substr(2, 1)));
}

GameUI* UIOutputDecorator::getUi()
{
	return decoratedUI;
}




