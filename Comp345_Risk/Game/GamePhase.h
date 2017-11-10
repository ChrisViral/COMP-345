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

#pragma once
enum GamePhase
{
	attackPhase,
	reinforcePhase,
	fortifyPhase
};

static string gamePhaseToString(GamePhase phase)
{
	switch (phase)
	{
	case attackPhase: return "Attack phase";
	case reinforcePhase: return "Reinforce phase";
	case fortifyPhase: return "Fortify phase";
	default: ;
	}
}
