#pragma once
#include <stdint.h>
#include <unordered_map>
#include "Events/InputEvents.h"

class InputSystem
{
public:
	InputSystem();
	void processGui();
	void processLocationSelected(int32_t x, int32_t y);
private:
	void processInputEvent(InputEventType ev);
};