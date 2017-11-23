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

#include "UIOutputDecorator.h"
#include "TextBasedUI.h"
#include "PlayerHandUI.h"
#include "ContinentControlUI.h"
#include "DominationUI.h"
#include "../../../Base/Utils.h"


UIOutputDecorator::UIOutputDecorator(Game* game)
{
	this->game = game;


	// Attempt to not hardcode it
	/*for (int decEnum = UIDecorator::DefaultUIDecorator;
		decEnum != UIDecorator::ContinentControlUIDecorator;
		decEnum++) {
		UIDecorator dec = static_cast<UIDecorator>(decEnum);

		decorators.insert(dec, )
		
	}*/


	// TODO(Steven) I didnt want to hardcode it like this, but there is not enough time to do this properly
	decorators.emplace(PlayerHandUIDecorator, new PlayerHandUI());
	decorators.emplace(ContinentControlUIDecorator, new ContinentControlUI());
	decorators.emplace(DominationUIDecorator, new DominationUI());

	// Just awful
	decoratedUI = new TextBasedUI(game);
	decoratedUI->attachDecorator(this);

	decorators[PlayerHandUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[PlayerHandUIDecorator];

	decorators[ContinentControlUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[ContinentControlUIDecorator];

	decorators[DominationUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[DominationUIDecorator];


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
	string bits = toBinary(octalFlag);
	if (bits.size() == 4) return;
	// DHC
	// See Utils::printOutputOptionFlags()


	setDecoratorEnabled(DominationUIDecorator, strBitToBool(bits.substr(0, 1)));
	setDecoratorEnabled(PlayerHandUIDecorator, strBitToBool(bits.substr(1, 1)));
	setDecoratorEnabled(ContinentControlUIDecorator, strBitToBool(bits.substr(2, 1)));
}

GameUI* UIOutputDecorator::getUi() const
{
	return decoratedUI;
}
