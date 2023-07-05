#pragma once

#include "../detour.h"

using KeyboardPressFunction = LRESULT(*)(int param_1, WPARAM param_2, int *param_3);

class KeyboardPressDetour: public Detour {
public:
	static KeyboardPressFunction m_originalKeyboardPress;

	long applyDetour() override;
	long restoreDetour() override;

	static LRESULT hookKeyboardPress(int param_1, WPARAM param_2, int *param_3);
};

