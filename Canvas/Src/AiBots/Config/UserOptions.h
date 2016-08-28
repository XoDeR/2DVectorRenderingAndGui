#pragma once

#include <unordered_map>

enum class GameOption
{
	ShowGraph,
	ShowNodeIndices,
	ShowPathOfSelectedBot,
	ShowTargetOfSelectedBot,
	ShowOpponentsSensedBySelectedBot,
	OnlyShowBotsInTargetsFOV,
	ShowGoalsOfSelectedBot,
	ShowGoalAppraisals,
	ShowWeaponAppraisals,
	SmoothPathsQuick,
	SmoothPathsPrecise,
	ShowBotIDs,
	ShowBotHealth,
	ShowScore,
	QueueMovementCommand,
	Paused,
	SelectBotMode,
	PossessedBotFireMode,
};

// controls menu options
class UserOptions
{
private:
	UserOptions();
	UserOptions(const UserOptions&);
	UserOptions& operator=(const UserOptions&);
public:
	static UserOptions* Instance();
	std::unordered_map<GameOption, bool> gameOptions;
};