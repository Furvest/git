#pragma once
#include "common/vector.hpp"
class InputManager {
	
	int mouse_x, mouse_y;
	bool lmb_press;
	bool lmb_trigger;
public:
	Vector GetMousePosition();
	bool IsLeftClickPressed();
	void Init();
	void ProcessEvent();
};