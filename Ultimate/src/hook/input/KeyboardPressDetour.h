#pragma once

#include "../detour.h"

using KeyboardPressFunction = LRESULT(*)(int nCode, WPARAM wParam, LPARAM lParam);

class KeyboardPressDetour: public Detour {
public:
	static KeyboardPressFunction m_originalKeyboardPress;

	long applyDetour() override;
	long restoreDetour() override;

	static LRESULT hookKeyboardPress(int nCode, WPARAM wParam, LPARAM lParam);
};

