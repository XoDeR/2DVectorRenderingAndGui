#include "Config/UserOptions.h"

UserOptions* UserOptions::Instance()
{
  static UserOptions instance; 
  return &instance;
}

UserOptions::UserOptions()
{
	std::unordered_map<GameOption, bool> gameOptionsInit =
	{
		{ GameOption::ShowGraph, false },
		{ GameOption::ShowNodeIndices, false },
		{ GameOption::ShowPathOfSelectedBot, true },
		{ GameOption::ShowTargetOfSelectedBot, false },
		{ GameOption::ShowOpponentsSensedBySelectedBot, true },
		{ GameOption::OnlyShowBotsInTargetsFOV, false },
		{ GameOption::ShowGoalsOfSelectedBot, true },
		{ GameOption::ShowGoalAppraisals, true },
		{ GameOption::ShowWeaponAppraisals, false },
		{ GameOption::SmoothPathsQuick, false },
		{ GameOption::SmoothPathsPrecise, false },
		{ GameOption::ShowBotIDs, false },
		{ GameOption::ShowBotHealth, true },
		{ GameOption::ShowScore, false },
		{ GameOption::QueueMovementCommand, false },
		{ GameOption::Paused, false },
		{ GameOption::SelectBotMode, false },
		{ GameOption::PossessedBotFireMode, false },
	};

	gameOptions = std::move(gameOptionsInit);
}
