#include "UIOutput.h"
#include "Game/UI/Decorators/TextBasedUI.h"
#include "Game/UI/Decorators/PlayerHandUi.h"
#include "Game/UI/Decorators/ContinentControlUi.h"
#include "Game/UI/Decorators/DominationUI.h"


UIOutput::UIOutput(Game* game) {
	this->game = game;
	
	

	// Attempt to not hardcode it
	/*for (int decEnum = UIDecorator::DefaultUIDecorator;
		decEnum != UIDecorator::ContinentControlUIDecorator;
		decEnum++) {
		UIDecorator dec = static_cast<UIDecorator>(decEnum);

		decorators.insert(dec, )
		
	}*/


	// TODO(Steven) I didnt want to hardcode it like this, but there is not enough time to do this properly
	decorators.emplace(UIDecorator::PlayerHandUIDecorator, new PlayerHandUi());
	decorators.emplace(UIDecorator::ContinentControlUIDecorator, new ContinentControlUi());
	decorators.emplace(UIDecorator::DominationUIDecorator, new DominationUI());

	// Just awful
	decoratedUI = new TextBasedUI(game);
	decorators[UIDecorator::PlayerHandUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[UIDecorator::PlayerHandUIDecorator];

	decorators[UIDecorator::ContinentControlUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[UIDecorator::ContinentControlUIDecorator];

	decorators[UIDecorator::DominationUIDecorator]->setDecoratedUI(decoratedUI);
	decoratedUI = decorators[UIDecorator::DominationUIDecorator];
	

	// The above mess is trying to do this with the map
	//GameUI* ui = new TextBasedUI(&game);
	//ui = new PlayerHandUi(ui);
	//ui = new ContinentControlUi(ui);
	//ui = new DominationUI(ui);

	

}

UIOutput::~UIOutput()
{


	for (std::unordered_map<UIDecorator, GameStatisticsDecorator*>::value_type dec : decorators)
	{
		delete dec.second;

	}

	//delete decoratedUI;
	decoratedUI = nullptr;
}

void UIOutput::setDecoratorEnabled(UIDecorator decorator, bool enabled)
{
	decorators[decorator]->enabled = enabled;
}

GameUI* UIOutput::getUi()
{
	return decoratedUI;
}




