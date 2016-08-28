#include "InputSystem.h"
#include <ocornut-imgui/imgui.h>
#include "Config/UserOptions.h"

InputSystem::InputSystem()
{

}

void InputSystem::processLocationSelected(int32_t x, int32_t y)
{
	// TODO process location selection
}

void InputSystem::processGui()
{
	// Menu
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Game"))
		{
			if (ImGui::Button("Load Map")) processInputEvent(InputEventType::GAME_LOAD);
			if (ImGui::Button("Add Bot [ csr up ]")) processInputEvent(InputEventType::GAME_ADDBOT);
			if (ImGui::Button("Remove Bot [ csr down ]")) processInputEvent(InputEventType::GAME_REMOVEBOT);
			ImGui::Checkbox("Toggle Pause [ 'P' ]", &UserOptions::Instance()->gameOptions[GameOption::Paused]);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Navigation"))
		{
			ImGui::Checkbox("Show NavGraph", &UserOptions::Instance()->gameOptions[GameOption::ShowGraph]);
			ImGui::Checkbox("Show Node Indices", &UserOptions::Instance()->gameOptions[GameOption::ShowNodeIndices]);
			if (ImGui::Checkbox("Smooth Paths (quick)", &UserOptions::Instance()->gameOptions[GameOption::SmoothPathsQuick]))
			{
				UserOptions::Instance()->gameOptions[GameOption::SmoothPathsPrecise] = false;
			}
			if (ImGui::Checkbox("Smooth Paths (Precise)", &UserOptions::Instance()->gameOptions[GameOption::SmoothPathsPrecise]))
			{
				UserOptions::Instance()->gameOptions[GameOption::SmoothPathsQuick] = false;
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("General Bot Info"))
		{
			ImGui::Checkbox("Show IDs", &UserOptions::Instance()->gameOptions[GameOption::ShowBotIDs]);
			ImGui::Checkbox("Show Health", &UserOptions::Instance()->gameOptions[GameOption::ShowBotHealth]);
			ImGui::Checkbox("Show Scores", &UserOptions::Instance()->gameOptions[GameOption::ShowScore]);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Selected Bot Info"))
		{
			ImGui::Checkbox("Show Target (boxed in red)", &UserOptions::Instance()->gameOptions[GameOption::ShowTargetOfSelectedBot]);
			ImGui::Checkbox("Show Sensed Opponents (boxed in orange)", &UserOptions::Instance()->gameOptions[GameOption::ShowOpponentsSensedBySelectedBot]);
			ImGui::Checkbox("Only Show Opponents in FOV", &UserOptions::Instance()->gameOptions[GameOption::OnlyShowBotsInTargetsFOV]);
			ImGui::Checkbox("Show Goal Queue", &UserOptions::Instance()->gameOptions[GameOption::ShowGoalsOfSelectedBot]);
			ImGui::Checkbox("Show Path", &UserOptions::Instance()->gameOptions[GameOption::ShowPathOfSelectedBot]);
			ImGui::Checkbox("Queue movement command", &UserOptions::Instance()->gameOptions[GameOption::QueueMovementCommand]);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Selected Bot"))
		{
			if (ImGui::Button("Blaster")) processInputEvent(InputEventType::BOT_SELECT_BLASTER);
			if (ImGui::Button("Shotgun")) processInputEvent(InputEventType::BOT_SELECT_SHOTGUN);
			if (ImGui::Button("Rocket Launcher")) processInputEvent(InputEventType::BOT_SELECT_ROCKET_LAUNCHER);
			if (ImGui::Button("Railgun")) processInputEvent(InputEventType::BOT_SELECT_RAIL_GUN);
			if (ImGui::Button("Release Bot")) processInputEvent(InputEventType::BOT_RELEASE);
			if (ImGui::Checkbox("Select Bot", &UserOptions::Instance()->gameOptions[GameOption::SelectBotMode]))
			{
				UserOptions::Instance()->gameOptions[GameOption::PossessedBotFireMode] = false;
			}
			if (ImGui::Checkbox("Fire Mode", &UserOptions::Instance()->gameOptions[GameOption::PossessedBotFireMode]))
			{
				UserOptions::Instance()->gameOptions[GameOption::SelectBotMode] = false;
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void InputSystem::processInputEvent(InputEventType ev)
{
	switch (ev)
	{
	case InputEventType::GAME_ADDBOT:
		break;
	case InputEventType::GAME_REMOVEBOT:
		break;
	case InputEventType::BOT_RELEASE:
		break;
	}
}