#pragma once
enum GamePhase
{
	attackPhase,
	reinforcePhase,
	fortifyPhase
};

static std::string gamePhaseToString(GamePhase phase) {
	switch (phase) {
		case attackPhase: return "Attack phase";;
		case reinforcePhase: return "Reinforce phase";;
		case fortifyPhase: return "Fortify phase";;
		default: ;
	}
}

