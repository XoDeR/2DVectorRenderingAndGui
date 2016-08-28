#pragma once

enum class InputEventType
{
	GAME_LOAD,
	GAME_ADDBOT,
	GAME_REMOVEBOT,

	// for posessed bot
	BOT_SELECT_BLASTER,
	BOT_SELECT_SHOTGUN,
	BOT_SELECT_ROCKET_LAUNCHER,
	BOT_SELECT_RAIL_GUN,
	BOT_RELEASE,
};
